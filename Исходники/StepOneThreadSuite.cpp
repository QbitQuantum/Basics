void StepOneThreadSuite::RunDebuggee( Step* steps, int stepsCount )
{
    Exec    exec;

    TEST_ASSERT_RETURN( SUCCEEDED( exec.Init( mCallback ) ) );

    LaunchInfo  info = { 0 };
    wchar_t     cmdLine[ MAX_PATH ] = L"";
    IProcess*   proc = NULL;
    const wchar_t*  Debuggee = StepOneThreadDebuggee;

    swprintf_s( cmdLine, L"\"%s\" 1", Debuggee );

    info.CommandLine = cmdLine;
    info.Exe = Debuggee;

    TEST_ASSERT_RETURN( SUCCEEDED( exec.Launch( &info, proc ) ) );

    uint32_t            pid = proc->GetId();
    int                 nextStep = 0;
    char                msg[1024] = "";
    RefPtr<IProcess>    process;

    process = proc;
    proc->Release();
    mCallback->SetTrackLastEvent( true );

    for ( int i = 0; !mCallback->GetProcessExited(); i++ )
    {
        bool    continued = false;
        HRESULT hr = exec.WaitForEvent( DefaultTimeoutMillis );

        // this should happen after process exit
        if ( hr == E_TIMEOUT )
            break;

        TEST_ASSERT_RETURN( SUCCEEDED( hr ) );
        TEST_ASSERT_RETURN( SUCCEEDED( hr = exec.DispatchEvent() ) );

        if ( !process->IsStopped() )
            continue;

        if ( (mCallback->GetLastEvent()->Code != ExecEvent_ModuleLoad)
            && (mCallback->GetLastEvent()->Code != ExecEvent_ModuleUnload)
            && (mCallback->GetLastEvent()->Code != ExecEvent_ThreadStart)
            && (mCallback->GetLastEvent()->Code != ExecEvent_ThreadExit)
            && (mCallback->GetLastEvent()->Code != ExecEvent_LoadComplete) )
        {
            Step*   curStep = &steps[nextStep];
            nextStep++;

            RefPtr<Thread>  thread;
            CONTEXT_X86     context = { 0 };
            if ( mCallback->GetLastThreadId() != 0 )
            {
                TEST_ASSERT_RETURN( process->FindThread( mCallback->GetLastThreadId(), thread.Ref() ) );
                TEST_ASSERT_RETURN( exec.GetThreadContext( 
                    process, thread->GetId(), CONTEXT_X86_FULL, 0, &context, sizeof context ) == S_OK );
            }

            uintptr_t   baseAddr = 0;
            RefPtr<IModule> procMod = mCallback->GetProcessModule();
            if ( procMod.Get() != NULL )
                baseAddr = (uintptr_t) procMod->GetImageBase();

            // TODO: test threadId

            if ( mCallback->GetLastEvent()->Code != curStep->Event.Code )
            {
                sprintf_s( msg, "Expected event '%s', got '%s'.", 
                    GetEventName( curStep->Event.Code ),
                    GetEventName( mCallback->GetLastEvent()->Code ) );
                TEST_FAIL_MSG( msg );
                break;
            }
            else if ( (curStep->Event.Code == ExecEvent_Exception)
                && (curStep->Event.ExceptionCode != ((ExceptionEventNode*) mCallback->GetLastEvent().get())->Exception.ExceptionCode) )
            {
                sprintf_s( msg, "Expected exception %08x, got %08x.", 
                    curStep->Event.ExceptionCode, 
                    ((ExceptionEventNode*) mCallback->GetLastEvent().get())->Exception.ExceptionCode );
                TEST_FAIL_MSG( msg );
                break;
            }
            else if ( (curStep->Event.Code == ExecEvent_Exception)
                || (curStep->Event.Code == ExecEvent_StepComplete) 
                || (curStep->Event.Code == ExecEvent_Breakpoint) )
            {
                uintptr_t   addr = (curStep->Event.AddressOffset + baseAddr);

                if ( context.Eip != addr )
                {
                    sprintf_s( msg, "Expected instruction pointer at %p, got %08x.", addr, context.Eip );
                    TEST_FAIL_MSG( msg );
                    break;
                }
            }

            mCallback->SetCanStepInFunctionReturnValue( curStep->Action.CanStepInFunction );

            if ( curStep->Action.BPAddressOffset != 0 )
            {
                uintptr_t   addr = (curStep->Action.BPAddressOffset + baseAddr);
                TEST_ASSERT_RETURN( SUCCEEDED( exec.SetBreakpoint( process.Get(), addr ) ) );
            }

            if ( curStep->Action.Action == Action_StepInstruction )
            {
                TEST_ASSERT_RETURN( SUCCEEDED( 
                    exec.StepInstruction( process.Get(), curStep->Action.StepIn, true ) ) );
                continued = true;
            }
            else if ( curStep->Action.Action == Action_StepRange )
            {
                AddressRange range = { context.Eip, context.Eip };
                TEST_ASSERT_RETURN( SUCCEEDED( 
                    exec.StepRange( process.Get(), curStep->Action.StepIn, range, true ) ) );
                continued = true;
            }
        }

        if ( !continued )
            TEST_ASSERT_RETURN( SUCCEEDED( exec.Continue( process, true ) ) );
    }

    TEST_ASSERT( mCallback->GetLoadCompleted() );
    TEST_ASSERT( mCallback->GetProcessExited() );
}