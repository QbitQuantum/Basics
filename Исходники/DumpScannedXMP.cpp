static void
ProcessFile ( const char * fileName  )
{
	FILE * inFile;
	size_t fileLen, readCount;
	size_t snipCount;
	char buffer [64*1024];

	// ---------------------------------------------------------------------
	// Use the scanner to find all of the packets then process each of them.
	
	inFile = fopen ( fileName, "rb" );
	if ( inFile == 0 ) {
		printf ( "Can't open \"%s\"\n", fileName );
		return;
	}
	
	fseek ( inFile, 0, SEEK_END );
	fileLen = ftell ( inFile );	// ! Only handles up to 2GB files.
	fseek ( inFile, 0, SEEK_SET );

	XMPScanner scanner ( fileLen );
	
	for ( size_t filePos = 0; true; filePos += readCount ) {
		readCount = fread ( buffer, 1, sizeof(buffer), inFile );
		if ( readCount == 0 ) break;
		scanner.Scan ( buffer, filePos, readCount );
	}
	
	snipCount = scanner.GetSnipCount();
	
	XMPScanner::SnipInfoVector snips (snipCount);
	scanner.Report ( snips );

	size_t packetCount = 0;
	for ( size_t s = 0; s < snipCount; ++s ) {
		if ( snips[s].fState == XMPScanner::eValidPacketSnip ) {
			++packetCount;
			ProcessPacket ( fileName, inFile, (size_t)snips[s].fOffset, (size_t)snips[s].fLength );
		}
	}
	if ( packetCount == 0 ) printf ( "   No packets found\n" );

}	// ProcessFile