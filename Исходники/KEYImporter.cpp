bool KEYImporter::Open(const char *resfile, const char *desc)
{
	free(description);
	description = strdup(desc);
	if (!core->IsAvailable( IE_BIF_CLASS_ID )) {
		print( "[ERROR]\nAn Archive Plug-in is not Available\n" );
		return false;
	}
	unsigned int i;
	// NOTE: Interface::Init has already resolved resfile.
	printMessage("KEYImporter", "Opening %s...", WHITE, resfile);
	FileStream* f = FileStream::OpenFile(resfile);
	if (!f) {
		// Check for backslashes (false escape characters)
		// this check probably belongs elsewhere (e.g. ResolveFilePath)
		if (strstr( resfile, "\\ " )) {
			print("%s", "\nEscaped space(s) detected in path!. Do not escape spaces in your GamePath! " );
		}
		printStatus( "ERROR", LIGHT_RED );
		printMessage( "KEYImporter", "Cannot open Chitin.key\n", LIGHT_RED );
		textcolor( WHITE );
		print("This means you set the GamePath config variable incorrectly.\n");
		print("It must point to the directory that holds a readable Chitin.key\n");
		return false;
	}
	printStatus( "OK", LIGHT_GREEN );
	printMessage( "KEYImporter", "Checking file type...", WHITE );
	char Signature[8];
	f->Read( Signature, 8 );
	if (strncmp( Signature, "KEY V1  ", 8 ) != 0) {
		printStatus( "ERROR", LIGHT_RED );
		printMessage( "KEYImporter", "File has an Invalid Signature.\n", LIGHT_RED );
		textcolor( WHITE );
		delete( f );
		return false;
	}
	printStatus( "OK", LIGHT_GREEN );
	printMessage( "KEYImporter", "Reading Resources...\n", WHITE );
	ieDword BifCount, ResCount, BifOffset, ResOffset;
	f->ReadDword( &BifCount );
	f->ReadDword( &ResCount );
	f->ReadDword( &BifOffset );
	f->ReadDword( &ResOffset );
	printMessage( "KEYImporter", " ", WHITE );
	print( "BIF Files Count: %d (Starting at %d Bytes)\n", BifCount,
		BifOffset );
	printMessage("KEYImporter", "RES Count: %d (Starting at %d Bytes)\n", WHITE,
		ResCount, ResOffset);
	f->Seek( BifOffset, GEM_STREAM_START );

	ieDword BifLen, ASCIIZOffset;
	ieWord ASCIIZLen;
	for (i = 0; i < BifCount; i++) {
		BIFEntry be;
		f->Seek( BifOffset + ( 12 * i ), GEM_STREAM_START );
		f->ReadDword( &BifLen );
		f->ReadDword( &ASCIIZOffset );
		f->ReadWord( &ASCIIZLen );
		f->ReadWord( &be.BIFLocator );
		be.name = ( char * ) malloc( ASCIIZLen );
		f->Seek( ASCIIZOffset, GEM_STREAM_START );
		f->Read( be.name, ASCIIZLen );
		for (int p = 0; p < ASCIIZLen; p++) {
			//some MAC versions use : as delimiter
			if (be.name[p] == '\\' || be.name[p] == ':')
				be.name[p] = PathDelimiter;
		}
		FindBIF(&be);
		biffiles.push_back( be );
	}
	f->Seek( ResOffset, GEM_STREAM_START );

	MapKey key;
	ieDword ResLocator;

	// limit to 32k buckets
	// only ~1% of the bg2 entries are of bucket lenght >4
	resources.init(ResCount > 32 * 1024 ? 32 * 1024 : ResCount, ResCount);

	for (i = 0; i < ResCount; i++) {
		f->ReadResRef(key.ref);
		f->ReadWord(&key.type);
		f->ReadDword(&ResLocator);

		// seems to be always the last entry?
		if (key.ref[0] != 0)
			resources.set(key, ResLocator);
	}

	printMessage( "KEYImporter", "Resources Loaded...", WHITE );
	printStatus( "OK", LIGHT_GREEN );
	delete( f );
	return true;
}