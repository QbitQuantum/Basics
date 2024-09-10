///////////////////////////////////////////////////////////////////////////////
// Run
///////////////////////////////////////////////////////////////////////////////
// DESCRIPTION:
//      This function runs the main thread loop
//      this implementation can be overloaded.
//      This function calls CSocketComm::OnDataReceived() (Virtual Function)
// PARAMETERS:
// NOTES:
//      You should not wait on the thread to end in this function or overloads
///////////////////////////////////////////////////////////////////////////////
void CSocketComm::Run()
{
    stMessageProxy stMsgProxy;
    DWORD   dwBytes  = 0L;
    DWORD   dwTimeout = INFINITE;
    LPBYTE  lpData  = (LPBYTE)&stMsgProxy;
    DWORD   dwSize  = sizeof(stMsgProxy);

    bool bSmartAddressing = IsSmartAddressing();
    if ( !bSmartAddressing )
    {
        lpData = stMsgProxy.byData;
        dwSize = sizeof(stMsgProxy.byData);
    }

    // Should we run as server mode
    if (IsServer() && !bSmartAddressing)
    {
        if (!IsBroadcast())
        {
            SOCKET sock = (SOCKET) m_hComm;
            sock = WaitForConnection( sock );

            // Get new connection socket
            if (sock != INVALID_SOCKET)
            {
                ShutdownConnection( (SOCKET) m_hComm);
                m_hComm = (HANDLE) sock;
                OnEvent( EVT_CONSUCCESS, NULL ); // connect
            }
            else
            {
                // Do not send event if we are closing
                if (IsOpen())
                    OnEvent( EVT_CONFAILURE, NULL ); // wait fail
                return;
            }
        }
    }
    else
    {
        GetPeerName( stMsgProxy.address );
    }

    while( IsOpen() )
    {
        // Blocking mode: Wait for event
        dwBytes = ReadComm(lpData, dwSize, dwTimeout);

        // Error? - need to signal error
        if (dwBytes == (DWORD)-1L)
        {
            // Do not send event if we are closing
            if (IsOpen())
            {
                if ( bSmartAddressing )
                {
                    RemoveFromList( stMsgProxy.address );
                }
                OnEvent( EVT_CONDROP, &stMsgProxy.address ); // lost connection
            }

            // special case for UDP, alert about the event but do not stop
            if ( bSmartAddressing )
                continue;
            else
                break;
        }

        // Chars received?
        if ( bSmartAddressing && dwBytes == sizeof(SOCKADDR_IN))
        {
            OnEvent( EVT_ZEROLENGTH, NULL );
        }
        else if (dwBytes > 0L)
        {
            OnDataReceived( lpData, dwBytes);
        }

        //Sleep(0);
    }
}