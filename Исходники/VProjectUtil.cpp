//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
std::string CVProjectUtil::ConvertMaterialSrcToVtf(
	const std::string &file )
{
	const std::string game( Prefix() + "/game/" + Game() );
	const std::string src( MaterialSrc( file ) );

	const std::string cmd( std::string( "vtex -mkdir -nopause -game \"" ) + game + std::string( "\" \"" ) + src + "\"" );

	FILE *vtex( _popen( cmd.c_str(), "rt" ) );
	if ( !vtex )
	{
		merr << "Couldn't execute vtex command: " << cmd << std::endl;
		return false;
	}

	char buf[ BUFSIZ ];

	while ( !feof( vtex ) )
	{
		if ( fgets( buf, BUFSIZ, vtex ) == NULL )
		{
			break;
		}

		minfo << "vtex: " << buf;
	}
	minfo << std::endl;

	_pclose( vtex );

	return MaterialDst( src );
}