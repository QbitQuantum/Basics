void GetAvatarCache(LPTSTR szPath)
{
	// Получить путь новым способом
	if ( ServiceExists( MS_UTILS_REPLACEVARS ) )
	{
		LPTSTR szAvatarCache = Utils_ReplaceVarsT(
			_T("%miranda_avatarcache%\\") modname_t _T("\\") );
		if ( szAvatarCache && szAvatarCache != (LPTSTR)0x80000000 )
		{
			lstrcpyn( szPath, szAvatarCache, MAX_PATH );

			// Создание пути до будущего файла аватара
			CallService( MS_UTILS_CREATEDIRTREET, 0, (LPARAM)szPath );
			return;
		}
	}

	// Получить путь старым способом
	char szProfilePath[ MAX_PATH ], szProfileName[ MAX_PATH ];
	CallService( MS_DB_GETPROFILEPATH, MAX_PATH, (LPARAM)szProfilePath );
	CallService( MS_DB_GETPROFILENAME, MAX_PATH, (LPARAM)szProfileName );
	char *pos = strrchr( szProfileName, '.' );
	if ( lstrcmpA( pos, ".dat" ) == 0 )
		*pos = 0;
	lstrcpy( szPath, CA2T( szProfilePath ) );
	lstrcat( szPath, _T("\\") );
	lstrcat( szPath, CA2T( szProfileName ) );
	lstrcat( szPath, _T("\\AvatarCache\\") modname_t _T("\\") );

	// Создание пути до будущего файла аватара
	CallService( MS_UTILS_CREATEDIRTREET, 0, (LPARAM)szPath );
	return;
}