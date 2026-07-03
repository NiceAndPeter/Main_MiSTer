# Adding MCP Capability to Plain Vivado 2025.2

This document explains how to add Model Context Protocol (MCP) control to a standard Vivado 2025.2 installation, so Vivado can be driven from an MCP-capable client.

## 1. What "MCP capability" means

Vivado does not ship with native MCP support. MCP control is provided by a bridge service that:

- Starts or connects to Vivado.
- Executes TCL commands on your behalf.
- Exposes those operations through an MCP server interface.

In practice, you keep Vivado installed as usual and add an external MCP server layer.

## 2. Prerequisites

- Vivado 2025.2 installed and runnable from shell.
- A working Python 3.10+ environment (or the runtime required by your MCP bridge implementation).
- Node.js runtime only if your MCP client or bridge uses it.
- Network permissions for local loopback ports.

Recommended checks:

```bash
vivado -version
which vivado
python3 --version
```

## 3. Bridge architecture

Typical setup:

1. MCP client (IDE/agent) sends a tool request.
2. MCP server receives the request and translates it into Vivado TCL actions.
3. Vivado executes TCL through one of two mechanisms:
   - Direct stdin/stdout proxy (preferred for TCL mode).
   - Vivado webserver endpoint (useful when GUI sessions are involved).
4. Results, logs, and errors flow back through MCP.

## 4. Vivado-side preparation

Use Tcl mode by default for stability and automation.

### Option A: Tcl mode session (preferred)

```bash
vivado -mode tcl
```

### Option B: GUI mode plus webserver

Inside Vivado TCL console:

```tcl
webserver -start -port 8088 -key none
```

Notes:

- `-key none` is convenient for local-only development. Use a key for shared or remote environments.
- Reserve one port per session to avoid collisions.

## 5. MCP server setup steps

The exact command depends on the specific MCP bridge implementation you use, but the pattern is:

1. Install/start the MCP bridge.
2. Configure the Vivado executable path (if not in PATH).
3. Configure session working directory.
4. Configure execution mode:
   - Tcl/proxy mode for raw TCL command fidelity.
   - Webserver mode when GUI/webserver workflow is required.
5. Register the MCP server in your MCP client config.

## 6. Minimal validation flow

After startup, test with read-only TCL commands first:

```tcl
version -short
pwd
get_projects
```

Then test a small project operation:

```tcl
create_project mcp_smoke ./mcp_smoke -part <your_part>
get_property PART [current_project]
close_project
```

If these commands complete with structured responses in the MCP client, your integration is functional.

## 7. Operational best practices

- Keep one command in-flight per Vivado session.
- Batch quick setup commands with semicolons to reduce round trips.
- Keep long-running steps separate (`launch_runs`, `wait_on_run`, `route_design`, etc.).
- Poll status endpoints during long runs instead of repeatedly issuing new execute calls.
- Capture and persist Vivado logs for post-mortem analysis.

## 8. Troubleshooting

### Vivado launches but no command output in MCP

- Confirm execution mode matches session type (proxy for Tcl, webserver for GUI/webserver workflows).
- Verify the process has access to working directory and project files.

### Webserver connection failures

- Confirm `webserver -start` ran successfully.
- Check port availability and firewall rules.
- Validate host/port in MCP server config.

### Commands appear stuck

- Check for long-running implementation/synthesis operations.
- Use status monitoring rather than issuing parallel commands to the same session.

### Display/GUI issues in headless environments

- Prefer Tcl mode for automated tasks.
- For GUI requirements, use a virtual display (for example, Xvnc) and confirm DISPLAY is set.

## 9. Security guidance

- Do not expose unauthenticated webserver endpoints to untrusted networks.
- Prefer local loopback binding when possible.
- Use API keys/tokens where your MCP client/server supports them.
- Treat Vivado logs and TCL history as potentially sensitive project metadata.

## 10. Team onboarding checklist

- Document required Vivado version and patch level.
- Version-control MCP server/client configuration templates.
- Provide a one-command smoke test script.
- Define recovery steps for stale sessions.

With this setup, a plain Vivado 2025.2 installation can be operated through MCP tooling without modifying Vivado itself.