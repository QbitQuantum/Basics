// returns true if successful, false otherwise
bool MsdFile::ReadFile( CString sNewPath )
{
	error = "";

	RageFile f;
	/* Open a file. */
	if( !f.Open( sNewPath ) )
	{
		error = f.GetError();
		return false;
	}

	// allocate a string to hold the file
	CString FileString;
	FileString.reserve( f.GetFileSize() );

	int iBytesRead = f.Read( FileString );
	if( iBytesRead == -1 )
	{
		error = f.GetError();
		return false;
	}

	ReadBuf( (char*) FileString.c_str(), iBytesRead );

	return true;
}