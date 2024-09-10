BOOL CTextPasterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// register a system wide hotkey to be handled by this window (via WM_HOTKEY messages)
	const UINT hotKeyModifiers = MOD_CONTROL | MOD_SHIFT; 
	const TCHAR hotKeyChar = _T('/');
	BOOL res = RegisterHotKey(GetSafeHwnd(),HOTKEY_ID,hotKeyModifiers,VkKeyScan(hotKeyChar));

	// set message control to have a large bold font
	LOGFONT lf = {0};
	m_MsgCtrl.GetFont()->GetLogFont(&lf);
	CDC* pDC = GetDC();
	const LONG textHeightPts = 32;
	lf.lfHeight = -MulDiv(textHeightPts, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	lf.lfWeight = FW_BOLD;
	ReleaseDC(pDC);
	textFont.CreateFontIndirectW(&lf);
	m_MsgCtrl.SetFont(&textFont);

	// initial message
	m_MsgCtrl.SetWindowText(defaultMsg);

	return TRUE;  // return TRUE  unless you set the focus to a control
}