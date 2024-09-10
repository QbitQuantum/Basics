void DoParentProcess()
{
    TCHAR                   szPath[MAX_PATH] = {0,};
    STARTUPINFO				si = {sizeof(STARTUPINFO),};
    PROCESS_INFORMATION		pi = {0,};
    DEBUG_EVENT             de = {0,};
    CONTEXT                 ctx = {0,};
    BYTE                    pBuf[0x20] = {0,};
    DWORD                   dwExcpAddr = 0, dwExcpCode = 0;
    const DWORD             DECODING_SIZE = 0x14;
    const DWORD             DECODING_KEY = 0x7F;
    const DWORD             EXCP_ADDR_1 = 0x0040103F;
    const DWORD             EXCP_ADDR_2 = 0x00401048;
    
    // create debug process
    GetModuleFileName(
        GetModuleHandle(NULL), 
        szPath, 
        MAX_PATH);

    if( !CreateProcess(
            NULL,
            szPath,
            NULL, NULL,
            FALSE,
            DEBUG_PROCESS | DEBUG_ONLY_THIS_PROCESS,
            NULL, NULL,
            &si,
            &pi) )
    {
        printf("CreateProcess() failed! [%d]\n", GetLastError());
        return;
    }

    printf("Parent Process\n");

    // debug loop
    while( TRUE )
    {
        ZeroMemory(&de, sizeof(DEBUG_EVENT));

        if( !WaitForDebugEvent(&de, INFINITE) )
        {
            printf("WaitForDebugEvent() failed! [%d]\n", GetLastError());
            break;
        }

        if( de.dwDebugEventCode == EXCEPTION_DEBUG_EVENT )
        {
            dwExcpAddr = (DWORD)de.u.Exception.ExceptionRecord.ExceptionAddress;
            dwExcpCode = de.u.Exception.ExceptionRecord.ExceptionCode;

            if( dwExcpCode == EXCEPTION_ILLEGAL_INSTRUCTION )
            {
                if( dwExcpAddr == EXCP_ADDR_1 )
                {
                    // decoding
                    ReadProcessMemory(
                        pi.hProcess, 
                        (LPCVOID)(dwExcpAddr + 2),
                        pBuf,
                        DECODING_SIZE,
                        NULL);

                    for(DWORD i = 0; i < DECODING_SIZE; i++)
                        pBuf[i] ^= DECODING_KEY;

                    WriteProcessMemory(
                        pi.hProcess,
                        (LPVOID)(dwExcpAddr + 2),
                        pBuf,
                        DECODING_SIZE,
                        NULL);
                    
                    // change EIP
                    ctx.ContextFlags = CONTEXT_FULL;
                    GetThreadContext(pi.hThread, &ctx);
                    ctx.Eip += 2;
                    SetThreadContext(pi.hThread, &ctx);
                }
                else if( dwExcpAddr == EXCP_ADDR_2 )
                {
                    pBuf[0] = 0x68;
                    pBuf[1] = 0x1C;
                    WriteProcessMemory(
                        pi.hProcess,
                        (LPVOID)dwExcpAddr,
                        pBuf,
                        2,
                        NULL);
                }
            }
        }
        else if( de.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT )
        {
            break;
        }

        ContinueDebugEvent(de.dwProcessId, de.dwThreadId, DBG_CONTINUE);
    }
}