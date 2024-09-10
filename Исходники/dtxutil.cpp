void DtxUtil::FillDTXHandler( const char* input, const char* output, char* command )
{
	char inputDir[_MAX_PATH];
	char outputDir[_MAX_PATH];

	strcpy( inputDir, input );
	strcpy( outputDir, output );

	int inputLen = strlen( inputDir );
	int outputLen = strlen( outputDir );

	if( !inputLen || !outputLen )
		return;

	if( inputDir[inputLen-1] != '\\' )
	{
		inputDir[inputLen] = '\\';
		inputDir[inputLen+1] = 0;
		inputLen++;
	}

	if( outputDir[outputLen-1] != '\\' )
	{
		outputDir[outputLen] = '\\';
		outputDir[outputLen+1] = 0;
		outputLen++;
	}

	// loop over all .tgas in input directory and child directories
	WIN32_FIND_DATA findData;
	HANDLE findHandle;
	CString startDir;

	startDir = inputDir;
	startDir += "*.*";
	findHandle = FindFirstFile( LPCTSTR(startDir), &findData );

	if( findHandle != INVALID_HANDLE_VALUE )
	{
		do
		{
			if( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				// ignore directories starting with .
				if( findData.cFileName[0] != '.' )
				{
					// found a directory, recurse into it
					CString newInDir = inputDir;
					newInDir += findData.cFileName;
					CString newOutDir = outputDir;
					newOutDir += findData.cFileName;

					FillDTXHandler( newInDir, newOutDir, command );
				}
			}
			else
			{
				// it's a file, check to see if it's a tga
				char ext[_MAX_EXT];
				char file[_MAX_FNAME];

				_splitpath( findData.cFileName, NULL, NULL, file, ext );

				// make sure the extension is lower case
				for( unsigned i = 0; i < strlen( ext ); i++ )
				{
					if( isupper( ext[i] ) )
						ext[i] = tolower( ext[i] );
				}

				// found a tga, process it
				if( !strcmp( ext, ".tga" ) )
				{
					CString inFile = inputDir;
					inFile += file;
					inFile += ext;
					CString outFile = outputDir;
					outFile += file;
					outFile += ".dtx";

					FillDTX( inFile, outFile );
				}
			}
		}
		while( FindNextFile( findHandle, &findData ) );

		FindClose( findHandle );
	}
}