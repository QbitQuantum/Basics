PWSSOCKET
WSAAPI
WsSockFindIfsSocket(IN SOCKET Handle)
{
    INT ErrorCode;
    DWORD Flags;
    PWSSOCKET Socket = NULL;
    PWSPROCESS Process = NULL;
    PTCATALOG Catalog = NULL;

    /* Validate the socket and get handle info */
    if ((Handle != INVALID_SOCKET) &&
        (GetHandleInformation((HANDLE)Handle, &Flags)))
    {
        /* Get the process */
        if ((Process = WsGetProcess()))
        {
            /* Get the catalog */
            Catalog = WsProcGetTCatalog(Process);

            /* Get the IFS Provider */
            ErrorCode = WsTcFindIfsProviderForSocket(Catalog, Handle);

            /* Check for success */
            if (ErrorCode == ERROR_SUCCESS)
            {
                /* Get the Socket now */
                Socket = WsSockGetSocketNoExport(Handle);

                /* Mark it as an API Socket */
                if (Socket) Socket->ApiSocket = TRUE;
            }
        }
    }

    /* Return the socket */
    return Socket;
}