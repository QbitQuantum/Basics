/**********************************************************************
 *	RegisterServiceCtrlHandlerA
 *
 * @implemented
 */
SERVICE_STATUS_HANDLE WINAPI
RegisterServiceCtrlHandlerA(LPCSTR lpServiceName,
                            LPHANDLER_FUNCTION lpHandlerProc)
{
    ANSI_STRING ServiceNameA;
    UNICODE_STRING ServiceNameU;
    SERVICE_STATUS_HANDLE SHandle;

    RtlInitAnsiString(&ServiceNameA, (LPSTR)lpServiceName);
    if (!NT_SUCCESS(RtlAnsiStringToUnicodeString(&ServiceNameU, &ServiceNameA, TRUE)))
    {
        SetLastError(ERROR_OUTOFMEMORY);
        return (SERVICE_STATUS_HANDLE)0;
    }

    SHandle = RegisterServiceCtrlHandlerW(ServiceNameU.Buffer,
                                          lpHandlerProc);

    RtlFreeUnicodeString(&ServiceNameU);

    return SHandle;
}