/**
 * 폴더 가져오기
*/
BOOL GetFolder(CString* strSelectedFolder, const char* lpszTitle, const HWND hwndOwner, 
				   const char* strRootFolder, const char* strStartFolder)
{
	char			pszDisplayName[ MAX_PATH ];
	LPITEMIDLIST	lpID;
	BROWSEINFOA		bi;
	
	bi.hwndOwner = hwndOwner;
	
	if (strRootFolder == NULL)
	{ bi.pidlRoot = NULL; }
	else
	{
	   LPITEMIDLIST  pIdl = NULL;
	   IShellFolder* pDesktopFolder;
	   char          szPath[ MAX_PATH ];
	   OLECHAR       olePath[ MAX_PATH ];
	   ULONG         chEaten;
	   ULONG         dwAttributes;

	   strcpy(szPath, (LPCTSTR)strRootFolder);
	   if (SUCCEEDED (SHGetDesktopFolder (&pDesktopFolder)))
	   {
		   MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, szPath, -1, olePath, MAX_PATH);
		   pDesktopFolder->ParseDisplayName (NULL, NULL, olePath, &chEaten, &pIdl, &dwAttributes);
		   pDesktopFolder->Release ();
	   }
	   bi.pidlRoot = pIdl;
	}
	bi.pszDisplayName	= pszDisplayName;
	bi.lpszTitle		= lpszTitle;
	bi.ulFlags			= BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	bi.lpfn				= BrowseCallbackProc;

	if (strStartFolder == NULL)
	{ bi.lParam = FALSE; }
	else
	{
		strTmpPath.Format ("%s", strStartFolder);
		bi.lParam = TRUE;
	}
	bi.iImage = NULL;
	lpID = SHBrowseForFolderA(&bi);
	if (lpID != NULL)
	{
		BOOL b = SHGetPathFromIDList (lpID, pszDisplayName);
		if (b == TRUE)
		{
			strSelectedFolder->Format ("%s",pszDisplayName);
			return TRUE;
		}
	}
	else
	{ strSelectedFolder->Empty (); }

	return FALSE;
}