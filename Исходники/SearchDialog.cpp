void CSearchDialog::StartSearching()
{
	ShowWindow(GetDlgItem(m_hDlg, IDC_LINK_STATUS), SW_HIDE);
	ShowWindow(GetDlgItem(m_hDlg, IDC_STATIC_STATUS), SW_SHOW);

	m_AwaitingSearchItems.clear();
	m_SearchItemsMapInternal.clear();

	ListView_DeleteAllItems(GetDlgItem(m_hDlg, IDC_LISTVIEW_SEARCHRESULTS));

	TCHAR szBaseDirectory[MAX_PATH];
	TCHAR szSearchPattern[MAX_PATH];

	/* Get the directory and name, and remove leading and
	trailing whitespace. */
	/* TODO: Verify fields. */
	GetDlgItemText(m_hDlg, IDC_COMBO_DIRECTORY, szBaseDirectory,
		SIZEOF_ARRAY(szBaseDirectory));
	PathRemoveBlanks(szBaseDirectory);
	GetDlgItemText(m_hDlg, IDC_COMBO_NAME, szSearchPattern,
		SIZEOF_ARRAY(szSearchPattern));
	PathRemoveBlanks(szSearchPattern);

	BOOL bSearchSubFolders = IsDlgButtonChecked(m_hDlg, IDC_CHECK_SEARCHSUBFOLDERS) ==
		BST_CHECKED;

	BOOL bUseRegularExpressions = IsDlgButtonChecked(m_hDlg, IDC_CHECK_USEREGULAREXPRESSIONS) ==
		BST_CHECKED;

	BOOL bCaseInsensitive = IsDlgButtonChecked(m_hDlg, IDC_CHECK_CASEINSENSITIVE) ==
		BST_CHECKED;

	/* Turn search patterns of the form '???' into '*???*', and
	use this modified string to search. */
	if(!bUseRegularExpressions && lstrlen(szSearchPattern) > 0)
	{
		if(szSearchPattern[0] != '*' &&
			szSearchPattern[lstrlen(szSearchPattern) - 1] != '*')
		{
			TCHAR szTemp[MAX_PATH];

			StringCchPrintf(szTemp, SIZEOF_ARRAY(szTemp), _T("*%s*"),
				szSearchPattern);
			StringCchCopy(szSearchPattern, SIZEOF_ARRAY(szSearchPattern),
				szTemp);
		}
	}

	DWORD dwAttributes = 0;

	if(IsDlgButtonChecked(m_hDlg, IDC_CHECK_ARCHIVE) == BST_CHECKED)
		dwAttributes |= FILE_ATTRIBUTE_ARCHIVE;

	if(IsDlgButtonChecked(m_hDlg, IDC_CHECK_HIDDEN) == BST_CHECKED)
		dwAttributes |= FILE_ATTRIBUTE_HIDDEN;

	if(IsDlgButtonChecked(m_hDlg, IDC_CHECK_READONLY) == BST_CHECKED)
		dwAttributes |= FILE_ATTRIBUTE_READONLY;

	if(IsDlgButtonChecked(m_hDlg, IDC_CHECK_SYSTEM) == BST_CHECKED)
		dwAttributes |= FILE_ATTRIBUTE_SYSTEM;

	m_pSearch = new CSearch(m_hDlg, szBaseDirectory, szSearchPattern,
		dwAttributes, bUseRegularExpressions, bCaseInsensitive, bSearchSubFolders);
	m_pSearch->AddRef();

	/* Save the search directory and search pattern (only if they are not
	the same as the most recent entry). */
	BOOL bSaveEntry = FALSE;

	if(m_sdps->m_pSearchDirectories->empty() ||
		lstrcmp(szBaseDirectory, m_sdps->m_pSearchDirectories->begin()->c_str()) != 0)
	{
		bSaveEntry = TRUE;
	}

	if(bSaveEntry)
	{
		SaveEntry(IDC_COMBO_DIRECTORY, *m_sdps->m_pSearchDirectories);
	}

	bSaveEntry = FALSE;

	if(m_sdps->m_pSearchPatterns->empty() ||
		lstrcmp(szSearchPattern, m_sdps->m_pSearchPatterns->begin()->c_str()) != 0)
	{
		bSaveEntry = TRUE;
	}

	if(bSaveEntry)
	{
		SaveEntry(IDC_COMBO_NAME, *m_sdps->m_pSearchPatterns);
	}

	GetDlgItemText(m_hDlg, IDSEARCH, m_szSearchButton, SIZEOF_ARRAY(m_szSearchButton));

	TCHAR szTemp[64];

	LoadString(GetInstance(), IDS_STOP, szTemp, SIZEOF_ARRAY(szTemp));
	SetDlgItemText(m_hDlg, IDSEARCH, szTemp);

	m_bSearching = TRUE;

	/* Create a background thread, and search using it... */
	HANDLE hThread = CreateThread(NULL, 0, NSearchDialog::SearchThread,
		reinterpret_cast<LPVOID>(m_pSearch), 0, NULL);
	CloseHandle(hThread);
}