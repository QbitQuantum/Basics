int SP_IocpLFServer :: run()
{
	int ret = 0;
	int listenFD = -1;

	ret = SP_IOUtils::tcpListen( mBindIP, mPort, &listenFD, 0 );

	if( 0 == ret ) {
		mCompletionHandler = mAcceptArg->mHandlerFactory->createCompletionHandler();

		SP_IocpMsgQueue * msgQueue = new SP_IocpMsgQueue( mEventArg->getCompletionPort(),
			SP_IocpEventCallback::eKeyMsgQueue, SP_IocpEventCallback::onResponse, mEventArg );
		mEventArg->setResponseQueue( msgQueue );
		mEventArg->loadDisconnectEx( listenFD );

		mAcceptArg->mAcceptEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
		mAcceptArg->mListenSocket = (HANDLE)listenFD;

		if( NULL == CreateIoCompletionPort( mAcceptArg->mListenSocket,
				mEventArg->getCompletionPort(), SP_IocpEventCallback::eKeyAccept, 0 ) ) {
			sp_syslog( LOG_ERR, "CreateIoCompletionPort fail, errno %d", WSAGetLastError() );
			return -1;		
		}

		if( NULL == mAcceptArg->mIOChannelFactory ) {
			mAcceptArg->mIOChannelFactory = new SP_DefaultIOChannelFactory();
		}

		sp_thread_t thread;
		ret = sp_thread_create( &thread, NULL, acceptThread, mAcceptArg );
		if( 0 == ret ) {
			sp_syslog( LOG_NOTICE, "Thread #%ld has been created to accept socket", thread );
		} else {
			sp_syslog( LOG_WARNING, "Unable to create a thread to accept socket, %s", strerror( errno ) );
			return -1;
		}

		mIsRunning = 1;

		mThreadPool = new SP_ThreadPool( mMaxThreads );
		for( int i = 0; i < mMaxThreads; i++ ) {
			mThreadPool->dispatch( lfHandler, this );
		}
	}

	return ret;
}