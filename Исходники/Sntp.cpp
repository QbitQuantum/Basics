BOOL CSNTPClient::SetClientTime( const CNtpTime & NewTime )
{
	BOOL bSuccess	= FALSE;
// AR 22-07-2000
#ifndef _WIN32_WCE
	if( EnableSetTimePrivilege() )
	{
#endif	// _WIN32_WCE
		SYSTEMTIME st	= NewTime;
		bSuccess	= SetSystemTime( &st );
		if( !bSuccess )
			TRACE( _T( "Failed in call to set the system time\n" ) );
// AR 22-07-2000
#ifndef _WIN32_WCE
	}
	RevertSetTimePrivilege();
#endif	// _WIN32_WCE
	return bSuccess;
}