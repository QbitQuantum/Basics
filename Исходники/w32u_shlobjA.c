static LPITEMIDLIST WINAPI SHBrowseForFolderUA(PBROWSEINFO lpbi)
{
	// BROWSEINFOA and BROWSEINFOW don't contain any actual string data,
	// so the structs can be copied.
	BROWSEINFOA abi;
	memcpy(&abi, lpbi, sizeof(abi));
	
	// Convert constant strings from UTF-8 to ANSI.
	char *lpszaTitle = NULL;
	
	if (lpbi->lpszTitle)
	{
		lpszaTitle = w32u_UTF8toANSI(lpbi->lpszTitle);
		abi.lpszTitle = lpszaTitle;
	}
	
	// Allocate the return buffer.
	char *pszaDisplayName = NULL;
	if (lpbi->pszDisplayName)
	{
		// This is assumed to be MAX_PATH characters.
		pszaDisplayName = (char*)malloc(MAX_PATH * sizeof(char));
		abi.pszDisplayName = pszaDisplayName;
	}
	
	// Get the directory list entry.
	LPITEMIDLIST pidl = SHBrowseForFolderA(&abi);
	
	// Convert the non-constant strings from ANSI to UTF-8.
	if (abi.pszDisplayName)
	{
		w32u_ANSItoUTF8_copy(lpbi->pszDisplayName, abi.pszDisplayName, MAX_PATH);
	}
	
	// Free the strings.
	free(lpszaTitle);
	free(pszaDisplayName);
	return pidl;
}