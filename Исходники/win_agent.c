int __cdecl main( int argc, CHAR* argv[] )
{
    
    ShowWindow(GetConsoleWindow(),SW_HIDE);
    
    int iResult;
    CHAR sLogMessage[SZ_MAX_LOG];
    
    WSADATA wsaData;
    SOCKET sListenSocket = INVALID_SOCKET;  // listen socket
    
    LUID pv;
    TOKEN_PRIVILEGES tp;
    HANDLE hProc;
    HMODULE ntdll;
    
    // Raise up the privilege
    LookupPrivilegeValue( NULL, "SeProfileSingleProcessPrivilege", &pv );
    OpenProcessToken( GetCurrentProcess(), TOKEN_WRITE, &hProc );
        
    tp.PrivilegeCount            = 1;
    tp.Privileges[0].Luid        = pv;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(    hProc,
                            FALSE,
                            &tp,
                            sizeof(TOKEN_PRIVILEGES),
                            (PTOKEN_PRIVILEGES)NULL,
                            (PDWORD)NULL );
    ntdll = LoadLibrary("ntdll.dll");
    NtSetSystemInformation = (NTSTATUS (WINAPI *)(INT, PVOID, ULONG))GetProcAddress(ntdll, "NtSetSystemInformation");    
    
    GetLocalTime(&localTime);
    
    g_hLog = create_log_file( NULL );
    if (g_hLog == INVALID_HANDLE_VALUE) {
        write_agent_log("main - CreateFile - log file", TRUE);
        return 1;
    }

    // Initialize Winsock using Windows socket API version 2.2
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        write_agent_log("main - WSAStartup", TRUE);
        return 2;
    }

    // Server socket setup
    sListenSocket = socket_setup();
    if (sListenSocket == -1) {
        write_agent_log("main - socket_setup", TRUE);
        return 3;
    }

    // Giving welcom message
    sprintf_s(sLogMessage, SZ_MAX_LOG, "================ Welcome to MBA Agent ================\r\n");
    write_agent_log(sLogMessage, FALSE);

    // Server infinite loop
    server_mainloop( sListenSocket );

    // Cleanup
    WSACleanup();
    closesocket(sListenSocket);
    CloseHandle(g_hLog);

    return 0;
}