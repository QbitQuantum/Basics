BOOL CSelectDrivesDlg::OnInitDialog()
{
	CWaitCursor wc;

	CDialog::OnInitDialog();

	if (WMU_THREADFINISHED == 0)
	{
		TRACE("RegisterMessage() failed. Using WM_USER + 123\r\n");
		WMU_THREADFINISHED = WM_USER + 123;
	}

	ModifyStyle(0, WS_CLIPCHILDREN);

	m_layout.AddControl(IDOK,				1, 0, 0, 0);
	m_layout.AddControl(IDCANCEL,			1, 0, 0, 0);
	m_layout.AddControl(IDC_DRIVES,			0, 0, 1, 1);
	m_layout.AddControl(IDC_AFOLDER,		0, 1, 0, 0);
	m_layout.AddControl(IDC_FOLDERNAME,		0, 1, 1, 0);
	m_layout.AddControl(IDC_BROWSEFOLDER,	1, 1, 0, 0);

	m_layout.OnInitDialog(true);

	m_list.ShowGrid(GetOptions()->IsListGrid());
	m_list.ShowStripes(GetOptions()->IsListStripes());
	m_list.ShowFullRowSelection(GetOptions()->IsListFullRowSelection());

	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_HEADERDRAGDROP);
	// If we set an ImageList here, OnMeasureItem will have no effect ?!

	m_list.InsertColumn(COL_NAME,		LoadString(IDS_DRIVECOL_NAME),		LVCFMT_LEFT, 120, COL_NAME);
	m_list.InsertColumn(COL_TOTAL,		LoadString(IDS_DRIVECOL_TOTAL),		LVCFMT_RIGHT, 55, COL_TOTAL);
	m_list.InsertColumn(COL_FREE,		LoadString(IDS_DRIVECOL_FREE),		LVCFMT_RIGHT, 55, COL_FREE);
	m_list.InsertColumn(COL_GRAPH,		LoadString(IDS_DRIVECOL_GRAPH),		LVCFMT_LEFT, 100, COL_GRAPH);
	m_list.InsertColumn(COL_PERCENTUSED,LoadString(IDS_DRIVECOL_PERCENTUSED),LVCFMT_RIGHT, 55, COL_PERCENTUSED);

	m_list.OnColumnsInserted();

	m_folderName= CPersistence::GetSelectDrivesFolder();
	CPersistence::GetSelectDrivesDrives(m_selectedDrives);

	ShowWindow(SW_SHOWNORMAL);
	UpdateWindow();
	BringWindowToTop();
	SetForegroundWindow();

	DWORD drives= GetLogicalDrives();
	int i;
	DWORD mask= 0x00000001;
	for (i=0; i < 32; i++, mask <<= 1)
	{
		if ((drives & mask) == 0)
			continue;

		CString s;
		s.Format(_T("%c:\\"), i + _T('A'));

		UINT type= GetDriveType(s);
		if (type == DRIVE_UNKNOWN || type == DRIVE_NO_ROOT_DIR)
			continue;

		// The check of remote drives will be done in the backgound by the CDriveInformationThread.
		if (type != DRIVE_REMOTE && !DriveExists(s))
			continue;

		CDriveItem *item= new CDriveItem(&m_list, s);
		m_list.InsertListItem(m_list.GetItemCount(), item);
		item->StartQuery(m_hWnd, _serial);

		for (int k=0; k < m_selectedDrives.GetSize(); k++)
		{
			if (item->GetDrive() == m_selectedDrives[k])
			{
				m_list.SelectItem(item);
				break;
			}
		}
	}

	m_list.SortItems();

	m_radio= CPersistence::GetSelectDrivesRadio();
	UpdateData(false);

	switch (m_radio)
	{
	case RADIO_ALLLOCALDRIVES:
	case RADIO_AFOLDER:
		m_okButton.SetFocus();
		break;
	case RADIO_SOMEDRIVES:
		m_list.SetFocus();
		break;
	}

	UpdateButtons();
	return false; // we have set the focus.
}