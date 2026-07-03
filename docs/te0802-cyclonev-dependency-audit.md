# Cyclone V Dependency Audit for TE0802 Migration

Date: 2026-07-03

Purpose: identify code paths tightly coupled to Cyclone V SoCFPGA/HPS hardware so they can be isolated behind a new TE0802 platform layer.

## Executive summary

High coupling is concentrated in low-level FPGA programming and bridge control logic. The largest blocker is the direct use of SoCFPGA register maps and hard-coded address constants in the runtime path used for bitstream loading and FPGA-HPS bridge management.

Most platform-sensitive code appears in:

- fpga I/O and bitstream loading path.
- SoCFPGA register definition headers.
- small Linux/sysfs assumptions tied to HPS naming.

## Findings by severity

## Critical: direct SoCFPGA register programming path

Files:

- fpga_io.cpp
- fpga_base_addr_ac5.h
- fpga_manager.h
- fpga_reset_manager.h
- fpga_system_manager.h
- fpga_nic301.h

Evidence:

- SoCFPGA address constants are used directly for register access and bridge control.
- Runtime casts fixed addresses into SoCFPGA register structures.
- Bitstream programming is implemented through SoCFPGA FPGA manager register protocol (`socfpga_load`, `fpgamgr_*`).
- bridge sequencing manipulates reset/NIC/system manager registers directly (`do_bridge`).

Migration implication:

- This implementation cannot be reused as-is on TE0802.
- A new board abstraction is required for bitstream lifecycle operations and bridge/memory interconnect enable/disable behavior.

Action:

- Introduce a platform interface:
  - `platform_fpga_load_bitstream(path_or_buffer)`
  - `platform_bridges_set(enabled)`
  - `platform_fpga_ready()`
- Move existing SoCFPGA logic behind a Cyclone V backend so TE0802 can provide a Xilinx backend.

## High: hard-coded memory-map assumptions

Files:

- fpga_base_addr_ac5.h
- fpga_io.cpp

Evidence:

- SoCFPGA HPS-FPGA and FPGA-HPS windows are fixed at address constants (for example LWHPS2FPGA, HPS2FPGA, FPGA2HPS ranges).
- direct reads/writes are performed through those windows.

Migration implication:

- Existing register aperture assumptions will not match TE0802/Xilinx PS mapping.

Action:

- Replace fixed address macros in common runtime with backend-provided accessors.
- Define one neutral register access API and per-platform mapping implementation.

## Medium: Linux HPS-specific sysfs assumptions

Files:

- input.cpp

Evidence:

- LED monitor path references `/sys/class/leds/hps_led0/brightness_hw_changed`.

Migration implication:

- Path naming is board-specific and likely invalid on TE0802 Linux images.

Action:

- Move LED/sysfs paths into runtime-configurable platform settings.
- Add graceful fallback when path does not exist.

## Medium: command/interface naming with HPS semantics

Files:

- user_io.h
- video.cpp
- menu.cpp (comments/ownership assumptions)

Evidence:

- constants and messages use HPS-specific language.

Migration implication:

- Mostly cosmetic or ownership semantics, but can hide architectural assumptions.

Action:

- Keep protocol IDs stable for compatibility, but rename internal abstraction layer terminology to `platform` or `host` in new code.

## Low: support modules mentioning hps_io in comments

Files:

- support/c64/c64.cpp
- support/megadrive/mdplus.cpp
- support/sharpmz/*

Evidence:

- mostly comments or protocol notes, not necessarily hard blockers.

Migration implication:

- verify case-by-case when each core support module is enabled.

Action:

- defer to core migration phase; do not block Phase A/B on these items.

## Proposed portability split

Create a thin platform boundary with two implementations:

- `platform/cyclonev/*` (existing behavior extracted from current code)
- `platform/te0802/*` (new Xilinx implementation)

Candidate interface surface:

- bitstream load and readiness.
- bridge enable/disable and reset sequencing.
- low-level register read/write accessors.
- board service helpers (LED state, reboot policy hooks, optional diagnostics).

## Immediate next implementation tasks

1. Extract SoCFPGA-specific logic from `fpga_io.cpp` into a Cyclone V backend module without changing behavior.
2. Replace direct SoCFPGA macro use in shared paths with backend calls.
3. Add a compile-time platform selector and default to existing Cyclone V backend until TE0802 backend is ready.
4. Define TE0802 backend stubs to allow incremental bring-up and unit-level compile checks.

## Audit scope notes

- Search was performed with recursive grep due unavailable ripgrep in this environment.
- This audit focuses on explicit platform-coupled code paths and does not yet include timing/performance profiling.