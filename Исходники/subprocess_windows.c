void gpr_subprocess_interrupt(gpr_subprocess *p) {
    DWORD dwExitCode;
    if (GetExitCodeProcess(p->pi.hProcess, &dwExitCode)) {
        if (dwExitCode == STILL_ACTIVE) {
            gpr_log(GPR_INFO, "sending ctrl-break");
            GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, p->pi.dwProcessId);
            p->joined = 1;
            p->interrupted = 1;
        }
    }
    return;
}