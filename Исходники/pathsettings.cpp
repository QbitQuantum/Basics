BOOL BrowseForPath(char *pathToBrowse)
{
	LPMALLOC shMalloc;
	BOOL changed = false;
	LPITEMIDLIST idList;
	BROWSEINFO bi;

	//stupid shell
	if(SHGetMalloc( &shMalloc) != S_OK)
		return FALSE;

	ZeroMemory(&idList, sizeof(idList));
	ZeroMemory(&bi, sizeof(bi));

	char tmp[MAX_PATH];
	strncpy(tmp, pathToBrowse, MAX_PATH);

	bi.hwndOwner = MainWindow->getHWnd();
	bi.lpszTitle = "Choose a Folder";
	bi.ulFlags = BIF_NONEWFOLDERBUTTON;

	/*wanted to add a callback function for the folder initialization but it crashes everytime i do
	bi.lpfn = (BFFCALLBACK)InitialFolder;
	bi.lParam = (LPARAM)pathToBrowse;
	*/

	if( (idList = SHBrowseForFolder(&bi)) )
	{
		changed = true;
		SHGetPathFromIDList(idList, pathToBrowse);
//		shMalloc->Free(&idList);
	}

	return changed;
}