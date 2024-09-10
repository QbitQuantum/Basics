TBool CSmsReplyToStep::WatchersAlreadyRunningL()
	{
	RSocketServ server;
	RSocket socket;

	User::LeaveIfError(server.Connect());
	CleanupClosePushL(server);

		// test if it's there... 
	TProtocolDesc protoInfo;
	TProtocolName protocolname;
	protocolname.Copy(KSmsDatagram);
	User::LeaveIfError(server.FindProtocol(protocolname,protoInfo));

	User::LeaveIfError(socket.Open(server,
										protoInfo.iAddrFamily,
										protoInfo.iSockType, 
										protoInfo.iProtocol));
	CleanupClosePushL(socket);
	

	TSmsAddr addr;
	addr.SetSmsAddrFamily(ESmsAddrRecvAny);
	TInt err = socket.Bind(addr);

	CleanupStack::Pop(2, &server);
	socket.CancelAll();
	socket.Close();
	server.Close();
	return (err == KErrAlreadyExists);
	}