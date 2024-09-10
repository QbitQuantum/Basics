void SocketConnection::acceptNB()
{
    LBASSERT( isListening() );

    // Create new accept socket
    const DWORD flags = WSA_FLAG_OVERLAPPED;

    LBASSERT( _overlappedAcceptData );
    LBASSERT( _overlappedSocket == INVALID_SOCKET );
    _overlappedSocket = WSASocketW( AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0,
                                    flags );

    if( _overlappedSocket == INVALID_SOCKET )
    {
        LBERROR << "Could not create accept socket: " << lunchbox::sysError
                << ", closing listening socket" << std::endl;
        close();
        return;
    }

    const int on = 1;
    setsockopt( _overlappedSocket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
        reinterpret_cast<const char*>( &on ), sizeof( on ));

    // Start accept
    ResetEvent( _overlappedRead.hEvent );
    DWORD got;
    if( !AcceptEx( _readFD, _overlappedSocket, _overlappedAcceptData, 0,
                   sizeof( sockaddr_in ) + 16, sizeof( sockaddr_in ) + 16,
                   &got, &_overlappedRead ) &&
        GetLastError() != WSA_IO_PENDING )
    {
        LBERROR << "Could not start accept operation: "
                << lunchbox::sysError << ", closing connection" << std::endl;
        close();
    }
}