ConnectionPtr PGMConnection::acceptSync()
{
    EQ_TS_THREAD( _recvThread );
    if( _state != STATE_LISTENING )
        return 0;

    EQASSERT( _overlappedAcceptData );
    EQASSERT( _overlappedSocket != INVALID_SOCKET );
    if( _overlappedSocket == INVALID_SOCKET )
        return 0;

    // complete accept
    DWORD got   = 0;
    DWORD flags = 0;
    if( !WSAGetOverlappedResult( _readFD, &_overlapped, &got, TRUE, &flags ))
    {
        EQWARN << "Accept completion failed: " << base::sysError 
               << ", closing connection" << std::endl;
        close();
        return 0;
    }

    sockaddr_in* local     = 0;
    sockaddr_in* remote    = 0;
    int          localLen  = 0;
    int          remoteLen = 0;
    GetAcceptExSockaddrs( _overlappedAcceptData, 0, sizeof( sockaddr_in ) + 16,
                          sizeof( sockaddr_in ) + 16, (sockaddr**)&local, 
                          &localLen, (sockaddr**)&remote, &remoteLen );

    PGMConnection* newConnection = new PGMConnection;
    ConnectionPtr connection( newConnection ); // to keep ref-counting correct

    newConnection->_readFD  = _overlappedSocket;
    _overlappedSocket       = INVALID_SOCKET;

    newConnection->_setupReadSocket();
    newConnection->_writeFD = _writeFD;
    newConnection->_initAIORead();
    newConnection->_state       = STATE_CONNECTED;
    newConnection->_description = _description;

    EQINFO << "accepted connection " << (void*)newConnection << " from " 
           << inet_ntoa( remote->sin_addr ) << ":" << ntohs( remote->sin_port )
           << std::endl;
    return connection;
}