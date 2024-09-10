HRESULT RemoteDebuggerProxy::Start()
{
    if ( mSessionGuid != GUID_NULL )
        return S_OK;

    HRESULT     hr = S_OK;
    GUID        sessionGuid = { 0 };
    wchar_t     sessionGuidStr[GUID_LENGTH + 1] = L"";
    int         ret = 0;

    hr = CoCreateGuid( &sessionGuid );
    if ( FAILED( hr ) )
        return hr;

    ret = StringFromGUID2( sessionGuid, sessionGuidStr, _countof( sessionGuidStr ) );
    _ASSERT( ret > 0 );
    if ( ret == 0 )
        return E_FAIL;

    mSessionGuid = sessionGuid;

    hr = StartAgent( sessionGuidStr );
    if ( FAILED( hr ) )
        return hr;

    hr = StartServer( sessionGuidStr );
    if ( FAILED( hr ) )
        return hr;

    SetRemoteEventCallback( this );
    hr = StartClient( sessionGuidStr, sessionGuid, mhContext );
    SetRemoteEventCallback( NULL );
    if ( FAILED( hr ) )
    {
        StopServer();
        return hr;
    }

    return S_OK;
}