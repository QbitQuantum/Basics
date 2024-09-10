bool CAviReportWnd::DoModal(CAviFile* pAF, bool fHideChecked, bool fShowWarningText)
{
	m_nChunks = 0;
	m_rtDur = 0;

	for(int i = 0; i < (int)pAF->m_avih.dwStreams; i++)
	{
		int cnt = pAF->m_strms[i]->cs2.GetCount();
		if(cnt <= 0) continue;
		CAviFile::strm_t::chunk2& c2 = pAF->m_strms[i]->cs2[cnt-1];
		m_nChunks = max(m_nChunks, c2.n);
		m_rtDur = max(m_rtDur, (REFERENCE_TIME)c2.t<<13);
	}

	CRect r, r2;
	GetDesktopWindow()->GetWindowRect(r);
	r.DeflateRect(r.Width()/4, r.Height()/4);

	LPCTSTR wndclass = AfxRegisterWndClass(
		CS_VREDRAW|CS_HREDRAW|CS_DBLCLKS, 
		AfxGetApp()->LoadStandardCursor(IDC_ARROW), 
		(HBRUSH)(COLOR_BTNFACE + 1), 0);

	CreateEx(0, wndclass, TITLE, WS_POPUPWINDOW|WS_CAPTION|WS_CLIPCHILDREN, r, NULL, 0);

	CRect cr;
	GetClientRect(cr);
	cr.DeflateRect(10, 10);

	SetFont(&m_font, FALSE);

	CDC* pDC = GetDC();
	CFont* pOldFont = pDC->SelectObject(&m_font);

	//

	CString str(
		_T("This AVI file was not prepared for sequential reading, the alternative ")
		_T("'Avi Splitter' will now let the default one handle it. ")
		_T("The complete reinterleaving of this file is strongly recommended before ")
		_T("burning it onto a slow media like cd-rom."));

	r = cr;

	pDC->DrawText(str, r, DT_WORDBREAK|DT_CALCRECT);
	r.right = cr.right;

	m_message.Create(str, WS_CHILD|WS_VISIBLE, r, this);
	m_message.SetFont(&m_font, FALSE);

	//

	r.SetRect(cr.left, r.bottom + 10, cr.right, cr.bottom);

	str = _T("Do not show this dialog again (hold Shift to re-enable it)");

	pDC->DrawText(str, r, DT_WORDBREAK|DT_CALCRECT);
	r.right = cr.right;

	m_checkbox.Create(str, WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_AUTOCHECKBOX, r, this, IDC_DONOTSHOWAGAINCHECK);
	m_checkbox.SetFont(&m_font, FALSE);

	CheckDlgButton(IDC_DONOTSHOWAGAINCHECK, fHideChecked?BST_CHECKED:BST_UNCHECKED);

	//

	if(!fShowWarningText)
	{
		m_message.ShowWindow(SW_HIDE);
		m_checkbox.ShowWindow(SW_HIDE);
		r = cr;
	}
	else
	{
		r.SetRect(cr.left, r.bottom + 10, cr.right, cr.bottom);
	}

	m_graph.Create(pAF, r, this);

	//

	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

	SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	SetForegroundWindow();
	ShowWindow(SW_SHOWNORMAL);

	return !!RunModalLoop();
}