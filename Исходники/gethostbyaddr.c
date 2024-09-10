int __cdecl main(int argc, char *argv[])
{
    WORD VersionRequested = MAKEWORD(2, 2);
    WSADATA WsaData;
    int err;
    struct hostent *host;
    u_long addr;
    BOOL errorFlag = FALSE;
    int i = 0;
    int strlength = 0;
    char ch;

    /*Initialize the PAL environment*/
    err = PAL_Initialize(argc, argv);
    if(0 != err)
    {
        return FAIL;
    }

    /*initialize to use winsock2.dll*/
    err = WSAStartup(VersionRequested, &WsaData);
    if(err != 0)
    {
        Fail("\nFailed to find a usable WinSock DLL!\n");
    }

    /*Confirm that the WinSock DLL supports 2.2.*/
    if(LOBYTE( WsaData.wVersion ) != 2 ||
            HIBYTE( WsaData.wVersion ) != 2 )
    {
        Trace("\nFailed to find a usable WinSock DLL!\n");
        err = WSACleanup();
        if(SOCKET_ERROR == err)
        {
            Trace("\nFailed to call WSACleanup API!\n");
        }
        Fail("");
    }

    addr = inet_addr("127.0.0.1");

    host = gethostbyaddr ((const char *)&addr, sizeof(addr), AF_INET );
    if(NULL == host)
    {
        Trace("\nFailed to call gethostbynaddr API to retrive host info, "
                "error code = %u\n", GetLastError());
        err = WSACleanup();
        if(SOCKET_ERROR == err)
        {
            Trace("\nFailed to call WSACleanup API!\n");
        }
        Fail("");
    }


    /*
    *further check the struct host contains legal DNS name
    *with alphanumeric, dot, underscore and hyphan characters
    */ 
    strlength = (int)strlen(host->h_name); 
    
    for(i = 0; i < strlength; i++)
    {
        ch = host->h_name[i];
        if(!(ch == '.' || ch == '-' || (ch <= 'z' && ch >= 'a') ||
            (ch <= 'Z' && ch >= 'A') || (ch <='9' && ch >= '0') ||
            (ch == '_')))
        {
            errorFlag = TRUE;
        }
    }

    if(errorFlag)
    {
        Trace("\nFailed to call gethostbyaddr API to retrieve host info, "
                "the hostent struct does not contain valid host name "
                "the host name is = %s\n", host->h_name);
               
        err = WSACleanup();
        if(SOCKET_ERROR == err)
        {
            Trace("\nFailed to call WSACleanup API!\n");
        }
        Fail("");
    }

    err = WSACleanup();
    if(SOCKET_ERROR == err)
    {
        Fail("\nFailed to call WSACleanup API!\n");
    }

    PAL_Terminate();
    return PASS;
}