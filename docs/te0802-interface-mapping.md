# MiSTer to TE0802 Interface Mapping

Populate this sheet before RTL or software porting decisions are finalized.

## Target definition

- TE0802 module variant: TODO
- Carrier board: TODO
- FPGA part number: TODO
- DDR type/size: TODO
- Required bring-up interfaces: video, audio, input, storage, control path

## Functional mapping table

| MiSTer function | Existing Cyclone V dependency | TE0802/carrier resource | Migration strategy | Status |
|---|---|---|---|---|
| FPGA fabric clocks | Cyclone V PLL + board osc assumptions | TODO | Add wrapper + Xilinx MMCM/PLL config | todo |
| Reset sequencing | Cyclone V reset manager assumptions | TODO | Board-specific reset controller wrapper | todo |
| Main memory path | Cyclone V/SoC memory map assumptions | TODO | Abstract memory adapter + arbitration update | todo |
| Video output | Existing HDMI/scaler chain assumptions | TODO | Replace low-level PHY path, keep core API | todo |
| Audio output | Existing audio codec/DAC path assumptions | TODO | Implement TE0802-compatible audio wrapper | todo |
| Input devices | USB/input event stack assumptions | TODO | Port board support and event plumbing | todo |
| SD/storage | Existing storage path and mount assumptions | TODO | Validate device mapping + boot flow | todo |
| Network (optional first pass) | Existing network stack assumptions | TODO | Defer or map via carrier Ethernet | todo |

## Signal-level notes

Add interface-specific signal and timing notes here as constraints are discovered.

## Decision log

| Date | Decision | Reason | Impact |
|---|---|---|---|
| 2026-07-03 | Created mapping template | Start execution of TE0802 plan | Enables concrete dependency tracking |