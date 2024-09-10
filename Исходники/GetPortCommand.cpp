void CGetPortCommand::DoExecuteL()
    {
	TInt errorCode = KErrNone;
	RSocketServ	socketServer;
	errorCode = socketServer.Connect();
	if(errorCode  == KErrNone)
		{
	    RSocket listeningSocket;
		TSockAddr localAddress;
		//TODO: add retrying to find ports
		for(int i = 0; errorCode == KErrNone && i < iFreePortsNum; i++)
			{
			TInt port = iDriver->NextRandomPort();
			listeningSocket.Open(socketServer, KAfInet, KSockStream, KProtocolInetTcp);
			localAddress.SetPort(port); 
			errorCode = listeningSocket.Bind(localAddress);
			if(errorCode == KErrNone)
				{
				iFreePorts.Append(port);
				}
			listeningSocket.Close();
			}
		}
	socketServer.Close();
	User::LeaveIfError(errorCode);
    }