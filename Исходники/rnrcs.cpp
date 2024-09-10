//---------------------------------------------------------------------------
//  FUNCTION: BOOL WINAPI CtrlHandler ( DWORD dwEvent )
//  Intercept CTRL-C or CTRL-BRK events and cause the server to 
//  initiate shutdown and cleanup.
//---------------------------------------------------------------------------
BOOL WINAPI CtrlHandler (   DWORD dwEvent )
{
    int nRet = 0;
    int i = 0;
    WCHAR szGuid[MAX_PATH] = {'\0'};
    HRESULT hRet;

    switch (dwEvent)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
    case CTRL_CLOSE_EVENT:
        fEndProgram = TRUE;
        printf("CtrlHandler: cleaning up...\n");

        printf("delete service instance...\n");
        nRet = WSASetService(&g_QS, RNRSERVICE_DELETE, 0L);
        if (nRet == SOCKET_ERROR)
        {
            printf("WSASetService DELETE error %d\n", WSAGetLastError());
        } else
            printf(" Deleted.\n");
        
        printf("Removing Service class ");

        if (SUCCEEDED(hRet = StringCchPrintfW(szGuid,
                                              sizeof(szGuid)/sizeof(szGuid[0]),
                                              L"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                                              g_MyGuid.Data1,                    
                                              g_MyGuid.Data2,
                                              g_MyGuid.Data3,
                                              g_MyGuid.Data4[0],
                                              g_MyGuid.Data4[1],
                                              g_MyGuid.Data4[2],
                                              g_MyGuid.Data4[3],
                                              g_MyGuid.Data4[4],
                                              g_MyGuid.Data4[5],
                                              g_MyGuid.Data4[6],
                                              g_MyGuid.Data4[7]
                                             )))
        {
            wprintf(L"%s",szGuid);

        }

        printf("... \n");

        nRet = WSARemoveServiceClass(&g_MyGuid);
        if (nRet == SOCKET_ERROR)
        {
            printf("WSARemoveServiceClass error %d\n", WSAGetLastError());
        } else
            printf(" Removed.\n");

        for (i = 0; i < g_nMaxNumOfSocks; i++)
        {
            if ( g_aSock[i] != INVALID_SOCKET )
            {
                closesocket ( g_aSock[i] );
                g_aSock[i] = INVALID_SOCKET;
            }
        }
        break;

    default:
        // unknown type--better pass it on.
        return FALSE;
    }
    return TRUE;
}