void CXUIDatePicker::Init()
{
	DWORD wStyle = WS_CHILD | WS_TABSTOP;

	if(m_showNone)	wStyle |= DTS_SHOWNONE;
	if(m_useSpin)	wStyle |= DTS_UPDOWN;
	switch(m_format)
	{
	case XUI_DATE_FORMAT_LONG:
		wStyle |= DTS_LONGDATEFORMAT;
		break;
	case XUI_DATE_FORMAT_TIME:
		wStyle |= DTS_TIMEFORMAT;
		break;
	default:
		wStyle |= DTS_SHORTDATEFORMAT;
		break;
	}

	if(get_disabled())	wStyle |= WS_DISABLED;
	if(!get_hidden())	wStyle |= WS_VISIBLE;

	m_hWnd = CreateWindowEx(0, DATETIMEPICK_CLASS, L"", wStyle, m_left, m_top, m_width, m_height, m_parent->get_parentWnd(), (HMENU) m_id, m_engine->get_hInstance(), NULL);

	RECT rcDlg = {0, 0, 100, 14};
	if(m_width) rcDlg.right = m_width;
	if(m_height) rcDlg.bottom = m_height;
	MapDialogRect(m_parent->get_parentWnd(), &rcDlg);
	m_minWidth	= rcDlg.right;
	m_minHeight = rcDlg.bottom;

	CXUIElement::Init();
}