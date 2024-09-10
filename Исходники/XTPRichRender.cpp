CXTPRichRender::CXTPRichRender()
{
	NONCLIENTMETRICS ncm;
	::ZeroMemory(&ncm, sizeof(ncm));
	ncm.cbSize = sizeof(ncm);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);

	HDC hDC = ::GetDC(NULL);

	::ZeroMemory(&m_charformat, sizeof(m_charformat));
	m_charformat.cbSize = sizeof(m_charformat);
	m_charformat.dwMask = CFM_BOLD | CFM_CHARSET | CFM_COLOR  |CFM_FACE | CFM_ITALIC |
		CFM_SIZE | CFM_STRIKEOUT | CFM_UNDERLINE;
	m_charformat.yHeight = -MulDiv(ncm.lfMessageFont.lfHeight, 1440, ::GetDeviceCaps(hDC, LOGPIXELSY));
	m_charformat.crTextColor = ::GetSysColor(COLOR_BTNTEXT);
	m_charformat.bPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	WCSNCPY_S(m_charformat.szFaceName, LF_FACESIZE, XTP_CT2CW(ncm.lfMessageFont.lfFaceName), LF_FACESIZE);

	::ReleaseDC(NULL,hDC);

	::ZeroMemory(&m_paraformat, sizeof(m_paraformat));
	m_paraformat.cbSize = sizeof(m_paraformat);
	m_paraformat.dwMask = PFM_ALIGNMENT | PFM_NUMBERING | PFM_OFFSET | PFM_OFFSETINDENT |
		PFM_RIGHTINDENT | PFM_RTLPARA | PFM_STARTINDENT | PFM_TABSTOPS;
	m_paraformat.wAlignment = PFA_LEFT;

	m_pTextService = NULL;

	m_hModule = LoadLibraryA("RICHED20.dll");
	if (!m_hModule)
		return;

	// Get an interface to the windowless rich edit control
	IUnknown* pUnknown = NULL;
	PCreateTextServices lpCreateTextServices = (PCreateTextServices)GetProcAddress(m_hModule, "CreateTextServices");
	HRESULT hr = lpCreateTextServices(NULL, &m_xTextHost, &pUnknown);

	if (SUCCEEDED(hr))
	{
		pUnknown->QueryInterface(IID_XTPITextServices, (void**)&m_pTextService);
		pUnknown->Release();
	}
}