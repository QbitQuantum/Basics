int RtpDataThread::run()
{
  Debug( 2, "Starting data thread %d on port %d", mRtpSource.getSsrc(), mRtpSource.getLocalDataPort() );

  SockAddrInet localAddr;
  UdpInetServer rtpDataSocket;
  if ( mRtpSource.getLocalHost() != "" ) {
    if ( !rtpDataSocket.bind( mRtpSource.getLocalHost().c_str(), mRtpSource.getLocalDataPort() ) )
      Fatal( "Failed to bind RTP server" );
    Debug( 3, "Bound to %s:%d",  mRtpSource.getLocalHost().c_str(), mRtpSource.getLocalDataPort() );
  }
  else
  {
    if ( !rtpDataSocket.bind( mRtspThread.getAddressFamily() == AF_INET6 ? "::" : "0.0.0.0", mRtpSource.getLocalDataPort() ) )
      Fatal( "Failed to bind RTP server" );
    Debug( 3, "Bound to %s:%d",  mRtpSource.getLocalHost().c_str(), mRtpSource.getLocalDataPort() );
  }

  Select select( 3 );
  select.addReader( &rtpDataSocket );

  unsigned char buffer[ZM_NETWORK_BUFSIZ];
  while ( !mStop && select.wait() >= 0 )
  {
     if ( mStop )
      break;
     Select::CommsList readable = select.getReadable();
     if ( readable.size() == 0 )
     {
       Error( "RTP timed out" );
       mStop = true;
       break;
     }
     for ( Select::CommsList::iterator iter = readable.begin(); iter != readable.end(); iter++ )
     {
       if ( UdpInetServer *socket = dynamic_cast<UdpInetServer *>(*iter) )
       {
         int nBytes = socket->recv( buffer, sizeof(buffer) );
         Debug( 4, "Got %d bytes on sd %d", nBytes, socket->getReadDesc() );
         if ( nBytes )
         {
            recvPacket( buffer, nBytes );
         }
         else
         {
          mStop = true;
          break;
         }
       }
       else
       {
         Panic( "Barfed" );
       }
     }
  }
  rtpDataSocket.close();
  mRtspThread.stop();
  return( 0 );
}