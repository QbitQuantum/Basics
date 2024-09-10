BOOL CNewBehaviorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Add movements to dialog
	POSITION pos = g_dlls->GetStartPosition();
	DWORD    nKey;
	OINFO*   oInfo;

	m_Images.Create(32, 32, ILC_COLOR24, 3, 3);
	ListView_SetImageList(m_List.m_hWnd, m_Images.m_hImageList, LVSIL_NORMAL);

	vector<OINFO*> sorted;

	while (pos != NULL)
	{ 
		// locate the object DLL to use
		g_dlls->GetNextAssoc(pos, nKey, oInfo);

		if (oInfo->ideFlags & OF_MOVEMENTPLUGIN) 
		{
			sorted.push_back(oInfo);
		}
	}

	sort(sorted.begin(), sorted.end(), BehaviorSortFunction);

	for (int i = 0; i < sorted.size(); i++)
	{
		int icon = ImageList_Add(m_Images.m_hImageList, sorted[i]->hLargeIcon, NULL);

		int item = m_List.InsertItem(m_List.GetItemCount(), sorted[i]->extName, icon);
		behaviors.push_back(sorted[i]->oID);
	}

	// Resizing
	dlgMan.Load(this->m_hWnd, "Software\\Construct\\NewBehaviorDialog");
    dlgAnchor.Init(this->m_hWnd);

	dlgAnchor.Add(IDC_LIST, ANCHOR_TOPLEFT | ANCHOR_BOTTOMRIGHT);
	dlgAnchor.Add(IDOK, ANCHOR_RIGHT | ANCHOR_TOP);
	dlgAnchor.Add(IDCANCEL, ANCHOR_RIGHT | ANCHOR_TOP);
	dlgAnchor.Add(IDC_INFO, ANCHOR_BOTTOM | ANCHOR_LEFT);

	// Change title
	CString Title;
	Title.Format("Construct : %s", PROPERTIES_NEWMOVEMENT);
	SetWindowText(Title);

	m_Cancel.SetWindowText(CANCEL);
	m_OK.SetWindowText(INSERT);
	m_OK.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}