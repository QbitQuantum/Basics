std::string OFXGetEnv( const char* e )
{
	#if !defined( __GNUC__ ) && defined( WINDOWS )
	std::size_t requiredSize;
	getenv_s( &requiredSize, 0, 0, e );
	std::vector<char> buffer( requiredSize );
	if( requiredSize > 0 )
	{
		getenv_s( &requiredSize, &buffer.front(), requiredSize, e );
		return &buffer.front();
	}
	return "";
	#else
	const char* env_value = getenv( e );
	if( env_value == NULL )
		return "";
	return env_value;
	#endif
}