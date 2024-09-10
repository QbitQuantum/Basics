BOOL
IrdaStartDocPort(
    _Inout_ PLCMINIPORT    pIniPort
    )
{
    HANDLE hToken       = NULL;
    DWORD  dwLastError  = ERROR_SUCCESS;


    //
    // If remote guest is the first user to print, then the connect fails.
    // Thus we need to revert to system context before calling IrdaConnect
    //

    hToken = RevertToPrinterSelf();

    if (!hToken) {
        return FALSE;
    }

    dwLastError = IrdaConnect(pIniPort);

    ImpersonatePrinterClient(hToken);

    if ( dwLastError ) {

        SetLastError(dwLastError);
        return FALSE;
    } else
        return TRUE;
}