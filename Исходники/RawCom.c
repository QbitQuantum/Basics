static BOOL CloseConnection(LPCOMMINFO hCom)
{

    if (NULL == hCom)
      return (FALSE);

    // drop DTR
    EscapeCommFunction(hCom->hComPort, CLRDTR);

    // purge any outstanding reads/writes and close device handle
    PurgeComm(hCom->hComPort, PURGE_TXABORT | PURGE_RXABORT |
                            PURGE_TXCLEAR | PURGE_RXCLEAR);

    // close handle
    CloseHandle(hCom->hComPort);

    return (TRUE);

} // end of CloseConnection()