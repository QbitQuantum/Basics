static int cr_runproc(wchar_t *name, wchar_t *cmdline)
{
    STARTUPINFOW si;
    STARTUPINFOW our_si;
    PROCESS_INFORMATION pi;
    DWORD retval = 1;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.dwFlags |= STARTF_USESTDHANDLES;

    // Copy the list of inherited CRT file descriptors to the new process
    our_si.cb = sizeof(our_si);
    GetStartupInfoW(&our_si);
    si.lpReserved2 = our_si.lpReserved2;
    si.cbReserved2 = our_si.cbReserved2;

    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessW(name, cmdline, NULL, NULL, TRUE, 0,
                        NULL, NULL, &si, &pi)) {

        cr_perror(L"CreateProcess");
    } else {
        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &retval);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    return (int)retval;
}