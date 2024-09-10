bool CXTPShellListCtrlEx::BrowseToFolder(LPCTSTR lpszPath)
{
	XTP_TVITEMDATA lpTVID;

	LPITEMIDLIST  pidl;
	LPSHELLFOLDER pDesktopFolder;
	OLECHAR       szOleChar[MAX_PATH];
	ULONG         chEaten;
	ULONG         dwAttributes;
	HRESULT       hr;

	// Get a pointer to the Desktop's IShellFolder interface.
	if (SUCCEEDED(::SHGetDesktopFolder(&pDesktopFolder)))
	{
		// IShellFolder::ParseDisplayName requires the file name be in
		// Unicode.

#if !defined(_UNICODE)
		::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpszPath, -1,
			szOleChar, MAX_PATH);
#else
		STRCPY_S(szOleChar, MAX_PATH, lpszPath);
#endif

		// Convert the path to an ITEMIDLIST.
		hr = pDesktopFolder->ParseDisplayName(NULL, NULL, szOleChar,
			&chEaten, &pidl, &dwAttributes);

		if (SUCCEEDED(hr))
		{
			IShellFolder *psfMyFolder;

			lpTVID.lpi = lpTVID.lpifq = pidl;

			pDesktopFolder->BindToObject(lpTVID.lpifq, NULL,
				IID_IShellFolder, (LPVOID*)&psfMyFolder);

			lpTVID.lpsfParent = psfMyFolder;
			PopulateListView(&lpTVID, lpTVID.lpsfParent);

			m_strItemPath = lpszPath;
			pDesktopFolder->Release();

			return true;
		}

		pDesktopFolder->Release();
	}

	return false;
}