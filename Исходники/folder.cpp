BOOL CFolder::OnInitDialog() 
{
	CDialog::OnInitDialog();

	HTREEITEM	hPar;
	CString		csTitle;
	DWORD       dwLen;
	DWORD		i;
	int			nType;
	WCHAR		*p;
	WCHAR		szLetter[4];
	WCHAR		szDrivesLetter[MAX_PATH];
	CBitmap     Bitmap;
	
	if (m_bShowFile)
	{
		csTitle.LoadString(IDS_SELECT_FILE_OR_DIR);
		SetWindowText(csTitle);
	}
	Bitmap.LoadBitmap(IDB_TREE);
	m_ImageList.Create(16,16,ILC_COLOR16,0,10);
	m_ImageList.Add(&Bitmap, RGB(0,0,0));
	m_Tree.SetImageList(&m_ImageList, TVSIL_NORMAL);

	dwLen = GetLogicalDriveStrings(0,NULL);
	::GetLogicalDriveStrings(dwLen,szDrivesLetter);
	_wcsupr( szDrivesLetter );
	p = szDrivesLetter;

	dwLen = dwLen/4;
	for(i = 0;i<dwLen;i++)
	{
		wcscpy(szLetter,p);
		//szLetter[2] = 0;
		nType = GetLetterType(szLetter);
		szLetter[2] = 0;
		if (nType < 7)
		{
			hPar = m_Tree.InsertItem(szLetter, nType, nType);
			m_Tree.SetItemData(hPar, 1);
			CreateFolder(szLetter, &m_Tree, hPar);
			m_Tree.SortChildren(hPar);
		}
		p += 4;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}