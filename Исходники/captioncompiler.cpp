void CCompileCaptionsApp::CompileCaptionFile( char const *infile, char const *outfile )
{
	StringIndex_t maxindex = (StringIndex_t)-1;
	int maxunicodesize = 0;
	int totalsize = 0;

	int c = 0;

	int curblock = 0;
	int usedBytes = 0;
	int blockSize = MAX_BLOCK_SIZE;

	int freeSpace = 0;

	CUtlVector< CaptionLookup_t >	directory;
	CUtlBuffer data;

	CUtlRBTree< unsigned int >	hashcollision( 0, 0, DefLessFunc( unsigned int ) );

	for ( StringIndex_t i = g_pVGuiLocalize->GetFirstStringIndex(); i != INVALID_LOCALIZE_STRING_INDEX; i = g_pVGuiLocalize->GetNextStringIndex( i ), ++c )
	{
		char const *entryName = g_pVGuiLocalize->GetNameByIndex( i );
		CaptionLookup_t entry;
		entry.SetHash( entryName );
		
		// 	vprint( 0, "%d / %d:  %s == %u\n", c, i, g_pVGuiLocalize->GetNameByIndex( i ), entry.hash );

		if ( hashcollision.Find( entry.hash ) != hashcollision.InvalidIndex() )
		{
			Error( "Hash name collision on %s!!!\n", g_pVGuiLocalize->GetNameByIndex( i ) );
		}

		hashcollision.Insert( entry.hash );

		const wchar_t *text = g_pVGuiLocalize->GetValueByIndex( i );
		if ( verbose )
		{
			vprint( 0, "Processing: '%30.30s' = '%S'\n", entryName, text );
		}
		int len = text ? ( wcslen( text ) + 1 ) * sizeof( short ) : 0;
		if ( len > maxunicodesize )
		{
			maxindex = i;
			maxunicodesize = len;
		}

		if ( len > blockSize )
		{
			Error( "Caption text file '%s' contains a single caption '%s' of %d bytes (%d is max), change MAX_BLOCK_SIZE in captioncompiler.h to fix!!!\n", g_pVGuiLocalize->GetNameByIndex( i ),
				entryName, len, blockSize );
		}
		totalsize += len;

		if ( usedBytes + len >= blockSize )
		{
			++curblock;

			int leftover = ( blockSize - usedBytes );

			totalsize += leftover;

            freeSpace += leftover;

			while ( --leftover >= 0 )
			{
				data.PutChar( 0 );
			}

			usedBytes = len;
			entry.offset = 0;

			data.Put( (const void *)text, len );
		}
		else
		{
			entry.offset = usedBytes;
			usedBytes += len;
			data.Put( (const void *)text, len );
		}

		entry.length = len;
		entry.blockNum = curblock;

		directory.AddToTail( entry );
	}
	
	int leftover = ( blockSize - usedBytes );
	totalsize += leftover;
	freeSpace += leftover;
	while ( --leftover >= 0 )
	{
		data.PutChar( 0 );
	}

	vprint( 0, "Found %i strings in '%s'\n", c, infile );

	if ( maxindex != INVALID_LOCALIZE_STRING_INDEX )
	{
		vprint( 0, "Longest string '%s' = (%i) bytes average(%.3f)\n%",
			g_pVGuiLocalize->GetNameByIndex( maxindex ), maxunicodesize, (float)totalsize/(float)c );
	}

	vprint( 0, "%d blocks (%d bytes each), %d bytes wasted (%.3f per block average), total bytes %d\n",
		curblock + 1, blockSize, freeSpace, (float)freeSpace/(float)( curblock + 1 ), totalsize );

	vprint( 0, "directory size %d entries, %d bytes, data size %d bytes\n",
		directory.Count(), directory.Count() * sizeof( CaptionLookup_t ), data.TellPut() );

	CompiledCaptionHeader_t header;
	header.magic			= COMPILED_CAPTION_FILEID;
	header.version			= COMPILED_CAPTION_VERSION;
	header.numblocks		= curblock + 1;
	header.blocksize		= blockSize;
	header.directorysize	= directory.Count();
	header.dataoffset		= 0;

	// Now write the outfile
	CUtlBuffer out;
	out.Put( &header, sizeof( header ) );
	out.Put( directory.Base(), directory.Count() * sizeof( CaptionLookup_t ) );
	int curOffset = out.TellPut();
	// Round it up to the next 512 byte boundary
	int nBytesDestBuffer = AlignValue( curOffset, 512 );  // align to HD sector
	int nPadding = nBytesDestBuffer - curOffset;
	while ( --nPadding >= 0 )
	{
		out.PutChar( 0 );
	}
	out.Put( data.Base(), data.TellPut() );

	// Write out a corrected header
	header.dataoffset = nBytesDestBuffer;
	int savePos = out.TellPut();
	out.SeekPut( CUtlBuffer::SEEK_HEAD, 0 );
	out.Put( &header, sizeof( header ) );
	out.SeekPut( CUtlBuffer::SEEK_HEAD, savePos );

	g_pFullFileSystem->WriteFile( outfile, NULL, out );

	// Jeep: this function no longer exisits
	/*if ( bX360 )
	{
		UpdateOrCreateCaptionFile_X360( g_pFullFileSystem, outfile, NULL, true );
	}*/
}