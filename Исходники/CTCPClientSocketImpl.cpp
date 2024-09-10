bool CTCPClientSocketImpl::Connect ( const char* szHost, unsigned short usPort )
{
    // Save the port
    m_usPort = usPort;

    // If we're already connected, disconnect
    if ( m_bIsConnected )
    {
        Disconnect ();
    }

    // If we have active host resolving, cancel it
    if ( m_bIsResolvingHost )
    {
        WSACancelAsyncRequest ( m_pAsyncHostResolving );
    }

    // Got a socket?
    if ( !m_Socket )
    {
        // No socket
        strcpy ( m_szLastError, "No socket initialized" );
        return false;
    }

    // Start async resolving it
    m_pAsyncHostResolving = WSAAsyncGetHostByName ( CCore::GetSingleton ().GetHookedWindow (), WM_ASYNCTRAP + m_uiID + 256, szHost, m_pHostInfo, MAXGETHOSTSTRUCT );
    if ( !m_pAsyncHostResolving )
    {
        // Failed
        strcpy ( m_szLastError, "Unable to start resolving" );
        return false;
    }
    m_bIsResolvingHost = true;
    return true;
}