void service_process(BOOL (*start_service)(PCSTR, PCWSTR), int argc, char** argv)
{
    BOOL res;

    StringCbCopyA(service_nameA, sizeof(service_nameA), argv[2]);
    MultiByteToWideChar(CP_ACP, 0, service_nameA, -1, service_nameW, _countof(service_nameW));
    StringCbPrintfW(named_pipe_name, sizeof(named_pipe_name), L"\\\\.\\pipe\\%ls_pipe", service_nameW);

    res = WaitNamedPipeW(named_pipe_name, NMPWAIT_USE_DEFAULT_WAIT);
    if (!res)
        return;

    hClientPipe = CreateFileW(named_pipe_name, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hClientPipe == INVALID_HANDLE_VALUE)
        return;

    service_trace("Service process starting...\n");
    res = start_service(service_nameA, service_nameW);
    service_trace("Service process stopped.\n");

    CloseHandle(hClientPipe);
}