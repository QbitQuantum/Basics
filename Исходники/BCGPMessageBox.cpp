void CBCGPMessageBox::Initialize ()
{
	CWnd* pParent = CWnd::FromHandle (m_Params.hwndOwner);

	if (pParent == NULL)
	{
		pParent = CWnd::GetActiveWindow();

		if (pParent != NULL)
		{
			CWnd* pPopup = pParent->GetLastActivePopup();

			if (pPopup != NULL)
			{
				pParent = pPopup;
			}
		}
	}

	// Loading an icon

	LPTSTR iconID = NULL;

	switch (m_Params.dwStyle & MB_ICONMASK)
	{
	case MB_ICONASTERISK:
		iconID = IDI_ASTERISK;
		break;
	case MB_ICONEXCLAMATION:
		iconID = IDI_EXCLAMATION;
		break;
	case MB_ICONHAND:
		iconID = IDI_HAND;
		break;
	case MB_ICONQUESTION:
		iconID = IDI_QUESTION;
		break;
	}

	m_hMessageIcon = NULL;
	if (iconID)
	{
		m_hMessageIcon = ::LoadIcon (NULL, MAKEINTRESOURCE(iconID));
	}

	if (m_Params.dwStyle & MB_USERICON)
	{
		m_hMessageIcon = ::LoadIcon (m_Params.hInstance, m_Params.lpszIcon);
	}

	m_rectIcon.SetRectEmpty ();
	if (m_hMessageIcon != NULL)
	{
		m_rectIcon.right = ::GetSystemMetrics(SM_CXICON);
		m_rectIcon.bottom = ::GetSystemMetrics(SM_CYICON);
	}

	m_strMessageCaption = GetString (m_Params.lpszCaption, _T("Error"));
	m_strMessageText = GetString (m_Params.lpszText);
	m_strCheckBox = GetString (m_Params.lpszCheckBoxText);

	switch (m_Params.dwStyle & MB_DEFMASK)
	{
	case MB_DEFBUTTON1:
		m_nDefaultButtonIndex = 0;
		break;
	case MB_DEFBUTTON2:
		m_nDefaultButtonIndex = 1;
		break;
	case MB_DEFBUTTON3:
		m_nDefaultButtonIndex = 2;
		break;
	case MB_DEFBUTTON4:
		m_nDefaultButtonIndex = 3;
		break;
	default:
		m_nDefaultButtonIndex = -1;
		break;
	}

	// Creating dialog template

	m_pTemplate = (DLGTEMPLATE*)::GlobalAlloc (GPTR, 1024);

	m_pTemplate->x = 0;
	m_pTemplate->y = 0;
	m_pTemplate->cx = 62;
	m_pTemplate->cy = 40;
	m_pTemplate->cdit = 0;

	m_pTemplate->style = WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_POPUP | DS_MODALFRAME | DS_CENTER;

	m_pTemplate->dwExtendedStyle = 0;

	m_bRightAlignment = (m_Params.dwStyle & MB_RIGHT) != 0;

	if (m_Params.dwStyle & MB_RTLREADING)
	{
		//// Uncomment to enable RTL
		//m_pTemplate->dwExtendedStyle |= WS_EX_LAYOUTRTL;
		//m_bRightAlignment = !m_bRightAlignment;
	}

	if (m_Params.dwStyle & MB_SYSTEMMODAL)
	{
		m_pTemplate->style |= DS_SYSMODAL;
	}

	WORD* pEnd = (WORD*)(m_pTemplate + 1);
	*pEnd = 0;

	InitModalIndirect (m_pTemplate, pParent);

	// Calculating margins, sizes and spacings
	m_rectClientMargins.SetRect (7, 7, 5, 7);
	m_szButton.cx = 52;
	m_szButton.cy = 14;
	m_cxIconSpacing = 12; // spacing between an icon and message text
	m_cyCheckBoxHeight = 10;
	m_cxButtonSpacing = 4; // gap between buttons
	m_cyVerticalSpacing = 11; // vertical spacing between text, optional check box and buttons
}