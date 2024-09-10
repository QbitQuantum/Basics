int
main(int argc, char *argv[])
{
    char pipe[2048];
    MSG msg;
    STARTUPINFO si = { 0, };
    PROCESS_INFORMATION pi = { 0, };
    gchar *program_path = get_program_path();
    gchar *command;
    int rv = 0;

    argv[0] = "gdb -ex run --args";
    command = g_strjoinv(" ", argv);

    snprintf(pipe, sizeof(pipe), "\\\\.\\pipe\\SpiceController-%lu", GetCurrentProcessId());

    SetEnvironmentVariable("SPICE_DEBUG", "1");
    SetEnvironmentVariable("G_MESSAGES_DEBUG", "all");
    SetEnvironmentVariable("SPICE_XPI_NAMEDPIPE", pipe);

    si.cb = sizeof(si);
    if (!CreateProcess(NULL,
                       command,
                       NULL,
                       NULL,
                       FALSE,
                       0,
                       NULL,
                       program_path,
                       &si,
                       &pi)) {
        printf("CreateProcess failed (%ld).\n", GetLastError());
        rv = 1;
        goto end;
    }


    while (1) {
        DWORD reason = MsgWaitForMultipleObjects(1, &pi.hProcess, FALSE,
                                                 INFINITE, QS_ALLINPUT);
        if (reason == WAIT_OBJECT_0)
            break;
        else {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

end:
    g_free(program_path);
    g_free(command);

    exit(rv);
    return rv;
}