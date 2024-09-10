static LPITEMIDLIST WINAPI SHBrowseForFolderUW(PBROWSEINFO lpbi)
{
	// BROWSEINFOA and BROWSEINFOW don't contain any actual string data,
	// so the structs can be copied.
	BROWSEINFOW wbi;
	memcpy(&wbi, lpbi, sizeof(wbi));
	
	// Convert constant strings from UTF-8 to UTF-16.
	wchar_t *lpszwTitle = NULL;
	
	if (lpbi->lpszTitle)
	{
		lpszwTitle = w32u_UTF8toUTF16(lpbi->lpszTitle);
		wbi.lpszTitle = lpszwTitle;
	}
	
	// Allocate the return buffer.
	wchar_t *pszwDisplayName = NULL;
	if (lpbi->pszDisplayName)
	{
		// This is assumed to be MAX_PATH characters.
		pszwDisplayName = (wchar_t*)malloc(MAX_PATH * sizeof(wchar_t));
		wbi.pszDisplayName = pszwDisplayName;
	}
	
	// Get the directory list entry.
	LPITEMIDLIST pidl = SHBrowseForFolderW(&wbi);
	
	// Convert the non-constant strings from UTF-16 to UTF-8.
	if (wbi.pszDisplayName)
	{
		WideCharToMultiByte(CP_UTF8, 0, wbi.pszDisplayName, MAX_PATH,
				     lpbi->pszDisplayName, MAX_PATH, NULL, NULL);
	}
	
	// Free the strings.
	free(lpszwTitle);
	free(pszwDisplayName);
	return pidl;
}