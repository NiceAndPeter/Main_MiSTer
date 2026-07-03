# TE0802 Migration Risk Register

Update this register continuously during implementation.

| ID | Risk | Probability | Impact | Mitigation | Owner | Status |
|---|---|---|---|---|---|---|
| R-001 | Memory architecture mismatch causes runtime instability | medium | high | Create memory stress tests before core bring-up | unassigned | open |
| R-002 | Video timing incompatibility with timing-sensitive cores | medium | high | Validate with synthetic patterns and strict timing reports | unassigned | open |
| R-003 | Input latency regression in new board stack | medium | medium | Measure input-to-frame latency on reference core | unassigned | open |
| R-004 | Intel-specific IP dependencies block quick migration | high | medium | Replace dependencies with wrappers and portability layer | unassigned | open |
| R-005 | Timing closure fails at target clocks on TE0802 | medium | high | Establish timing budget and monitor slack trend per build | unassigned | open |

## Review cadence

- Weekly: review probability/impact changes.
- Per milestone: close obsolete risks and add newly discovered risks.