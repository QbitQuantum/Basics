int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (!lpCmdLine)
        return 1;

    if (!*lpCmdLine) {
        DWORD ppid = getppid();
        HANDLE pproc = OpenProcess(SYNCHRONIZE | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
            FALSE, ppid);
        if (pproc) {
            WaitForSingleObject(pproc, INFINITE);
            SetSuspendState(TRUE, FALSE, FALSE);
        }
    } else {
        run(__argv[0], FALSE);
        run(lpCmdLine, TRUE);
    }

    return 0;
}