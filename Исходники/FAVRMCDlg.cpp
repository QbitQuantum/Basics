// CFAVRMCDlg message handlers
//===========================================================================
BOOL CFAVRMCDlg::OnInitDialog()
//===========================================================================
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//! @defgroup Setting groups initialization
	//! @{
	//! @{ Key Define
	CEdit* pEditKeyDef = (CEdit*)GetDlgItem(IDC_RMC_KEYDEFINE_DATA);
	pEditKeyDef->SetWindowText(_T("SN pairing"));
	//! @}

	//! @{ Command
	CComboBox* pCMDCBox = (CComboBox*)GetDlgItem(IDC_RMC_CMD_DATA);
	pCMDCBox->InsertString(0,_T("M0"));
	pCMDCBox->InsertString(1,_T("M1"));
	pCMDCBox->SetCurSel(0);
	//! @}

	//! @{ Key
	CEdit* pEditKey = (CEdit*)GetDlgItem(IDC_RMC_KEY_DATA);
	pEditKey->SetWindowText(_T("50"));
	//! @}

	//! @{ Flag
	CComboBox* pFLAGCBox = (CComboBox*)GetDlgItem(IDC_RMC_FLAG_DATA);
	pFLAGCBox->InsertString(0,_T("0: No Double Key"));
	pFLAGCBox->InsertString(1,_T("1: Flag1"));
	pFLAGCBox->InsertString(2,_T("2: Flag2"));
	pFLAGCBox->InsertString(3,_T("3: Flag1 + Flag2"));
	pFLAGCBox->InsertString(4,_T("4: Flag3"));
	pFLAGCBox->InsertString(5,_T("5: Flag1 + Flag3"));
	pFLAGCBox->InsertString(6,_T("6: Flag2 + Flag3"));
	pFLAGCBox->SetCurSel(0);
	//! @}

	//! @{ SN
	CEdit* pEditSN = (CEdit*)GetDlgItem(IDC_RMC_SN_DATA);
	pEditSN->LimitText(8);
	pEditSN->SetWindowText(_T("FFFFFFFF"));
	pEditSN->EnableWindow(FALSE);
	//! @}

	//! @{ Number of times
	CEdit* pEditTimes = (CEdit*)GetDlgItem(IDC_RMC_TIMES_DATA);
	pEditTimes->LimitText(2);
	pEditTimes->SetWindowText(_T("37"));
	//! @}
	EnableGroupboxControls(::GetDlgItem(m_hWnd, IDC_RMC_SETTINGS), FALSE);		//Close groups
	//! @}


	//! @defgroup Send Sequences groups initialization
	//! @{
	//! @{ ListCtrl
	m_ListCtrl.InsertColumn(0, "Key Define", LVCFMT_CENTER, 100);
	m_ListCtrl.InsertColumn(1, "Command", LVCFMT_CENTER, 75);
	m_ListCtrl.InsertColumn(2, "Key", LVCFMT_CENTER, 40);
	m_ListCtrl.InsertColumn(3, "Flag", LVCFMT_CENTER, 50);
	m_ListCtrl.InsertColumn(4, "SN", LVCFMT_CENTER, 80);
	m_ListCtrl.InsertColumn(5, "Times", LVCFMT_CENTER, 40);
	m_ListCtrl.SetColumnWidth(5,LVSCW_AUTOSIZE_USEHEADER);
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle()|
		LVS_EX_FULLROWSELECT|
		LVS_EX_GRIDLINES);
	// http://msdn.microsoft.com/zh-tw/magazine/cc164140(en-us).aspx
	// Fixed column width
	CHeaderCtrl* pHeaderCtrl = (CHeaderCtrl*)m_ListCtrl.GetHeaderCtrl();
	pHeaderCtrl-> EnableWindow(FALSE);
	//! @}
	//EnableGroupboxControls(::GetDlgItem(m_hWnd, IDC_RMC_SEQUENCES), FALSE);		//Close groups
	//! @}

	// Create tooltips
	m_ToolTipsRMC.Create(this, TTS_ALWAYSTIP);
	::SendMessage(m_ToolTipsRMC.m_hWnd, TTM_SETMAXTIPWIDTH, 0, SHRT_MAX);
	CString str = _T("");
	str.Format(_T("Power"));
	m_ToolTipsRMC.AddTool(GetDlgItem(IDC_RMC_DEMO_POWER), str);
	str.Format(_T("Light OFF"));
	m_ToolTipsRMC.AddTool(GetDlgItem(IDC_RMC_DEMO_BULBOFF), str);

	CRect BtnRectPower; 
	m_ButtonPower.GetWindowRect(BtnRectPower);
	ScreenToClient(BtnRectPower);
	m_ButtonPower.SetBackBmp(IDB_RMCDEMO_BK1, BtnRectPower);
	m_ButtonPower.SetRgnStyle(0);
	m_ButtonPower.SetRgnMask(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonPower.SetMaskBitmapId(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonPower.SetBitmapId(0, IDB_RMCDEMO_POWER_NOMAL, IDB_RMCDEMO_POWER_MOVE,
		IDB_RMCDEMO_POWER_DOWN, IDB_RMCDEMO_POWER_MOVE);

	CRect BtnRectBulbOFF; 
	m_ButtonBulbOFF.GetWindowRect(BtnRectBulbOFF);
	ScreenToClient(BtnRectBulbOFF);
	m_ButtonBulbOFF.SetBackBmp(IDB_RMCDEMO_BK1, BtnRectBulbOFF);
	m_ButtonBulbOFF.SetRgnStyle(0);
	m_ButtonBulbOFF.SetRgnMask(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonBulbOFF.SetMaskBitmapId(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonBulbOFF.SetBitmapId(1, IDB_RMCDEMO_BULBOFF_NORMAL, IDB_RMCDEMO_BULBOFF_MOVE,
		IDB_RMCDEMO_BULBOFF_DOWN, IDB_RMCDEMO_BULBOFF_MOVE);

	CRect BtnRectBulbON; 
	m_ButtonBulbON.GetWindowRect(BtnRectBulbON);
	ScreenToClient(BtnRectBulbON);
	m_ButtonBulbON.SetBackBmp(IDB_RMCDEMO_BK1, BtnRectBulbON);
	m_ButtonBulbON.SetRgnStyle(0);
	m_ButtonBulbON.SetRgnMask(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonBulbON.SetMaskBitmapId(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonBulbON.SetBitmapId(2, IDB_RMCDEMO_BULBON_NORMAL, IDB_RMCDEMO_BULBON_MOVE,
		IDB_RMCDEMO_BULBON_DOWN, IDB_RMCDEMO_BULBON_MOVE);

	CRect BtnRectBON; 
	m_ButtonBuleON.GetWindowRect(BtnRectBON);
	ScreenToClient(BtnRectBON);
	m_ButtonBuleON.SetBackBmp(IDB_RMCDEMO_BK1, BtnRectBON);
	m_ButtonBuleON.SetRgnStyle(0);
	m_ButtonBuleON.SetRgnMask(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonBuleON.SetMaskBitmapId(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonBuleON.SetBitmapId(3, IDB_RMCDEMO_BON_NORMAL, IDB_RMCDEMO_BON_MOVE,
		IDB_RMCDEMO_BON_DOWN, IDB_RMCDEMO_BON_MOVE);

	CRect BtnRectBOFF; 
	m_ButtonBuleOFF.GetWindowRect(BtnRectBOFF);
	ScreenToClient(BtnRectBOFF);
	m_ButtonBuleOFF.SetBackBmp(IDB_RMCDEMO_BK1, BtnRectBOFF);
	m_ButtonBuleOFF.SetRgnStyle(0);
	m_ButtonBuleOFF.SetRgnMask(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonBuleOFF.SetMaskBitmapId(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonBuleOFF.SetBitmapId(4, IDB_RMCDEMO_BOFF_NOMAL, IDB_RMCDEMO_BOFF_MOVE,
		IDB_RMCDEMO_BOFF_DOWN, IDB_RMCDEMO_BOFF_MOVE);

	CRect BtnRectGON; 
	m_ButtonGreenON.GetWindowRect(BtnRectGON);
	ScreenToClient(BtnRectGON);
	m_ButtonGreenON.SetBackBmp(IDB_RMCDEMO_BK1, BtnRectGON);
	m_ButtonGreenON.SetRgnStyle(0);
	m_ButtonGreenON.SetRgnMask(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonGreenON.SetMaskBitmapId(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonGreenON.SetBitmapId(5, IDB_RMCDEMO_GON_NORMAL, IDB_RMCDEMO_GON_MOVE,
		IDB_RMCDEMO_GON_DOWN, IDB_RMCDEMO_GON_MOVE);

	CRect BtnRectGOFF; 
	m_ButtonGreenOFF.GetWindowRect(BtnRectGOFF);
	ScreenToClient(BtnRectGOFF);
	m_ButtonGreenOFF.SetBackBmp(IDB_RMCDEMO_BK1, BtnRectGOFF);
	m_ButtonGreenOFF.SetRgnStyle(0);
	m_ButtonGreenOFF.SetRgnMask(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonGreenOFF.SetMaskBitmapId(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonGreenOFF.SetBitmapId(6, IDB_RMCDEMO_GOFF_NORMAL, IDB_RMCDEMO_GOFF_MOVE,
		IDB_RMCDEMO_GOFF_DOWN, IDB_RMCDEMO_GOFF_MOVE);

	CRect BtnRectRON; 
	m_ButtonRedON.GetWindowRect(BtnRectRON);
	ScreenToClient(BtnRectRON);
	m_ButtonRedON.SetBackBmp(IDB_RMCDEMO_BK1, BtnRectRON);
	m_ButtonRedON.SetRgnStyle(0);
	m_ButtonRedON.SetRgnMask(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonRedON.SetMaskBitmapId(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonRedON.SetBitmapId(7, IDB_RMCDEMO_RON_NORMAL, IDB_RMCDEMO_RON_MOVE,
		IDB_RMCDEMO_RON_DOWN, IDB_RMCDEMO_RON_MOVE);

	CRect BtnRectROFF; 
	m_ButtonRedOFF.GetWindowRect(BtnRectROFF);
	ScreenToClient(BtnRectROFF);
	m_ButtonRedOFF.SetBackBmp(IDB_RMCDEMO_BK1, BtnRectROFF);
	m_ButtonRedOFF.SetRgnStyle(0);
	m_ButtonRedOFF.SetRgnMask(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonRedOFF.SetMaskBitmapId(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonRedOFF.SetBitmapId(8, IDB_RMCDEMO_ROFF_NORMAL, IDB_RMCDEMO_ROFF_MOVE,
		IDB_RMCDEMO_ROFF_DOWN, IDB_RMCDEMO_ROFF_MOVE);

	CRect BtnRectPair; 
	m_ButtonPair.GetWindowRect(BtnRectPair);
	ScreenToClient(BtnRectPair);
	m_ButtonPair.SetBackBmp(IDB_RMCDEMO_BK1, BtnRectPair);
	m_ButtonPair.SetRgnStyle(0);
	m_ButtonPair.SetRgnMask(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonPair.SetMaskBitmapId(IDB_RMCDEMO_MASK, TRUE);
	m_ButtonPair.SetBitmapId(9, IDB_RMCDEMO_PAIR_NORMAL, IDB_RMCDEMO_PAIR_MOVE,
		IDB_RMCDEMO_PAIR_DOWN, IDB_RMCDEMO_PAIR_MOVE);



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}