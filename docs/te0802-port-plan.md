# MiSTer (Cyclone V) to Trenz TE0802 Conversion Plan

## 1. Objective and success criteria

Port the MiSTer platform from Intel Cyclone V SoC assumptions to a Trenz TE0802-based Xilinx platform, with staged milestones and measurable acceptance criteria.

Primary success criteria:

- System boots to a stable control menu.
- One reference core runs with usable video, audio, and input.
- Timing/resource closure is repeatable in CI-like build flow.
- Platform interfaces are abstracted so additional cores can be migrated incrementally.

## 2. Scope boundary

In scope:

- Platform layer and hardware bring-up for TE0802 target.
- Build/tooling migration to Vivado flow.
- Integration path for at least one representative core.

Out of scope for initial milestones:

- Immediate 1:1 compatibility for all MiSTer cores.
- Perfect feature parity before first hardware validation.

## 3. Target definition

Freeze target hardware before implementation:

- Exact TE0802 variant (FPGA, speed grade, memory configuration).
- Carrier board and expansion stack.
- External interfaces required in first release (video, audio, storage, USB/input, network).

Deliverable: interface mapping table from current MiSTer platform signals/functions to TE0802/carrier resources.

## 4. Architecture strategy

Use a strict platform abstraction to isolate board/vendor specifics.

Define wrappers for:

- Clock and reset generation.
- Memory subsystem access.
- Video output path.
- Audio output path.
- Input subsystem.
- Storage and control-plane I/O.

Keep core-facing interfaces stable so existing logic can be adapted with minimal churn.

## 5. Work breakdown

### Phase A: Discovery and feasibility

- Inventory Cyclone V specific assumptions and Intel IP dependencies.
- Identify Linux/userspace components coupled to Cyclone V memory-mapped blocks.
- Identify high-risk domains: memory bandwidth, video timing, low-latency input path.

Exit criteria:

- Risk register with mitigation options.
- Frozen first implementation scope.

### Phase B: Xilinx platform baseline

- Create Vivado project and constraints for TE0802 + carrier.
- Bring up processing subsystem (if used) with DDR, SD, and baseline I/O.
- Establish deterministic reset and multi-clock plan.

Exit criteria:

- Baseline bitstream and software image boots reliably.
- Stable console/log path for bring-up diagnostics.

### Phase C: Subsystem ports

- Memory: port allocator/arbitration assumptions to Xilinx memory path.
- Video: port timing/scaler path to target output chain.
- Audio: port low-latency output pipeline.
- Input: port controller/USB/event path and validate latency budget.

Exit criteria:

- Synthetic tests pass for memory stress, video timing, audio continuity, and input responsiveness.

### Phase D: Reference core integration

- Select one medium-complexity core.
- Integrate and debug end-to-end runtime path.
- Close timing/resource constraints for repeatable implementation.

Exit criteria:

- Reference core playable and stable.
- Known-issues list documented.

### Phase E: Core migration waves

- Wave 1: low-complexity cores.
- Wave 2: medium-complexity cores.
- Wave 3: high-bandwidth/timing-sensitive cores.

Exit criteria:

- Per-core compatibility matrix with pass/fail and caveats.

## 6. Milestones (suggested)

- M0 (2-4 weeks): feasibility complete, architecture frozen.
- M1 (4-8 weeks): TE0802 baseline platform operational.
- M2 (4-8 weeks): reference core functional on hardware.
- M3 (ongoing): migration waves and stabilization.

## 7. Verification and quality gates

Minimum quality gates per milestone:

- Build reproducibility (clean build scripts, deterministic outputs).
- Timing checks with tracked slack trends.
- Runtime soak test on target hardware.
- Regression checklist for boot, video, audio, input, and storage.

## 8. Risk register (initial)

- Memory architecture mismatch can cause non-obvious runtime faults.
- Video chain differences can break timing-sensitive cores.
- Input/event stack changes can increase control latency.
- Vendor IP lock-in can slow core migration.

Mitigation:

- Early synthetic subsystem tests.
- Strict wrapper interfaces.
- Reference-core-first integration before broad rollout.

## 9. Immediate next actions

- Finalize TE0802 variant and carrier selection.
- Produce interface mapping table.
- Set up Vivado project skeleton with constraints and baseline clocks.
- Select the reference core and define acceptance tests.