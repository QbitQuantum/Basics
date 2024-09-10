unsigned long THREAD_FUNC SocketSubsystem::ListeningThread( void* Arg )
{
	SocketSubsystem* Subsystem = (SocketSubsystem*)Arg;

	ThreadStartupData StartupData;
	memset( &StartupData, 0, sizeof( StartupData ) );
	Subsystem->mListeningMutex.Aquire();
	Array<ThreadStartupData>& StartupDataList = Subsystem->mThreadStartupData;
	for( size_t i = 0; i < StartupDataList.Length(); ++i )
	{
		if( !StartupDataList[i].IsClaimed )
		{
			StartupDataList[i].IsClaimed = TRUE;
			StartupData = StartupDataList[i];
		}
	}
	Subsystem->mListeningMutex.Release();

	assert( StartupData.IsClaimed && StartupData.Socket != NULL && "Couldn't find startup data for socket listening thread" );

	Socket* ListeningSocket = StartupData.Socket;

	UBOOL ContinueListening = TRUE;
	while( ContinueListening && !fPendingDestroy )
	{
		// Blocking call
		ListeningSocket->Listen();
		
		// If we get here, we have gotten a new connection, accept it
		Socket* NewSocket = ListeningSocket->Accept();
		
		if( NewSocket != NULL && !fPendingDestroy )
		{
			Subsystem->mConnectionMutex.Aquire();
			Subsystem->mNewConnections.AddItem( NewSocket );
			Subsystem->mConnectionMutex.Release();
		}
		else if( NewSocket != NULL )
		{
			// CLEANUP, we allocated a socket while shutting down
			delete NewSocket;
		}

		Sleep( 10 );
	}

	return 0;
}