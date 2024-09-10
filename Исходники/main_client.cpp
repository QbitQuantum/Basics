int main( int argc, char* argv[])
{

	// create the context on the stack
	Context ct;

	// get the input, exit if failure
	if( !GetInput(&ct, argc, argv) )
		return 0;

	// init the context
	ct.Init();

	// set the run state
	ct.m_Running = true;

	// create the input thread
	ct.MakeThread(InputThread);

	// check the mode
	if( ct.m_Mode == 1 )
	{
		// create the server
		ct.MakeThread(ListenThread);
	}

	// some variables for sockets
	int sockfd;
	struct sockaddr_in saLoc;
	bool success = true;

	// lets do some socket creation (for the client)
	if( ct.m_Mode == 2 )
	{
		// place this in a for loop to create a breakable scope
		for(int dum = 0; dum < 1; dum++)
		{
			//Create a reliable, stream socket using TCP
			if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
			{
				LogMsgToTerminal("ERROR CREATING SOCKET");
				success = false;
				break;
			}

			// Local
			int yes = 1;
			memset(&saLoc, 0, sizeof(struct sockaddr_in));
			saLoc.sin_family = AF_INET; // Internet address family
			saLoc.sin_port = htons(ct.m_SPort); // the local port
			saLoc.sin_addr.s_addr = inet_addr("127.0.0.1"); // the local IP Addr

			// let the kernel know we are willing to reuse the socket if still around
			setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

			if( bind(sockfd, (struct sockaddr *)&saLoc, sizeof(struct sockaddr)) < 0 )
			{
				LogMsgToTerminal("ERROR BINDING SOCKET");
				success = false;
				close(sockfd);
				break;
			}

			// set the destination parameters - the IP is already set
			ct.m_Sa.sin_family = AF_INET; // Internet address family
			ct.m_Sa.sin_port = htons(ct.m_DPort); // Server port
		
			LogMsgToTerminal("ATTEMPTING TO CONNECT");
			if (connect(sockfd, (struct sockaddr*) &(ct.m_Sa),sizeof(ct.m_Sa)) < 0)
			{
				LogMsgToTerminal("ERROR CONNECTING");
				success = false;
				break;
			}
			else
			{
				LogMsgToTerminal("SUCCESSFULL CONNECTION");
				// set the socket to non-blocking
				// and create the recv thread
				struct timeval timeout;
                timeout.tv_sec = 10;
                timeout.tv_usec = 0;

                setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
                setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));

                // now lets add the new socket
				LocalContext* newCT = ct.MakeThread(RecvThread);
				newCT->m_Sockfd = sockfd;

			}
		}
	}

	

	// start the loop
	pthread_mutex_lock(&(ct.m_PollMutex));
	while(ct.m_Running)
	{
		// wait on the condition
		pthread_cond_wait(&(ct.m_PollCondition), &(ct.m_PollMutex));

		// access the thread context
		LocalContext* tLct = ct.FindThread( ct.m_Caller );

		if( tLct == NULL )
			continue; // no thread context...

		// do work
		stringstream ss;
		// check the caller
		if( ct.m_Caller == 1 )
		{
			// the input thread
			// switch on mode
			switch( ct.m_Mode )
			{
			case 1: // server
				
				// broadcast to all recv threads
				ss << ct.m_DPort << ": " << tLct->m_MSG;
				ct.BroadcastAll( ss.str() );

				break;
			case 2: // client
				
				// simple: broadcast the input thread string to the server
				// make sure we have a valid connection, and 
				// this was not an exit command
				if( success && ct.m_Running ) 				
				{
					// send the message
					LogMsgToTerminal( tLct->m_MSG );
					size_t sent = send( sockfd, tLct->m_MSG.c_str(), tLct->m_MSG.length(), 0 );
										
				}
				break;
			}

		}
		else
		{
			// the recv threads
			
			// switch on mode
			switch( ct.m_Mode )
			{
			case 1: // server
				
				// log the message and transmit
				ss << GetPortFromStruct( &(tLct->m_Addr) );
				ss << ": " << tLct->m_MSG;

				LogMsgToTerminal(ss.str());
				ct.BroadcastAll( ss.str(), ct.m_Caller );
				break;

			case 2: // client
				// simply log the message to the screen

				LogMsgToTerminal(tLct->m_MSG);
				break;
			}
		}


	}	
	pthread_mutex_unlock(&(ct.m_PollMutex));

	// clean up the socket
	if( ct.m_Mode == 2 )
	{
		if( success )
		{
			close(sockfd);
		}
	}	

	// destroy and join the threads
	ct.DestroyAllThreads();
		
	// shut down the context
	ct.Shutdown();

	return 0;
}