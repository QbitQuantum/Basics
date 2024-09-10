// CRotateDlg message handlers
BOOL CRotateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_AngleIcons.Create(16, 16, ILC_COLOR24 | ILC_MASK, 3, 3);

	HBITMAP icon = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ANGLEICONS));

	ImageList_Add(m_AngleIcons, icon, NULL);

	DeleteObject(icon);

	m_Angle.SetImageList(&m_AngleIcons);
	m_Angle.SetWindowText("0");

	for (int i = 0; i < 8; i++)
	{
		COMBOBOXEXITEM insItem;
		insItem.mask = CBEIF_IMAGE | CBEIF_TEXT | CBEIF_SELECTEDIMAGE; 
		insItem.iItem = i;
		insItem.iImage = i;
		insItem.iSelectedImage = i;

		CString Text;
		Text.Format("%d", i * 45);
		insItem.pszText = Text.GetBuffer(0);
		m_Angle.InsertItem(&insItem);
	}

	m_Angle.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}