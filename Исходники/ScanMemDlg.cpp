BOOL CScanMemDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (m_pFvdBlock == NULL) {
        MessageBox (_T("Database error."), DEFCAPTION, MB_ICONERROR);
        EndDialog (0);
        return TRUE;
    }

    //m_enumMemObjArray.EnumObjects ();
    //if (m_enumMemObjArray.GetSize() == 0) {
    //    EndDialog (0);
    //    return TRUE;
    //}
    //m_enumStObjArray.EnumObjects ();
    m_enumMWObjArray.EnumObjects(ET_ALL);
    if (m_enumMWObjArray.GetSize() == 0) {
        EndDialog (0);
        return TRUE;
    }

    m_wndLvScanResult.SetExtendedStyle ( LVS_EX_CHECKBOXES | LVS_EX_FLATSB | LVS_EX_FULLROWSELECT |
        LVS_EX_GRIDLINES );
    int i = 0;
    m_wndLvScanResult.InsertColumn (i++, _T("File Name"), LVCFMT_LEFT, 250);
    m_wndLvScanResult.InsertColumn (i++, _T("Virus Name"), LVCFMT_LEFT, 160);
    m_wndLvScanResult.InsertColumn (i, _T("Information"), LVCFMT_LEFT, 220);

	// init the tooltip
	m_toolTipCtrl.Create(this);
	CWnd* pLblFilePath = GetDlgItem(IDC_LBLSCANFILE);
	RECT rect;
	pLblFilePath->GetClientRect(&rect);
	pLblFilePath->MapWindowPoints(this, &rect);
	m_toolTipCtrl.AddTool(this, _T(""), &rect, IDC_LBLSCANFILE);

    CScanMemDlg* pclsParam = this;
    m_pThread = ::AfxBeginThread (ThreadMemFunc, pclsParam);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}