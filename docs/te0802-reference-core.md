# TE0802 Reference Core Selection

Purpose: choose a first core for end-to-end bring-up on TE0802 with minimal risk and maximum debug value.

## Selection criteria

Score each candidate (1 low risk/easy to 5 high risk/hard) on:

- memory bandwidth sensitivity.
- video timing complexity.
- audio path complexity.
- input stack dependence.
- external dependencies (special storage/network/extra devices).
- availability of deterministic smoke tests.

Target profile for first bring-up:

- low to medium complexity.
- stable known-good behavior in current MiSTer deployment.
- clear pass/fail checks for video, audio, and controls.

## Candidate shortlist (initial)

| Candidate | Reason | Risk score (1-5) | Notes |
|---|---|---|---|
| NES | Mature, relatively simple pipeline, fast iteration | 2 | Good for initial video/input/audio validation |
| SMS | Low-medium complexity and broad test ROM availability | 2 | Useful secondary validation target |
| Genesis/MegaDrive | More demanding and useful for timing confidence | 3 | Better as phase-2 reference after first success |

## Proposed decision

Primary reference core: NES

Rationale:

- balances realism with lower integration risk.
- enables quick iteration on platform wrappers.
- has abundant deterministic test content.

Secondary validation core: SMS

Rationale:

- confirms that the platform is not tuned only for one narrow core profile.

## Acceptance tests for reference core

1. boot menu -> load core -> start content without crash.
2. stable video output for at least 30 minutes.
3. audio continuity with no severe artifacts in 30-minute run.
4. controller input latency within agreed threshold.
5. repeatable cold boot success in 10 consecutive attempts.

## Open decisions

- Latency threshold for first pass: no perceptible added lag versus baseline MiSTer setup in A/B testing, then convert to numeric target after measurement harness is in place.
- Initial reproducible test set: one deterministic input-heavy title, one scrolling stress title, one audio continuity title.
- Workstream owner tag: reference-core-bringup.

## Decision status

Reference core track is now considered selected and ready for execution (NES primary, SMS secondary).