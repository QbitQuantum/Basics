/*
缓存目录
*/
static CString GetCacheDirectory()
{
#if 0
	char szModule[MAX_PATH*2] = {0};
	GetModuleFileName( NULL, szModule, MAX_PATH*2 );
	if ( !PathFileExists( szModule ) )
	{
		return "";
	}
	char* pTemp = strrchr( szModule, '\\' );
	if ( pTemp == NULL )
	{
		return "";
	}
	szModule[ pTemp-szModule ] = '\0';
	StringCbCat( szModule, MAX_PATH*2, "\\RunCache" );
	if ( !PathFileExists( szModule ) )
	{
		if ( !MakeSureDirectoryPathExists( szModule ) )
		{
			return "";
		}
	}
	return szModule;
#else
	CString sCacheDirectory = GetPeraGlobalDataFromReg( "LM", "PeraPRCacheDir" );
	if ( MakeSureDirectoryPathExists( sCacheDirectory ) )
	{
	}
	return sCacheDirectory;
#endif
}