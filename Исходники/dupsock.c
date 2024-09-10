/*
 * @implemented
 */
INT
WSAAPI
WSADuplicateSocketA(IN SOCKET s,
                    IN DWORD dwProcessId,
                    OUT LPWSAPROTOCOL_INFOA lpProtocolInfo)
{
    WSAPROTOCOL_INFOW ProtocolInfoW;
    INT ErrorCode;
    DPRINT("WSADuplicateSocketA: %lx, %lx, %p\n", s, dwProcessId, lpProtocolInfo);
  
    /* Call the Unicode Function */
    ErrorCode = WSADuplicateSocketW(s, dwProcessId, &ProtocolInfoW);

    /* Check for success */
    if (ErrorCode == ERROR_SUCCESS)
    {                          
        /* Convert Protocol Info to Ansi */
        if (lpProtocolInfo) 
        {    
            /* Convert the information to ANSI */
            ErrorCode = MapUnicodeProtocolInfoToAnsi(&ProtocolInfoW,
                                                     lpProtocolInfo);
        }
        else
        {
            /* Fail */
            ErrorCode = WSAEFAULT;
        }

        /* Check if the conversion failed */
        if (ErrorCode != ERROR_SUCCESS)
        {
            /* Set the last error and normalize the error */
            SetLastError(ErrorCode);
            ErrorCode = SOCKET_ERROR;
        }
    }

    /* Return */
    return ErrorCode;
}