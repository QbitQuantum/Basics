/** VOID WINAPI OssecServiceCtrlHandler (DWORD dwOpcode)
 * "Signal" handler
 */
VOID WINAPI OssecServiceCtrlHandler(DWORD dwOpcode)
{
    switch(dwOpcode)
    {
        case SERVICE_CONTROL_STOP:
            ossecServiceStatus.dwCurrentState           = SERVICE_STOPPED;
            ossecServiceStatus.dwWin32ExitCode          = 0;
            ossecServiceStatus.dwCheckPoint             = 0;
            ossecServiceStatus.dwWaitHint               = 0;

            verbose("%s: Received exit signal.", ARGV0);
            SetServiceStatus (ossecServiceStatusHandle, &ossecServiceStatus);
            verbose("%s: Exiting...", ARGV0);
            return;
        default:
            break;
    }
    return;
}