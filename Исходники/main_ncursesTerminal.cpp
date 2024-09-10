int main( int argc, char* argv[])
{


	// create the context on the stack
	Context ct;

	// init the context
	ct.Init();

	// set the run state
	ct.m_Running = true;

	// create the input thread
	ct.m_InputThread = ct.MakeThread(InputThread);
	ct.m_InputThread->m_Type = LocalContext::T_INPUT;

	bool success = true;

		
	// create the TCP thread
	ct.m_TCPThread = ct.MakeThread(TCPRecvThread);	
	ct.m_TCPThread->m_Sockfd = -1;
	ct.m_TCPThread->m_Type = LocalContext::T_TCP;
	ct.m_TCPThread->m_Mutex = ct.m_TCPMutex;
/*
	// create the UDP thread
	ct.m_TCPThread = ct.MakeThread(RecvThread);	
	ct.m_TCPThread->m_Sockfd = -1;
	ct.m_TCPThread->m_Type = LocalContext::T_TCP;

*/
	// create the TTY thread
	ct.m_TTYThread = ct.MakeThread(TTYRecvThread);	
	ct.m_TTYThread->m_Sockfd = -1;
	ct.m_TTYThread->m_Type = LocalContext::T_TTY;
	ct.m_TTYThread->m_Mutex = ct.m_TTYMutex;

	LogMsgToTerminal("INITIALIZATION COMPLETE");


	// start the loop
	pthread_mutex_lock(&(ct.m_PollMutex));
	while( ct.m_Running )
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
		if( ct.m_Caller == 1 )  // called from the input thread
		{
							
			// simple: broadcast the input thread string to the server
			// make sure we have a valid connection, and 
			// this was not an exit command
			if( success && ct.m_Running ) 				
			{
				// send the message
				//LogMsgToTerminal( tLct->m_MSG );
				//size_t sent = send( sockfd, tLct->m_MSG.c_str(), tLct->m_MSG.length(), 0 );
										
			}
			

		}
		else // called from recv thread
		{
			// the recv threads
			// simply log the message to the screen

			LogMsgToTerminal(tLct->m_MSG);
			
			
		}


	}
	
	pthread_mutex_unlock(&(ct.m_PollMutex));

	// clean up the socket
	if( (ct.m_TCPThread)->m_Sockfd >= 0 )
	{
		
		
		close((ct.m_TCPThread)->m_Sockfd);
		
	}	

	// destroy and join the threads
	ct.DestroyAllThreads();
		
	// shut down the context
	ct.Shutdown();

	return 0;
}