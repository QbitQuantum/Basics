int _tmain( int argc, _TCHAR* argv[] )
{
    BOOL                bRet = FALSE;
    STARTUPINFO         startupInfo = { sizeof startupInfo };
    PROCESS_INFORMATION procInfo = { 0 };
    DEBUG_EVENT         event = { 0 };
    _EventCallback   callback;
    Exec        exec;
    HRESULT     hr = S_OK;
    LaunchInfo  info = { 0 };

    InitDebug();

    //char*   s1 = new ( _NORMAL_BLOCK, __FILE__, __LINE__ ) char[100];
    //strcpy( s1, "hello, yo!" );
    //char*   s2 = (char*) malloc( 300 );
    //strcpy( s2, "say what?" );

    callback.SetExec( &exec );

    hr = exec.Init( &callback );
    if ( FAILED( hr ) )
        goto Error;
    
#if 0
    bRet = CreateProcess( L"F:\\Users\\Magus\\Documents\\Visual Studio 2008\\Projects\\test1\\Debug\\test1.exe",
    //bRet = CreateProcess( L"F:\\Users\\Magus\\Documents\\Visual Studio 2008\\Projects\\test1\\x64\\Debug\\test1.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        DEBUG_ONLY_THIS_PROCESS,
        NULL,
        NULL,
        &startupInfo,
        &procInfo );
    if ( !bRet )
        goto Error;
#else

//#define TEST_APP64

#ifndef TEST_APP64
    info.CommandLine = L"\"F:\\Users\\Magus\\Documents\\Visual Studio 2008\\Projects\\Debugger1\\Debug\\test1.exe\"";
    info.Exe = L"F:\\Users\\Magus\\Documents\\Visual Studio 2008\\Projects\\Debugger1\\Debug\\test1.exe";
#else
    info.CommandLine =L"\"F:\\Users\\Magus\\Documents\\Visual Studio 2008\\Projects\\Debugger1\\x64\\Debug\\test1.exe\"";
    info.Exe = L"\"F:\\Users\\Magus\\Documents\\Visual Studio 2008\\Projects\\Debugger1\\x64\\Debug\\test1.exe\"";
#endif

    IProcess*   proc = NULL;

    //hr = exec.Attach( 5336, proc );
    hr = exec.Launch( &info, proc );
    if ( FAILED( hr ) )
        goto Error;
#endif

#if 0
    bRet = WaitForDebugEvent( &event, INFINITE );
    if ( !bRet )
        goto Error;
#else
    int stepCount = 0;

    for ( int i = 0; /* doesn't end */ ; i++ )
    {
        hr = exec.WaitForEvent( 1000 );
        if ( FAILED( hr ) )
            goto Error;

        hr = exec.DispatchEvent();
        if ( FAILED( hr ) )
            goto Error;

#if 1
        if ( proc->IsStopped() )
        {
            if ( callback.GetHitBp() )
            {
                stepCount++;

                //11728
                IModule*    mod = NULL;
                UINT_PTR    baseAddr = 0;

                callback.GetModule( mod );
                baseAddr = (UINT_PTR) mod->GetImageBase();
                mod->Release();

                //hr = exec.StepOut( proc, (void*) (baseAddr + 0x00011728) );
                //hr = exec.StepInstruction( proc, true );

                if ( stepCount > 1 )
                    hr = exec.StepInstruction( proc, true, true );
                else
                {
                    //113A5
                    AddressRange    range = { baseAddr + 0x0001137A, baseAddr + 0x000113A5 };
                    hr = exec.StepRange( proc, false, range, true );
                }

                if ( FAILED( hr ) )
                    goto Error;
            }
            else
            {
                hr = exec.Continue( proc, true );
                if ( FAILED( hr ) )
                    goto Error;
            }
        }
#endif

#if 1
        if ( i == 0 )
        {
            IModule*    mod = NULL;
            UINT_PTR    baseAddr = 0;

            callback.GetModule( mod );
            baseAddr = (UINT_PTR) mod->GetImageBase();

            // 0x003C137A, 0x003C1395
            // 1137A, 11395

            //exec.SetBreakpoint( proc, baseAddr + 0x0001138C, 255 );
            exec.SetBreakpoint( proc, baseAddr + 0x0001137A );
            //exec.SetBreakpoint( proc, baseAddr + 0x00011395, 129 );

            mod->Release();
        }
#endif
    }
#endif

Error:
    //exec.Detach( proc );

    // when the debugger goes away, so does the debuggee automatically

    //if ( procInfo.hThread != NULL )
    //{
    //    CloseHandle( procInfo.hThread );
    //}

    //if ( procInfo.hProcess != NULL )
    //{
    //    TerminateProcess( procInfo.hProcess, MAXINT );
    //    CloseHandle( procInfo.hProcess );
    //}

    if ( proc != NULL )
        proc->Release();

    return 0;
}