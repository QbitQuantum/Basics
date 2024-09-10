BOOL CDLUpdateDlg::OnInitDialog()
{
    HRESULT hr = S_OK;
	CDialog::OnInitDialog();
	FC_DEBUGPRINT1(_T("CEDL> CDLUpdateDlg::OnInitDialog(): thread id=0x%x\n"),::GetCurrentThreadId());
	
    assert(m_pStation != NULL);
    //set the help id for context sensitive help
    SetWindowContextHelpId(IDD);
    // init the controls
    m_ImageList.Create(IDB_DOMIMAGELIST, DLG_BITMAP_WIDTH, 0, RGB(255, 0, 255));
	m_ImageList.SetBkColor(GetSysColor(COLOR_WINDOW));
	m_DomainListCtrl.SetImageList(&m_ImageList, LVSIL_SMALL);
    m_DomainListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT);
    DisplayColumnHeadings(IDS_COL_DOMAINLIST);
    m_DownloadBtn.EnableWindow(FALSE);
    m_strControlName.Format(_T("%s [%s]"), m_pStation->GetConfigName(), m_pStation->GetAddress());
    ClearProgress();
    
    // start the preparation for DL
    assert(m_pDLEvents != NULL);
    m_pDLEvents->SetListClient(this->GetSafeHwnd());

    if (m_pStation->IsRequestPending()) {
		FC_DEBUGPRINT(_T("CEDL> OnInitDialog: Download Pending\n"));
        m_pStation->FireErrorMessage(E_CE_DL_PENDING);
        m_pStation->FireError(E_CE_DL_PENDING);
    	m_strDomainName.LoadString(IDS_CONN_INTR);
        UpdateData(FALSE);
        return TRUE;
    }

	m_strDomainName.LoadString(IDS_CONN);
    UpdateData(FALSE);

	m_hSaveCursor = ::SetCursor(::LoadCursor(NULL, IDC_APPSTARTING));
	m_hwndCapture = GetSafeHwnd();
	if (m_hwndCapture) {
      ::SetCapture(m_hwndCapture);
	}

    m_pStation->SetSignal(BUILD_DL_LIST);
    m_pStation->ResetSignal(DOWN_LD);
    m_pStation->ResetSignal(DOWN_LD_ALL);
    m_pStation->ResetSignal(PRJ_NEW);
    m_pStation->ResetSignal(PRJ_CHANGED);
    m_pStation->SetState(CEDL_STAT_WAIT_CONNECT);
	m_pStation->DoStateMachine();

	if(FAILED(hr)) {
		FC_DEBUGPRINT1(_T("CEDL> OnInitDialog: failed hr= 0x%x\n"),hr);
        m_pStation->FireErrorMessage(hr);
        m_pStation->FireError(hr);
	}
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}