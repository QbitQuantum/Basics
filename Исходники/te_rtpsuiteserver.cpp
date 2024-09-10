void CTe_rtpSuite::ConfigureReflectorModeL(TBool aMode, TInetAddr& aAddr)
	{
    /* Configures the reflector to change the SSRC or not
     */	
	RSocketServ sockServer;
	//Open a connection
	RConnection conn;
	User::LeaveIfError(sockServer.Connect());
	CleanupClosePushL(sockServer);
	
	User::LeaveIfError(conn.Open(sockServer));
	CleanupClosePushL(conn);
	
	//Start the connection
	User::LeaveIfError(conn.Start());
	
	RSocket ctrlSock;
	User::LeaveIfError(ctrlSock.Open(sockServer,KAfInet, KSockDatagram, KProtocolInetUdp, conn));
	CleanupClosePushL(ctrlSock);
	
    TBuf8<64> lCmdBuff;
    TUint8* lPtr = const_cast<TUint8*>(lCmdBuff.Ptr());
    TUint32* lIntData = (TUint32*)lPtr;
    *lIntData = ByteOrder::Swap32(0xFF00BABE);
    if (aMode)
    	{
    	*(lIntData + 1) = ByteOrder::Swap32(0xCD000100);
    	}
    else
    	{
    	*(lIntData + 1) = ByteOrder::Swap32(0xCD000101);
    	}
    lCmdBuff.SetLength(64);
    
    TRequestStatus lMyReqStat;
    ctrlSock.SendTo(lCmdBuff,aAddr,0,lMyReqStat);
    User::WaitForRequest(lMyReqStat);
    
    ctrlSock.Close();
    conn.Close();
    sockServer.Close();
    
    CleanupStack::Pop(3);
	}