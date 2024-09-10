  void TCPSocket::bind( const wstring& host, const wstring& service,
  Protocol protocol )
  {
    if ( mState != State_Closed )
      EXCEPT( L"Cannot bind, socket is not closed" );

    ADDRINFOW resolve;
    PADDRINFOW address = nullptr;
    PADDRINFOW resolved = nullptr;

    memset( &resolve, 0, sizeof( ADDRINFOW ) );

    resolve.ai_family   = util::protocolToFamily( protocol );
    resolve.ai_socktype = SOCK_STREAM;
    resolve.ai_protocol = IPPROTO_TCP;

    if ( GetAddrInfoW( host.c_str(), service.c_str(), &resolve, &resolved ) )
      EXCEPT_WSA( L"Couldn't resolve" );

    for ( address = resolved; address != nullptr; address = address->ai_next )
    {
      if ( address->ai_socktype != SOCK_STREAM || address->ai_protocol != IPPROTO_TCP )
        continue;

      mSocket = WSASocketW(
        address->ai_family, address->ai_socktype, address->ai_protocol,
        nullptr, 0, mOverlapped ? WSA_FLAG_OVERLAPPED : 0 );

      if ( mSocket == INVALID_SOCKET )
        continue;

      if ( ::bind( mSocket, address->ai_addr, (int)address->ai_addrlen ) != SOCKET_ERROR )
        break;

      closesocket( mSocket );
    }

    if ( address == nullptr )
      EXCEPT_WSA( L"Couldn't bind" );

    mBound = true;

    mConnectionInfo.update( mSocket, false );
  }