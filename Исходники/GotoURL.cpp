bool GotoURL( RString sUrl )
{
	// First try ShellExecute()
	int iRet = (int) ShellExecute( NULL, "open", sUrl, NULL, NULL, SW_SHOWDEFAULT );

	// If it failed, get the .htm regkey and lookup the program
	if( iRet > 32 )
		return true;

	char key[2*MAX_PATH];
	if( GetRegKey(HKEY_CLASSES_ROOT, ".htm", key) != ERROR_SUCCESS )
		return false;

	strcpy( key, "\\shell\\open\\command" );

	if( GetRegKey(HKEY_CLASSES_ROOT, key, key) != ERROR_SUCCESS )
		return false;

	char *szPos = strstr( key, "\"%1\"" );
	if( szPos == NULL )
	{
		// No quotes found. Check for %1 without quotes
		szPos = strstr( key, "%1" );
		if( szPos == NULL )
			szPos = key+lstrlen(key)-1;	// No parameter.
		else
			*szPos = '\0';	// Remove the parameter
	}
	else
		*szPos = '\0';	// Remove the parameter

	strcat( szPos, " " );
	strcat( szPos, sUrl );

	return WinExec( key, SW_SHOWDEFAULT ) > 32;
}