# TE0802 Migration Execution Backlog

This backlog turns the high-level plan into immediate, executable work items.

## Current phase

Phase A: discovery and feasibility.

## Sprint 0 goals

- Freeze target TE0802 module + carrier tuple.
- Build interface mapping from MiSTer assumptions to TE0802 resources.
- Stand up baseline Vivado project script with deterministic structure.
- Create and maintain risk register with owners and mitigations.

## Work items

| ID | Task | Owner | Status | Output |
|---|---|---|---|---|
| A-001 | Confirm exact TE0802 part + carrier board | unassigned | in-progress | `docs/te0802-interface-mapping.md` |
| A-002 | Fill initial interface mapping table | unassigned | todo | `docs/te0802-interface-mapping.md` |
| A-003 | Run bootstrap Vivado TCL script and archive logs | unassigned | todo | `build/te0802_bootstrap/` |
| A-004 | Inventory Cyclone V specific dependencies in codebase | unassigned | done | `docs/te0802-cyclonev-dependency-audit.md` |
| A-005 | Fill risk register with owners + target dates | unassigned | in-progress | `docs/te0802-risk-register.md` |
| A-006 | Select reference core for first bring-up | unassigned | in-progress | `docs/te0802-reference-core.md` |
| A-007 | Add platform FPGA abstraction skeleton (non-breaking) | unassigned | done | `platform_fpga.h`, `platform_fpga.cpp`, `fpga_io.cpp` |

## Immediate commands

Run from repository root:

```bash
mkdir -p build/te0802_bootstrap
vivado -mode batch -source scripts/vivado/te0802_bootstrap.tcl -tclargs build/te0802_bootstrap
```

## Exit criteria for Phase A

- Target module and carrier are fixed in writing.
- Interface mapping is completed for all required external functions.
- Bootstrap Vivado project runs cleanly and produces project artifacts.
- Risk register has owners and mitigation actions.