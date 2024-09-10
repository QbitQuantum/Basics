// ---------------------------------------------------------------------------
// Launches the app server.
// ---------------------------------------------------------------------------
// 
EXPORT_C void RAlfClientBase::LaunchAppL( 
    TUid aAppUid, 
    TUint aServerDifferentiator, 
    TThreadId& aThreadId )
	{
	RApaLsSession apa;
	User::LeaveIfError( apa.Connect() );
	CleanupClosePushL( apa );
	
	TApaAppInfo info;
	User::LeaveIfError( apa.GetAppInfo( info, aAppUid ) );

	CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
	cmdLine->SetExecutableNameL( info.iFullName );
	cmdLine->SetServerRequiredL( aServerDifferentiator );
    // Set the command to start the server in background
    cmdLine->SetCommandL( EApaCommandBackground );        

	TRequestStatus status;	
	TInt err = apa.StartApp( *cmdLine, aThreadId, &status );
    
    User::LeaveIfError( err );
    
    User::WaitForRequest(status);
    
    User::LeaveIfError( status.Int() );
    
	CleanupStack::PopAndDestroy( cmdLine );
	CleanupStack::PopAndDestroy( &apa );
	}