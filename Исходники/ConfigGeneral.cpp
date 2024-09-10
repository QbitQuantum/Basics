BOOL CConfigGeneral::OnInitDialog()
{
	char Text[64];

	CPropertyPage::OnInitDialog();

	m_bWrapCursor		= theApp.GetSettings()->General.bWrapCursor;
	m_bWrapFrames		= theApp.GetSettings()->General.bWrapFrames;
	m_bFreeCursorEdit	= theApp.GetSettings()->General.bFreeCursorEdit;
	m_bPreviewWAV		= theApp.GetSettings()->General.bWavePreview;
	m_bKeyRepeat		= theApp.GetSettings()->General.bKeyRepeat;
	m_bRowInHex			= theApp.GetSettings()->General.bRowInHex;
	m_iEditStyle		= theApp.GetSettings()->General.iEditStyle;
	m_bFramePreview		= theApp.GetSettings()->General.bFramePreview;
	m_bNoDPCMReset		= theApp.GetSettings()->General.bNoDPCMReset;
	m_bNoStepMove		= theApp.GetSettings()->General.bNoStepMove;
	m_iPageStepSize		= theApp.GetSettings()->General.iPageStepSize;
	m_bPullUpDelete		= theApp.GetSettings()->General.bPullUpDelete;
	m_bBackups			= theApp.GetSettings()->General.bBackups;
	m_bSingleInstance	= theApp.GetSettings()->General.bSingleInstance;

	m_iKeyNoteCut		= theApp.GetSettings()->Keys.iKeyNoteCut; 
	m_iKeyNoteRelease	= theApp.GetSettings()->Keys.iKeyNoteRelease; 
	m_iKeyClear			= theApp.GetSettings()->Keys.iKeyClear; 
	m_iKeyRepeat		= theApp.GetSettings()->Keys.iKeyRepeat;

	GetKeyNameText(MapVirtualKey(m_iKeyNoteCut, MAPVK_VK_TO_VSC) << 16, Text, 64);
	SetDlgItemText(IDC_KEY_NOTE_CUT, Text);
	GetKeyNameText(MapVirtualKey(m_iKeyNoteRelease, MAPVK_VK_TO_VSC) << 16, Text, 64);
	SetDlgItemText(IDC_KEY_NOTE_RELEASE, Text);
	GetKeyNameText(MapVirtualKey(m_iKeyClear, MAPVK_VK_TO_VSC) << 16, Text, 64);
	SetDlgItemText(IDC_KEY_CLEAR, Text);
	GetKeyNameText(MapVirtualKey(m_iKeyRepeat, MAPVK_VK_TO_VSC) << 16, Text, 64);
	SetDlgItemText(IDC_KEY_REPEAT, Text);

	EnableToolTips(TRUE);

	m_wndToolTip.Create(this, TTS_ALWAYSTIP);
	m_wndToolTip.Activate(TRUE);

	CWnd *pWndChild = GetWindow(GW_CHILD);
	CString strToolTip;

	while (pWndChild) {
		int nID = pWndChild->GetDlgCtrlID();
		if (strToolTip.LoadString(nID)) {
			m_wndToolTip.AddTool(pWndChild, strToolTip);
		}
		pWndChild = pWndChild->GetWindow(GW_HWNDNEXT);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}