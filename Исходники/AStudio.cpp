// Get long path name from short path name.
// assumes that LongPath has enough characters to hold the generated name
static bool ShortPathToLongPath (const char *ShortPath, char *LongPath)
{
// Man, this is a seriously disturbed function.
// Win32 could use a GetLongFileName function (NT 5 has one...)
	LPSHELLFOLDER psfDesktop = NULL;

	WCHAR szShortPathNameW[MAX_PATH];

	// convert path name to wide and copy to local storage
	ULONG chEaten = 0;
	LPITEMIDLIST pidlShellItem = NULL;

	mbstowcs (szShortPathNameW, ShortPath, MAX_PATH);

	// Get desktop's shell folder interface
	HRESULT hr = SHGetDesktopFolder (&psfDesktop);

	// request an ID list (relative to the desktop) for the short pathname
	hr = psfDesktop->ParseDisplayName (NULL, NULL, szShortPathNameW, &chEaten, &pidlShellItem, NULL);
	psfDesktop->Release ();		// release desktop's IShellFolder

	if (FAILED (hr))
	{
		return false;
	}

	// got an ID list.  Convert it to a long pathname
	SHGetPathFromIDListA (pidlShellItem, LongPath);

	// Free the ID list allocated by ParseDisplayName
	LPMALLOC pMalloc = NULL;
	SHGetMalloc (&pMalloc);
	pMalloc->Free (pidlShellItem);
	pMalloc->Release ();

	return true;
}