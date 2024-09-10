int RtpCtrlThread::run() {
  Debug( 2, "Starting control thread %x on port %d", mRtpSource.getSsrc(), mRtpSource.getLocalCtrlPort() );
  SockAddrInet localAddr, remoteAddr;

  bool sendReports;
  UdpInetSocket rtpCtrlServer;
  if ( mRtpSource.getLocalHost() != "" ) {
    if ( !rtpCtrlServer.bind( mRtpSource.getLocalHost().c_str(), mRtpSource.getLocalCtrlPort() ) )
      Fatal( "Failed to bind RTCP server" );
    sendReports = false;
    Debug( 3, "Bound to %s:%d",  mRtpSource.getLocalHost().c_str(), mRtpSource.getLocalCtrlPort() );
  } else {
    if ( !rtpCtrlServer.bind( mRtspThread.getAddressFamily() == AF_INET6 ? "::" : "0.0.0.0", mRtpSource.getLocalCtrlPort() ) )
      Fatal( "Failed to bind RTCP server" );
    Debug( 3, "Bound to %s:%d",  mRtpSource.getLocalHost().c_str(), mRtpSource.getLocalCtrlPort() );
    if ( !rtpCtrlServer.connect( mRtpSource.getRemoteHost().c_str(), mRtpSource.getRemoteCtrlPort() ) )
      Fatal( "Failed to connect RTCP server" );
    Debug( 3, "Connected to %s:%d",  mRtpSource.getRemoteHost().c_str(), mRtpSource.getRemoteCtrlPort() );
    sendReports = true;
  }

  // The only reason I can think of why we would have a timeout period is so that we can regularly send RR packets.
  // Why 10 seconds? If anything I think this should be whatever timeout value was given in the DESCRIBE response
  Select select( 10 );
  select.addReader( &rtpCtrlServer );

  unsigned char buffer[ZM_NETWORK_BUFSIZ];

  time_t  last_receive = time(NULL);
  bool  timeout = false; // used as a flag that we had a timeout, and then sent an RR to see if we wake back up. Real timeout will happen when this is true.

  while ( !mStop && select.wait() >= 0 ) {

    time_t now = time(NULL);
    Select::CommsList readable = select.getReadable();
    if ( readable.size() == 0 ) {
      if ( ! timeout ) {
        // With this code here, we will send an SDES and RR packet every 10 seconds
        ssize_t nBytes;
        unsigned char *bufferPtr = buffer;
        bufferPtr += generateRr( bufferPtr, sizeof(buffer)-(bufferPtr-buffer) );
        bufferPtr += generateSdes( bufferPtr, sizeof(buffer)-(bufferPtr-buffer) );
        Debug( 3, "Preventing timeout by sending %zd bytes on sd %d. Time since last receive: %d",
            bufferPtr-buffer, rtpCtrlServer.getWriteDesc(), ( now-last_receive) );
        if ( (nBytes = rtpCtrlServer.send(buffer, bufferPtr-buffer)) < 0 )
          Error("Unable to send: %s", strerror(errno));
        timeout = true;
        continue;
      } else {
        //Error( "RTCP timed out" );
        Debug(1, "RTCP timed out. Time since last receive: %d", ( now-last_receive) );
        continue;
        //break;
      }
    } else {
      timeout = false;
      last_receive = time(NULL);
    }
    for ( Select::CommsList::iterator iter = readable.begin(); iter != readable.end(); ++iter ) {
      if ( UdpInetSocket *socket = dynamic_cast<UdpInetSocket *>(*iter) ) {
        ssize_t nBytes = socket->recv( buffer, sizeof(buffer) );
        Debug( 4, "Read %zd bytes on sd %d", nBytes, socket->getReadDesc() );

        if ( nBytes ) {
          recvPackets( buffer, nBytes );

          if ( sendReports ) {
            unsigned char *bufferPtr = buffer;
            bufferPtr += generateRr( bufferPtr, sizeof(buffer)-(bufferPtr-buffer) );
            bufferPtr += generateSdes( bufferPtr, sizeof(buffer)-(bufferPtr-buffer) );
            Debug(3, "Sending %zd bytes on sd %d", bufferPtr-buffer, rtpCtrlServer.getWriteDesc());
            if ( (nBytes = rtpCtrlServer.send( buffer, bufferPtr-buffer )) < 0 )
              Error("Unable to send: %s", strerror(errno));
            //Debug( 4, "Sent %d bytes on sd %d", nBytes, rtpCtrlServer.getWriteDesc() );
          }
        } else {
          // Here is another case of not receiving some data causing us to terminate... why?  Sometimes there are pauses in the interwebs.
          mStop = true;
          break;
        }
      } else {
        Panic("Barfed");
      } // end if socket
    } // end foeach comms iterator
  }
  rtpCtrlServer.close();
  mRtspThread.stop();
  return 0;
}