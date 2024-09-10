    RunMode EventCallback::OnException( 
        DWORD uniquePid, DWORD threadId, bool firstChance, const EXCEPTION_RECORD64* exceptRec )
    {
        const DWORD DefaultState = EXCEPTION_STOP_SECOND_CHANCE;

        OutputDebugStringA( "EventCallback::OnException\n" );

        HRESULT     hr = S_OK;
        RefPtr<ExceptionEvent>      event;
        RefPtr<Program>             prog;
        RefPtr<Thread>              thread;

        if ( !mEngine->FindProgram( uniquePid, prog ) )
            return RunMode_Break;

        if ( !prog->FindThread( threadId, thread ) )
            return RunMode_Break;

        prog->NotifyException( firstChance, exceptRec );

        hr = MakeCComObject( event );
        if ( FAILED( hr ) )
            return RunMode_Break;

        event->Init( prog.Get(), firstChance, exceptRec, prog->CanPassExceptionToDebuggee() );

        DWORD state = DefaultState;
        ExceptionInfo info;
        bool found = false;

        if ( event->GetSearchKey() == ExceptionEvent::Name )
        {
            found = mEngine->FindExceptionInfo( event->GetGUID(), event->GetExceptionName(), info );
        }
        else // search by code
        {
            found = mEngine->FindExceptionInfo( event->GetGUID(), event->GetCode(), info );
        }

        // if not found, then check against the catch-all entry
        if ( !found )
            found = mEngine->FindExceptionInfo( event->GetGUID(), event->GetRootExceptionName(), info );

        if ( found )
        {
            if ( event->GetSearchKey() == ExceptionEvent::Code )
            {
                wchar_t name[256] = L"";
                _swprintf_p( name, _countof( name ), L"0x%08x: %s", event->GetCode(), (BSTR) info.bstrExceptionName );
                event->SetExceptionName( name );
            }
            state = info.dwState;
        }

        if ( (  firstChance && ( state & EXCEPTION_STOP_FIRST_CHANCE ) ) ||
             ( !firstChance && ( state & EXCEPTION_STOP_SECOND_CHANCE ) ) )
        {
            hr = SendEvent( event.Get(), prog.Get(), thread.Get() );
            return RunMode_Break;
        }
        else
        {
            RefPtr<MessageTextEvent>    msgEvent;
            CComBSTR                    desc;

            hr = MakeCComObject( msgEvent );
            if ( FAILED( hr ) )
                return RunMode_Run;

            hr = event->GetExceptionDescription( &desc );
            if ( FAILED( hr ) )
                return RunMode_Run;

            desc.Append( L"\n" );

            msgEvent->Init( MT_REASON_EXCEPTION, desc );

            hr = SendEvent( msgEvent.Get(), prog.Get(), thread.Get() );
            return RunMode_Run;
        }
    }