//
// RunCmd is a private function to work around an obscure protocol
// bug in 2000.[12] servers. Running a "p4 -Ztag client -o" messes up the
// protocol so if they're running this command then we disconnect and
// reconnect to refresh it. For efficiency, we only do this if the
// server2 protocol is either 9 or 10 as other versions aren't affected.
//
void
P4ClientApi::RunCmd( const char *cmd, ClientUser *ui, int argc, char * const *argv, int table )
{
	client.SetProg( &prog );
	if( version.Length() )
		client.SetVersion( &version );

	if( mode & M_TAGGED )
		client.SetVar( "tag" );

	// If maxresults or maxscanrows is set, enforce them now
	if( maxResults  )	client.SetVar( "maxResults",  maxResults  );
	if( maxScanRows )	client.SetVar( "maxScanRows", maxScanRows );
	if( maxLockTime )	client.SetVar( "maxLockTime", maxLockTime );

	client.SetBreak( &cb );
	client.SetArgv( argc, argv );
	client.Run( cmd, ui );

	// Have to request server2 protocol *after* a command has been run. I
	// don't know why, but that's the way it is.

	if ( ! server2 )
	{
		StrPtr *pv = client.GetProtocol( "server2" );
		if ( pv )
			server2 = pv->Atoi();
	}

	if ( IS_TAGGED(mode) && StrRef( cmd ) == "client" &&
		server2 >= 9    && server2 <= 10  )
	{
		if ( argc && ( StrRef( argv[ 0 ] ) == "-o" ) )
		{
			if ( P4LUADEBUG_COMMANDS )
				printf( "Resetting client to avoid 2000.[12] protocol bug\n" );

			Error e;
			client.Final( &e );
			client.Init( &e );

			// Pass any errors down to the UI, so they'll get picked up.
			if ( e.Test() )
				ui->HandleError( &e );
		}
	}
}