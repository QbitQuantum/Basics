VOID _cdecl wmain( ULONG argc, WCHAR* argv[] )
{
    if (argc < 2)
    {
        wprintf(L"03sample <target>\n");
        return;
    }

    STARTUPINFO startupInfo={0}; 
    startupInfo.cb = sizeof(startupInfo);
    PROCESS_INFORMATION processInfo = {0};


    int commandLength = wcslen(argv[1])+(argv[2]?wcslen(argv[2]):0) + 2;
    WCHAR * commandLine = new WCHAR[commandLength];
    if (!commandLine)
    {
        TRACE(L"Allocation failed\n");
    }
    wcscpy_s(commandLine, commandLength, argv[1]);
    if (argv[2])
    {
        wcscat_s(commandLine, commandLength, L" ");
        wcscat_s(commandLine, commandLength, argv[2]);
    }

    BOOL res = CreateProcess(NULL, commandLine, NULL, NULL, FALSE, DEBUG_PROCESS, NULL, NULL, &startupInfo, &processInfo);
    if (FALSE == res)
    {
        TRACE(L"CreateProcess failed\n");
        return;
    }
    DEBUG_EVENT debugEvent = { 0 } ;

    DWORD endDisposition = DBG_CONTINUE;
    for(;endDisposition != 0;)
    {
        if (!WaitForDebugEvent(&debugEvent, INFINITE))
        {
            TRACE(L"WaitForDebugEvent failed\n");
            break;
        }
        endDisposition = ProcessEvent(debugEvent);
        if (0 == endDisposition) break;
        if (!ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, endDisposition))
        {
            TRACE(L"ContinueDebugEvent failed\n");
            break;
        };
    }
}