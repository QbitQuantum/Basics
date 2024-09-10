TBool TestFrameworkActionsUtils::CheckIfSmsWatcherAlreadyRunningL()
	{
	RSocketServ socketServer;
	RSocket socket;
	
	User::LeaveIfError(socketServer.Connect());
	CleanupClosePushL(socketServer);

	TProtocolDesc protoInfo;
	TProtocolName protocolname;
	protocolname.Copy(KSmsDatagram);
	User::LeaveIfError(socketServer.FindProtocol(protocolname,protoInfo));
	User::LeaveIfError(socket.Open(socketServer,
										protoInfo.iAddrFamily,
										protoInfo.iSockType, 
										protoInfo.iProtocol));

	CleanupClosePushL(socket);
	
	TSmsAddr addr;
	addr.SetSmsAddrFamily(ESmsAddrRecvAny);
	TInt err = socket.Bind(addr);
	
	socket.CancelAll();
	CleanupStack::PopAndDestroy(2); //socketServer, socket
		
	return (err == KErrAlreadyExists);
	}