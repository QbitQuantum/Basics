/*
	AddPackagePath().

*/
static int c_AddPackagePath( lua_State *_pState )
{
	const char *packagePath = luaL_checkstring( _pState, 1 );

	bool bRelative = true;

	if( lua_isboolean( _pState, 2 ) )
		if( lua_toboolean( _pState, 2 ) == 0 )
			bRelative = false;

	char  dirBuf[ MAX_PATH + 1];
#if defined(WIN32) && defined(_MSC_VER)
	std::string dir;
	if (GetCurrentDirectoryA(sizeof(dirBuf) - 1, dirBuf))
		dir = dirBuf;
#else
	std::string dir = getcwd( &dirBuf[0], MAX_PATH + 1 );
#endif

	if( bRelative )
		dir += packagePath;
	else
		dir = packagePath;

	Call( _pState, "AddInstallation", "s", (const char *)dir.c_str() );

	return( 0 );
}