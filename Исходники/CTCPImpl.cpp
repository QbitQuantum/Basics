CTCPClientSocket* CTCPImpl::CreateClient ( void )
{
    // Create the socket and initialize it
    CTCPClientSocketImpl* pSocket = new CTCPClientSocketImpl;
    if ( !pSocket->Initialize () )
    {
        // Copy the error details, delete it and return NULL
        strcpy ( m_szLastError, pSocket->GetLastError () );
        delete pSocket;
        return 0;
    }

    // Return the socket we created
    return pSocket;
}