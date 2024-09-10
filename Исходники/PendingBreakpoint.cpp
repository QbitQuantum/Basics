    HRESULT PendingBreakpoint::SendBoundEvent( IEnumDebugBoundBreakpoints2* enumBPs )
    {
        HRESULT hr = S_OK;
        CComPtr<IDebugPendingBreakpoint2>       pendBP;
        CComPtr<IDebugEngine2>                  engine;
        RefPtr<BreakpointBoundEvent>            event;

        hr = QueryInterface( __uuidof( IDebugPendingBreakpoint2 ), (void**) &pendBP );
        _ASSERT( hr == S_OK );

        hr = mEngine->QueryInterface( __uuidof( IDebugEngine2 ), (void**) &engine );
        _ASSERT( hr == S_OK );

        hr = MakeCComObject( event );
        if ( FAILED( hr ) )
            return hr;

        event->Init( enumBPs, pendBP );

        return event->Send( mCallback, engine, NULL, NULL );
    }