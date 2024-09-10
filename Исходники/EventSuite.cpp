void EventSuite::TestExceptionNotHandledFirstChanceCaught()
{
    enum State
    {
        State_Init,
        State_FirstNotHandled,
        State_Done
    };

    Exec    exec;
    State   state = State_Init;

    TEST_ASSERT_RETURN( SUCCEEDED( exec.Init( mCallback ) ) );

    LaunchInfo      info = { 0 };
    wchar_t         cmdLine[ MAX_PATH ] = L"";
    IProcess*       proc = NULL;
    const wchar_t*  Debuggee = EventsDebuggee;

    swprintf_s( cmdLine, L"\"%s\" exception 2", Debuggee );

    info.CommandLine = cmdLine;
    info.Exe = Debuggee;

    TEST_ASSERT_RETURN( SUCCEEDED( exec.Launch( &info, proc ) ) );

    uint32_t    pid = proc->GetId();
    RefPtr<IProcess>    process( proc );

    proc->Release();
    mCallback->SetTrackLastEvent( true );

    for ( int i = 0; !mCallback->GetProcessExited(); i++ )
    {
        bool    handled = true;

        HRESULT hr = exec.WaitForEvent( DefaultTimeoutMillis );

        // this should happen after process exit
        if ( hr == E_TIMEOUT )
            break;

        TEST_ASSERT_RETURN( SUCCEEDED( hr ) );
        TEST_ASSERT_RETURN( SUCCEEDED( exec.DispatchEvent() ) );

        if ( process->IsStopped() )
        {
            if ( (mCallback->GetLastEvent().get() != NULL) 
                && (mCallback->GetLastEvent()->Code == ExecEvent_Exception) )
            {
                ExceptionEventNode* node = (ExceptionEventNode*) mCallback->GetLastEvent().get();

                TEST_ASSERT( node->FirstChance );

                if ( node->Exception.ExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO )
                {
                    if ( state == State_Init )
                    {
                        state = State_FirstNotHandled;
                        handled = false;
                    }
                    else
                    {
                        TEST_FAIL( "Too many Integer divides by zero." );
                        exec.Terminate( process.Get() );
                    }
                }
                else
                {
                    TEST_FAIL( "Unexpected exception." );
                    exec.Terminate( process.Get() );
                }
            }
            else if ( (mCallback->GetLastEvent().get() != NULL) 
                && (mCallback->GetLastEvent()->Code == ExecEvent_Breakpoint)
                && (state == State_FirstNotHandled) )
            {
                state = State_Done;

                CONTEXT_X86     context = { 0 };
                RefPtr<Thread>  thread;

                TEST_ASSERT_RETURN( process->FindThread( mCallback->GetLastThreadId(), thread.Ref() ) );
                context.ContextFlags = CONTEXT_X86_FULL;
                TEST_ASSERT_RETURN( GetThreadContextX86( thread->GetHandle(), &context ) );
                TEST_ASSERT( context.Eax == 1877514773 );
            }

            TEST_ASSERT_RETURN( SUCCEEDED( exec.Continue( process, handled ) ) );
        }
    }

    TEST_ASSERT( mCallback->GetLoadCompleted() );
    TEST_ASSERT( mCallback->GetProcessExited() );

    TEST_ASSERT( state == State_Done );
}