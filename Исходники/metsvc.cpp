VOID WINAPI ServiceCtrlHandler(DWORD fdwControl)
{
    switch (fdwControl) {
        case SERVICE_CONTROL_STOP:
        case SERVICE_CONTROL_SHUTDOWN:
            status.dwCurrentState = SERVICE_STOPPED;
            break;

        default:
            break;
    }

    if (SetServiceStatus(hStatus, &status) == 0) {
        printf("Cannot set service status (0x%08x)\n", GetLastError());
        exit(1);
    }

    return;
}