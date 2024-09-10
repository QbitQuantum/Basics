// -----------------------------------------------------------------------------
// CClientInstallerApplication::StartBrowser(URL)
// Start up a NETFRONT browser on a given URL
// -----------------------------------------------------------------------------
//
void CClientInstallerApplication::StartBrowser(const TDesC& aUrl)
	{
	HBufC* param = HBufC::NewLC( 256 );
	param->Des().Format( _L( "4 %S" ),&aUrl );

	const TInt KWmlBrowserUid = ${browser.UID};  // NETFRONT Browser 3.3

	TUid id( TUid::Uid( KWmlBrowserUid ) );

	TApaTaskList taskList( CEikonEnv::Static()->WsSession() );
	TApaTask task = taskList.FindApp( id );
	if ( task.Exists() )
	{
	     HBufC8* param8 = HBufC8::NewLC( param->Length() );
	     param8->Des().Append( *param );
	     task.SendMessage( TUid::Uid( 0 ), *param8 ); // Uid is not used
	     CleanupStack::PopAndDestroy(); // param8
	}
	else
	{
	     RApaLsSession appArcSession;
	     User::LeaveIfError(appArcSession.Connect()); // connect to AppArc server
	     TThreadId id;
	     appArcSession.StartDocument( *param, TUid::Uid( KWmlBrowserUid ), id );
	     appArcSession.Close();
	}
	CleanupStack::PopAndDestroy(); // param
	}