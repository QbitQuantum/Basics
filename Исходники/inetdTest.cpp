// Main 
void MainL()
	{
	/* Inetd Setup 
	Create a inetd process 
	*/
	RProcess inetd;
	CleanupClosePushL(inetd);
	User::LeaveIfError(inetd.Create(_L("inetd"), _L("")));
	
	// Resume inetd
	inetd.Resume();
	
	// Wait for inetd to be ready
	console->Printf(_L("[ press any key ]"));
	console->Getch();	// Get and ignore character

	
	/* IPEcho Part 
	Connect to socket server 
	*/
	console->Printf(_L("Connect to socket server ... \n"));
	RSocketServ socketServ;
	CleanupClosePushL(socketServ);
	User::LeaveIfError(socketServ.Connect());
	
	// Open RConnection
	console->Printf(_L("Open RConnection ... \n"));
	RConnection connect;
	CleanupClosePushL(connect);
	User::LeaveIfError(connect.Open(socketServ, KConnectionTypeDefault));

	// Start RConnection
	console->Printf(_L("Start RConnection ... \n"));
	TCommDbConnPref prefs;
	prefs.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
	User::LeaveIfError(connect.Start(prefs));	// Handle options here like (ie: No Prompt)

	// Open RSocket
	console->Printf(_L("Open Socket ... \n"));
	RSocket sock;
	CleanupClosePushL(sock);
	User::LeaveIfError(sock.Open(socketServ, KAfInet, KSockStream, KProtocolInetTcp, connect));

	// Connect
	console->Printf(_L("Connect Socket ... \n"));
	TRequestStatus status;
	TInetAddr echoServAddr(KInetAddrLoop, 7);	// 7: TCP port 
	sock.Connect(echoServAddr, status);
	User::WaitForRequest(status);
	User::LeaveIfError(status.Int());

	// Wait for the socket transfer to be over 
	console->Printf(_L("[ press any key ]"));
	console->Getch();	// Get and ignore character
	
	// Send a packet
	console->Printf(_L("Send a packet ... \n"));
	HBufC8* packet = HBufC8::NewL(KSocketDefaultBufferSize);
	CleanupStack::PushL(packet);

	packet->Des().SetMax();
	packet->Des().FillZ();
	sock.Send(packet->Des(), 0, status);
	User::WaitForRequest(status);
	User::LeaveIfError(status.Int());
	
	// Receive it back
	console->Printf(_L("Received it back ... \n"));
	packet->Des().Zero();
	TPtr8 buff = packet->Des();
	sock.Recv(buff, 0, status);
	User::WaitForRequest(status);
	User::LeaveIfError(status.Int());

	
	// Terminates 
	console->Printf(_L("Terminates ... \n"));
	CleanupStack::PopAndDestroy(packet);
	CleanupStack::PopAndDestroy(&sock);
	CleanupStack::PopAndDestroy(&connect);
	CleanupStack::PopAndDestroy(&socketServ);
	CleanupStack::PopAndDestroy(&inetd);
	}