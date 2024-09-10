DWORD TUserGetAllInfo ( LPCSTR lpUserName, PUSER_INFO lpUserInfo )
{
	CHAR	szUserName[MAX_USER_NAME];
	LPSTR	ptr = NULL;
	DWORD	dwRetCode = 0;

	if( lpUserName == NULL || lpUserInfo == NULL )
		return ERROR_INVALID_PARAMETER;

	if( *lpUserName == '\x0' )
		return ERROR_INVALID_PARAMETER;

	if( UserDB == NULL )
		return TERR_NO_USER_DB;

	ZeroMemory( szUserName, MAX_USER_NAME );
	lstrcpyn( szUserName, lpUserName, MAX_USER_NAME );
	_strupr( szUserName );

	__try {
		WaitForSingleObject( hUserDBMutex, INFINITE );

		ptr = readBtreeData( UserDB, szUserName, (LPSTR)lpUserInfo, sizeof( USER_INFO ) );
		if( !ptr ) {
			dwRetCode = TERR_USER_NOT_EXIST;
			__leave;
		}

	}
	__finally {
		ReleaseMutex( hUserDBMutex );
	}
	
	return dwRetCode;
}