BOOL CDlgCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	// Set the application's icon.
	//
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	//
	// Remove the Size and Maximize commands from the system menu.
	//
	CMenu* pMenu = GetSystemMenu (FALSE);
	pMenu->DeleteMenu (SC_SIZE, MF_BYCOMMAND);
	pMenu->DeleteMenu (SC_MAXIMIZE, MF_BYCOMMAND);

	//
	// Initialize m_rect with the coordinates of the control representing
	// the calculator's output window. Then destroy the control.
	//
	CWnd* pWnd = GetDlgItem (IDC_DISPLAYRECT);
	pWnd->GetWindowRect (&m_rect);
	pWnd->DestroyWindow ();
	ScreenToClient (&m_rect);

	//
	// Initialize m_cxChar and m_cyChar with the average character width
	// and height.
	//
    TEXTMETRIC tm;
    CClientDC dc (this);
    dc.GetTextMetrics (&tm);
    m_cxChar = tm.tmAveCharWidth;
    m_cyChar = tm.tmHeight - tm.tmDescent;

	//
	// Initialize the calculator's output window and return.
	//
    DisplayXRegister ();
	return TRUE;
}