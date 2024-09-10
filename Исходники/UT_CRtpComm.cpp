void UT_CRtpComm::UT_CRtpComm_SetToAddressL(  )
    {
    TCreateSessionParams params;
    TInt err( KErrNone );
    TInetAddr aRtpAddr;
    TInetAddr aRtcpAddr;
    iLocalPort = 7777; // this should be changed to an even number by CRtpComm
    
    /////////////////////////////////////////////////
    // This object will be destroyed below
    // It is used for testing construction without RTCP on an odd port
    TRAP( err, iRtpComm = CRtpComm::NewL( iLocalPort,
                               iSocketServ,
                               iConnection,
                               params,
                               *this,
                               EFalse ) );
                               
    RTP_EUNIT_ASSERT_EQUALS ( err, KErrNone );
        
    // Check some initial values
    if ( iLocalPort != 7776 ||
         iRtpComm->iSender[ERTPPort] != NULL ||
         iRtpComm->iSender[ERTCPPort] != NULL ||
         iRtpComm->iReceiver[ERTPPort] != NULL ||
         iRtpComm->iReceiver[ERTCPPort] != NULL )
        {
        EUNIT_ASSERT ( EFalse );
    
        }
    
    
    iLocalPort = 5000; // use default port 5000
  
    TInt result( KErrNone );
    TBuf8<5> sendBuf;
    TBuf8<5> recvBuf;

    // Test setting a port to an address
    
    // Run the method
    TInetAddr dummyAddr( INET_ADDR( 127, 0, 0, 1 ), 5050 );
    TInetAddr remoteAddr( INET_ADDR( 127, 0, 0, 1 ), 5000 );
    TInt error = iRtpComm->SetToAddress( ERTPPort, dummyAddr );
    EUNIT_ASSERT ( error == KErrNone )
    
    // Test writing synchronously to a port
    // Run the method
    
    //
	iRtpComm->ConstructSenderL(remoteAddr, dummyAddr);
	err = iRtpComm->Send( ERTPPort, sendBuf );
	DelayL();
	iRtpComm->CancelSend( ERTPPort );
	DelayL();
	 // Check the results
    RTP_EUNIT_ASSERT_EQUALS ( err, KErrNone );
        
    // Run the method
    TRequestStatus status;
    iRtpComm->Send( ERTPPort, sendBuf, status );
    EUNIT_ASSERT( KRequestPending == status.Int() );
    User::WaitForRequest( iRtpComm->iSender[ERTPPort]->iStatus );
    iRtpComm->iSender[ERTPPort]->RunL();
    iRtpComm->iSender[ERTPPort]->iStatus = TRequestStatus();
    User::WaitForRequest( status );
    
    // Check the results
    EUNIT_ASSERT ( status == KErrNone )
        
    // Run the method
    iRtpComm->CancelSend( ERTPPort );
	DelayL();
	
    // Can't verify success here   
    
    // Run the method
    iRtpComm->RegisterReceivedNotify( this );
    
  
    iRtpComm->ConstructReceiverL(EFalse);    
    // Can't verify success here   
    err = iRtpComm->Receive( ERTPPort, recvBuf );
	RTP_EUNIT_ASSERT_EQUALS ( err, KErrNone );
    
	err = iRtpComm->Send( ERTPPort, sendBuf );
	DelayL();
	iRtpComm->CancelSend( ERTPPort );
	DelayL();
    // Check the results
    RTP_EUNIT_ASSERT_EQUALS ( err, KErrNone );
    
    RSocket* socket( NULL );
    
    // Run the method
    socket = iRtpComm->GetSocket( ERTPPort );

    TProtocolDesc desc1, desc2;
    
    socket->Info( desc1 );
    iRtpComm->iSocket[ERTPPort].Info( desc2 );

    // The info should match
    if ( desc1.iAddrFamily != desc2.iAddrFamily ||
         desc1.iByteOrder != desc2.iByteOrder ||
         desc1.iMessageSize != desc2.iMessageSize ||
         desc1.iName != desc2.iName ||
         desc1.iNamingServices != desc2.iNamingServices ||
         desc1.iProtocol != desc2.iProtocol ||
         desc1.iSecurity != desc2.iSecurity ||
         desc1.iServiceInfo != desc2.iServiceInfo ||
         desc1.iSockType != desc2.iSockType )
        {
        EUNIT_ASSERT(EFalse);
        }
    }