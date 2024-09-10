bool GetModelNameFromSourceFile( char const *filename, char *modelname, int maxlen )
{
	modelname[0]=0;

	int filelength;
	char *buffer = (char *)COM_LoadFile( filename, &filelength );
	if ( !buffer )
	{
		vprint( 0, "Couldn't load %s\n", filename );
		return false;
	}

	bool valid = false;

	// Parse tokens
	char *current = buffer;
	while ( current )
	{
		current = CC_ParseToken( current );
		if ( strlen( com_token ) <= 0 )
			break;

		if ( stricmp( com_token, "$modelname" ) )
			continue;

		current = CC_ParseToken( current );

		strcpy( modelname, com_token );
		_strlwr( modelname );

		Q_FixSlashes( modelname );

		Q_DefaultExtension( modelname, ".mdl", maxlen );

		valid = true;
		break;
	}

	COM_FreeFile( (unsigned char *)buffer );

	if ( !valid )
	{
		vprint( 0, ".qc file %s missing $modelname directive!!!\n", filename );
	}
	return valid;
}