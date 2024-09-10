void SetProfile( GUID guidIntf, char *essid, char *pwd )
{
	DWORD dwError;
	HANDLE hClient = NULL;
	DWORD dwReason;

	wchar_t strXml[1024];
	_snwprintf( strXml, _countof(strXml), szProfileStringFmt, essid, essid, pwd );

	// open handle
	if ((dwError = OpenHandleAndCheckVersion(
		&hClient
		)) != ERROR_SUCCESS)
	{
		puts( "error open handle" );
		return;
	}

	// set profile
	dwError = WlanSetProfile(
		hClient, 
		&guidIntf, 
		0,          // no flags for the profile 
		strXml, 
		NULL,       // use the default ACL
		TRUE,		// overwrite a profile if it already exists
		NULL,       // reserved
		&dwReason
		);

	switch(dwError)
	{
	case ERROR_INVALID_PARAMETER:
		puts( "The profile has invalid params." );
		break;
	case ERROR_BAD_PROFILE:
		puts( "The profile is bad." );
		break;
	case ERROR_ALREADY_EXISTS:
		puts( "The profile is already exists." );
	}

	// clean up
	if (hClient != NULL)
	{
		WlanCloseHandle(
			hClient, 
			NULL            // reserved
			);
	}
}