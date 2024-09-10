void CAddress::Create(HWND hParent, long ID, HINSTANCE hInst)
{
	InitCommonControls();
	m_hInst = hInst;
	m_hParent = hParent;
	m_hAddress = CreateWindow(TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | TBSTYLE_LIST,
		0, 100, 100, 200,
		m_hParent, (HMENU) ID, m_hInst, NULL);
	m_nID = ID;
	SetButtonImages();
	AddNonButtonControl(_T("STATIC"), _T("Address"), WS_CHILD | WS_VISIBLE, 
			IDC_ADDRESS_STATIC, 50, 50, 0, IDC_ADDRESS_STATIC, 3);
	HFONT hFont = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(GetDlgItem(m_hAddress, IDC_ADDRESS_STATIC), WM_SETFONT, (WPARAM) hFont, TRUE);

	RECT main;
	GetWindowRect(m_hParent, &main);
	AddNonButtonControl(_T("EDIT"), NULL, WS_CHILD | WS_VISIBLE, 
		IDC_ADDRESS_EDIT, 900, 20, 1, IDC_ADDRESS_EDIT, 1);
	SendMessage(GetDlgItem(m_hAddress, IDC_ADDRESS_EDIT), WM_SETFONT, (WPARAM) hFont, TRUE);

	AddButton(TBSTATE_ENABLED, BTNS_BUTTON, 0 , IDC_ADDRESS_GO, _T("Go"), 0);
}