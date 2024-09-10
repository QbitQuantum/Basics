DEBUG_LOCAL OSStatus	EnableNSP( const char *inGUID, BOOL inEnable )
{
	OSStatus		err;
	WSADATA			wsd;
	GUID			guid;
	
	require_action( inGUID && ( *inGUID != '\0' ), exit, err = kParamErr );
	
	err = StringToGUID( inGUID, &guid );
	require_noerr( err, exit );
	
	err = WSAStartup( MAKEWORD( 2, 2 ), &wsd );
	err = translate_errno( err == 0, errno_compat(), WSAEINVAL );
	require_noerr( err, exit );
	
	err = WSCEnableNSProvider( &guid, inEnable );
	err = translate_errno( err == 0, errno_compat(), WSAEINVAL );
	WSACleanup();
	require_noerr( err, exit );
	
	if (!gToolQuietMode)
	{
		fprintf( stderr, "Removed NSP %s\n", inGUID );
	}
		
exit:
	if( err != kNoErr )
	{
		fprintf( stderr, "### FAILED (%d) to remove %s Name Space Provider\n", err, inGUID );
	}
	return( err );
}