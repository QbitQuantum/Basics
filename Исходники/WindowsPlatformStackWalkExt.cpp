bool FWindowsPlatformStackWalkExt::InitStackWalking()
{
	if (!FWindowsPlatformMisc::CoInitialize())
	{
		return false;
	}

	check( DebugCreate( __uuidof( IDebugClient5 ), ( void** )&Client ) == S_OK );

	check( Client->QueryInterface( __uuidof( IDebugControl4 ), ( void** )&Control ) == S_OK );
	check( Client->QueryInterface( __uuidof( IDebugSymbols3 ), ( void** )&Symbol ) == S_OK );
	check( Client->QueryInterface( __uuidof( IDebugAdvanced3 ), ( void** )&Advanced ) == S_OK );

	return true;
}