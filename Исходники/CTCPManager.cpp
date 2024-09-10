CTCPClientSocket* CTCPManager::CreateClient ( void )
{
    for ( unsigned int i = 0; i < 255; i++ )
    {
        // Check for an empty socket pointer slot
        if ( m_pSocket[i] == NULL )
        {
            // Create the socket and initialize it
            CTCPClientSocketImpl* pSocket = new CTCPClientSocketImpl;
            if ( !pSocket->Initialize ( i ) )
            {
                // Copy the error details, delete it and return NULL
                strcpy ( m_szLastError, pSocket->GetLastError () );
                SAFE_RELEASE ( pSocket )
                return NULL;
            }
            m_pSocket[i] = pSocket;
            return pSocket;
        }