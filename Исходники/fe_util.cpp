std::string absolute_path( const std::string &path )
{
#ifdef SFML_SYSTEM_WINDOWS

	const int BUFF_SIZE = 512;
	char buff[ BUFF_SIZE + 1 ];
	buff[BUFF_SIZE] = 0;

	if ( GetFullPathNameA( path.c_str(), BUFF_SIZE, buff, NULL ))
		return std::string( buff );
#else
	char buff[PATH_MAX+1];

	if ( realpath( path.c_str(), buff ) )
	{
		std::string retval = buff;
		if (( retval.size() > 0 ) && ( retval[ retval.size()-1 ] != '/' ))
			retval += "/";

		return retval;
	}
#endif // SFML_SYSTEM_WINDOWS

	return path;
}