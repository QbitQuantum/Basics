int CIconList::CreateTabIcon(LPCWSTR asIconDescr, bool bAdmin)
{
	if (!asIconDescr || !*asIconDescr)
		return GetTabIcon(bAdmin);

	for (INT_PTR i = 0; i < m_Icons.size(); i++)
	{
		const TabIconCache& icn = m_Icons[i];
		if ((icn.bAdmin!=FALSE) != bAdmin)
			continue;
		if (lstrcmpi(icn.pszIconDescr, asIconDescr) != 0)
			continue;
		// Already was created!
		return icn.nIconIdx;
	}

	wchar_t* pszExpanded = ExpandEnvStr(asIconDescr);

	// Need to be created!
	int iIconIdx = -1;
	HICON hFileIcon = NULL;
	wchar_t szTemp[MAX_PATH];
	LPCWSTR pszLoadFile = pszExpanded ? pszExpanded : asIconDescr;
	LPCWSTR lpszExt = (wchar_t*)PointToExt(pszLoadFile);

	if (!lpszExt)
	{
		LPWSTR pszFile = NULL;
		if (SearchPath(NULL, pszLoadFile, L".exe", countof(szTemp), szTemp, &pszFile))
		{
			pszLoadFile = szTemp;
			lpszExt = (wchar_t*)PointToExt(pszLoadFile);
		}

		if (!lpszExt)
			goto wrap;
	}

	if (lstrcmpi(lpszExt, L".ico") == 0)
	{
		hFileIcon = (HICON)LoadImage(0, pszLoadFile, IMAGE_ICON,
			                            GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR|LR_LOADFROMFILE);
    }
    else if ((lstrcmpi(lpszExt, L".exe") == 0) || (lstrcmpi(lpszExt, L".dll") == 0))
    {
		//TODO: May be specified index of an icon in the file
		HICON hIconLarge = NULL;
        ExtractIconEx(pszLoadFile, 0, &hIconLarge, &hFileIcon, 1);
		if (hIconLarge) DestroyIcon(hIconLarge);
    }
	else
	{
		//TODO: Shell icons for registered files (cmd, bat, sh, pl, py, ...)
	}

	if (hFileIcon)
	{
		int iIconIdxAdm = -1;
		iIconIdx = ImageList_ReplaceIcon(mh_TabIcons, -1, hFileIcon);

		TabIconCache NewIcon = {lstrdup(asIconDescr), false, iIconIdx};
		m_Icons.push_back(NewIcon);

		HIMAGELIST hAdmList = ImageList_Merge(mh_TabIcons, iIconIdx, mh_TabIcons, mn_AdminIcon+2, 0,0);
		if (hAdmList)
		{
			HICON hNewIcon = ImageList_GetIcon(hAdmList, 0, ILD_TRANSPARENT);
			if (hNewIcon)
			{
				iIconIdxAdm = ImageList_ReplaceIcon(mh_TabIcons, -1, hNewIcon);
				DestroyIcon(hNewIcon);

				TabIconCache AdmIcon = {lstrdup(asIconDescr), true, iIconIdxAdm};
				m_Icons.push_back(AdmIcon);

				if (bAdmin && (iIconIdxAdm > 0))
				{
					iIconIdx = iIconIdxAdm;
				}
			}
		}

		//TODO: bAdmin!!!

		DestroyIcon(hFileIcon);
	}

wrap:
	SafeFree(pszExpanded);
	return iIconIdx;
}