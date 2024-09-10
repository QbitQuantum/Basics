static void WINAPI handler(DWORD sigint)
{
    switch(sigint) {
    case 128:
        // control::request("reload");
        return;
    case 129:
        // control::request("snapshot");
    case SERVICE_CONTROL_SHUTDOWN:
    case SERVICE_CONTROL_STOP:
        status.dwCurrentState = SERVICE_STOP_PENDING;
        status.dwWin32ExitCode = 0;
        status.dwCheckPoint = 0;
        status.dwWaitHint = 6000;
        SetServiceStatus(hStatus, &status);
        // control::request("down");
        break;
    default:
        break;
    }
}