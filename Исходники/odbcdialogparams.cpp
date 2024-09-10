void choosePath( HWND parent, int hostCtlId )
{
	HWND			hostControl = GetDlgItem( parent, hostCtlId );

	BROWSEINFOW		dialog;
	wchar_t			path[MAX_PATH];    // buffer for file name

	Edit_GetText( hostControl, path, sizeof(path) );

	ZeroMemory(&dialog,sizeof(dialog));

	dialog.lpszTitle		= L"Pick a CA Path";
	dialog.hwndOwner		= parent;
	dialog.pszDisplayName	= path;

	LPITEMIDLIST pidl = SHBrowseForFolder ( &dialog );

	if ( pidl )
	{
		SHGetPathFromIDList ( pidl, path );

		Edit_SetText( hostControl, path );

		IMalloc * imalloc = 0;
		if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
		{
			imalloc->Free ( pidl );
			imalloc->Release ( );
		}
	}
}