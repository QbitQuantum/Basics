  void EventTCPSocket::connect( const wstring& host,
  const wstring& service, Protocol protocol )
  {
    if ( mState != State_Closed )
      EXCEPT( L"Cannot connect, socket is not closed" );

    mState = State_Connecting;

    ADDRINFOW resolve;
    PADDRINFOW address = NULL;
    PADDRINFOW resolved = NULL;

    memset( &resolve, NULL, sizeof( ADDRINFOW ) );

    resolve.ai_family   = util::protocolToFamily( protocol );
    resolve.ai_socktype = SOCK_STREAM;
    resolve.ai_protocol = IPPROTO_TCP;

    if ( GetAddrInfoW( host.c_str(), service.c_str(), &resolve, &resolved ) )
    {
      mState = State_Closed;
      EXCEPT_WSA( L"Couldn't resolve" );
    }

    for ( address = resolved; address != nullptr; address = address->ai_next )
    {
      if ( address->ai_socktype != SOCK_STREAM || address->ai_protocol != IPPROTO_TCP )
        continue;

      mSocket = WSASocketW( address->ai_family, address->ai_socktype,
        address->ai_protocol, nullptr, 0,
        mOverlapped ? WSA_FLAG_OVERLAPPED : 0 );

      if ( mSocket == INVALID_SOCKET )
        continue;

      if ( !WSAConnect( mSocket, address->ai_addr, (int)address->ai_addrlen,
        nullptr, nullptr, nullptr, nullptr ) )
        break;

      closesocket( mSocket );
    }

    if ( address == nullptr )
    {
      mState = State_Closed;
      EXCEPT_WSA( L"Couldn't connect" );
    }

    mBound = true;
    
    mConnectionInfo.update( mSocket, false );
    mConnectionInfo.update( mSocket, true );

    if ( WSAEventSelect( mSocket, mNetworkEvent, FD_READ | FD_CLOSE ) == SOCKET_ERROR )
      EXCEPT_WSA( L"Couldn't select socket events" );

    mState = State_Connected;

    for ( SocketListener* listener : mListeners )
      if ( listener->connectCallback( this ) )
        break;
  }