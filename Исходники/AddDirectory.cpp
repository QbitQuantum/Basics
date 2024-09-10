////////////////////////////////////////////////////////////////////////////////
/// Shows a Browse-For-Folder dialog and recursively adds supported files
/// to the playlist. Files are sorted by full filaname before being added.
////////////////////////////////////////////////////////////////////////////////
void AddDirectory()
{
	TCHAR szPath[ MAX_PATH ];
	BROWSEINFO bi = { 0 };
	bi.hwndOwner  = WindowMain;
	bi.pidlRoot   = NULL; // Desktop folder
	bi.lpszTitle  = TEXT( "Please select a directory:" );
	bi.ulFlags    = BIF_VALIDATE | BIF_STATUSTEXT;
	bi.lpfn       = BrowseCallbackProc;

	LPITEMIDLIST pidl = SHBrowseForFolder( &bi );
	if( !pidl ) return;
	
	// Get path
	SHGetPathFromIDList( pidl, szPath );


	// Search
	SearchFolder( szPath );


	// Stay here
	SetCurrentDirectory( szPath );


	// Free memory used
	IMalloc * imalloc = 0;
	if( SUCCEEDED( SHGetMalloc( &imalloc ) ) )
	{
		imalloc->Free( pidl );
		imalloc->Release();
	}
}