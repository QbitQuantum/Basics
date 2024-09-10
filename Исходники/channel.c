static HRESULT send_message( struct channel *channel, BYTE *data, ULONG len )
{
    if (!WinHttpSendRequest( channel->http_request, NULL, 0, data, len, len, 0 ))
        return HRESULT_FROM_WIN32( GetLastError() );

    if (!WinHttpReceiveResponse( channel->http_request, NULL ))
        return HRESULT_FROM_WIN32( GetLastError() );
    return S_OK;
}