void CTcAppLauncher::RunL()
	{
	// Fatal error occurred, report
	User::LeaveIfError( iStatus.Int() );

	if( iDismissDialog )
		{
		TKeyEvent event;
		event.iCode = EKeyDevice3;
		RWsSession wsSession;
		User::LeaveIfError( wsSession.Connect() );
		wsSession.SimulateKeyEvent( event );
		wsSession.Close();
		}

	RApaLsSession apparc;
	User::LeaveIfError( apparc.Connect() );
	CleanupClosePushL( apparc );

	CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
	cmdLine->SetExecutableNameL( iAppName );
	cmdLine->SetCommandL( EApaCommandRun );

	User::LeaveIfError( apparc.StartApp( *cmdLine ) );
	CleanupStack::PopAndDestroy( 2 );

	// Write log entry
	LOG( _L("[APPLAUNCHER] Client restarted.") );
	delete this;
	}