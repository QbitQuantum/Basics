//--------------------------------------------------------------------------------------
// Name: OpenXbeFile
// Desc: Allows the user to search for any given .xbe file to use with the emulator.
//--------------------------------------------------------------------------------------
bool OpenXbeFile( void )
{
	char filter[256] = {0};
	char filename[256] = {0};
	OPENFILENAMEA File;

	if( Xbe.m_bXbeHasBeenOpened )
		XBEUnload();

	strcat( filter, "XBox Executable Files (*.xbe)" );
	ZeroMemory( &File, sizeof( OPENFILENAME ) );

	int index = lstrlenA( filter ) + 1;
	filter[index++] = '*';
	filter[index++] = '.';
	filter[index++] = 'x';
	filter[index++] = 'b';
	filter[index++] = 'e';

	File.lStructSize = sizeof( OPENFILENAME );
	File.hwndOwner = GetActiveWindow();
	File.lpstrFilter = filter;
	File.lpstrFile = filename;
	File.nMaxFile = 256;
	File.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

	if( !GetOpenFileNameA( &File ) )
		return EmuError( "Unable to load file.\n" );

	// Back up the .exe data before executing
	EmuMMUSaveExeContents();

	// Now, actually load the .xbe into memory.
	if( !XBELoad( File.lpstrFile ) )
	{
		EmuError( "Unable to load Xbe file!\n" );
		return 0;
	}

	// Hijack kernel functions
	HookKrnlFunctions();

	// Activate other threads
	ResumeThread( g_hExecutionThread );
	ResumeThread( g_hUpdateThread );

	return true;
}