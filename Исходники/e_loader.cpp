// read palette files into buffer ---------------------------------------------
//
PRIVATE
void ReadPalettes()
{
	// exit if nothing to read
	if ( NumLoadedPalettes == 0 )
		PANIC( "no palette defined." );

	if ( ( PaletteMem = (char *) ALLOCMEM( PALETTE_SIZE * NumLoadedPalettes ) ) == NULL )
		OUTOFMEM( no_palette_mem );

	if ( display_info ) {
		MSGPUT( "Loading palettes" );
		if ( show_palettes_loaded ) {
			MSGOUT( ":\n" );
		} else {
			MSGPUT( "..." );
		}
	}

	// load all palettes
	size_t readofs = 0;
	for ( int pid = 0; pid < NumLoadedPalettes; pid++ ) {

		if ( display_info && !show_palettes_loaded )
			MSGPUT( "." );

		FILE *fp = SYS_fopen( palette_fnames[ pid ], "rb" );
		if ( fp == NULL )
			FERROR( palette_not_found, palette_fnames[ pid ] );

		if ( display_info && show_palettes_loaded ) {
			MSGOUT( "loading \"%s\" (palette)\n", palette_fnames[ pid ] );
		}

		size_t bytesread = SYS_fread( PaletteMem + readofs, 1, PALETTE_SIZE, fp );
		if ( bytesread != PALETTE_SIZE )
			FERROR( palette_readerror, palette_fnames[ pid ] );
		readofs += PALETTE_SIZE;

		SYS_fclose( fp );
	}

	if ( display_info ) {
		MSGOUT( "done.\n" );
	}
}