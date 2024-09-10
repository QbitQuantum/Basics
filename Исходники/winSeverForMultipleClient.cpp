int main()
{
	// build a semaphore so we can synchronize the access to std cout
	// also includes the log file
	mySemaphore coutSemaphore(string(""),1);

	// Initialize the winsock library
	myTcpSocket::initialize();

	// create the server: local host will be used as the server, let us 
	// first use myHostInfo class to show the name and IP address 
	// of the local host
	winLog << endl;
	winLog << "Retrieve the local host name and address:" << endl;
	
    myHostInfo serverInfo;
	string serverName = serverInfo.getHostName();
    string serverIPAddress = serverInfo.getHostIPAddress();
	cout << "my localhost (server) information:" << endl;
	cout << "	Name:    " << serverName << endl;
    cout << "	Address: " << serverIPAddress << endl;
	winLog << "		==> Name: " << serverName << endl;
	winLog << "		==> Address: " << serverIPAddress << endl;

	// open socket on the local host(server) and show its configuration
	myTcpSocket myServer(PORTNUM);
	cout   << myServer;
	winLog << myServer;

	// create a thread to implement server process: listening to the socket,
	// accepting client calls and communicating with clients. This will free the 
	// main control (see below) to do other process.
	myThreadArgument* serverArgument = new myThreadArgument(&myServer,&coutSemaphore,serverName);
	myThread* serverThread = new myThread(serverHandleThread,(void*)serverArgument);
	serverThread->execute();

	// main control: since the serverThread is handling the server functions,
	// this main control is free to do other things.
	while ( 1 )
	{
		// do whatever you need to do here, I am using Sleep(x) 
		// to make a little delay, pretending to be the other 
		// possible processings.
		Sleep(50000);

		// report the server status
		coutSemaphore.lock();
		cout   << endl << "-----------------------------------------------------------------" << endl;
		winLog << endl << "-----------------------------------------------------------------" << endl;
		cout   << "server (name:" << serverName << ") status report:" << endl;
		winLog << "server (name:" << serverName << ") status report:" << endl;
		cout   << "   the following clients have successfully connected with server: " << endl;
		winLog << "   the following clients have successfully connected with server: " << endl;
		for ( int i = 0; i < MAX_NUM_CLIENTS; i ++ )
		{
			myThreadArgument* clientInfo = serverArgument->getClientArgument(i);
			if ( clientInfo ) 
			{
				cout   << "         " << clientInfo->getHostName() << endl;
				winLog << "         " << clientInfo->getHostName() << endl;
			}
		}
		cout   << "   the following clients have shutdown the connection: " << endl;
		winLog << "   the following clients have shutdown the connection: " << endl;
		for ( i = 0; i < MAX_NUM_CLIENTS; i ++ )
		{
			myThreadArgument* clientInfo = serverArgument->getClientArgument(i);
			if ( clientInfo && clientInfo->getExitEvent()->waitForEvent(0) )
			{
				clientInfo->setSignalToEnd(true);
				cout   << "         " << clientInfo->getHostName() << endl;
				winLog << "         " << clientInfo->getHostName() << endl;
			}
		}
        cout   << "-----------------------------------------------------------------" << endl << endl;
		winLog << "-----------------------------------------------------------------" << endl << endl;
		coutSemaphore.unlock();
	}

    return 1;
}