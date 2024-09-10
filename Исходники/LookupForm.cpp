BOOL CLookupForm::DoCreateDialog(CWnd* parent)
{
	BOOL ret = Create(IDD, parent);
	if (!ret) return FALSE;

    // prepare titlebar
	m_title.ModifyStyle(0, WS_CLIPCHILDREN);
	m_title.ModifyStyleEx(0, WS_EX_CONTROLPARENT);

    CRect	rc;
	rc.SetRect(0, 0, 60, 23);
    m_btnSearch.Create(_T("&Search"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, rc, &m_title, IDC_BUTTON_SEARCH);
    m_btnSearch.SetFont(GetFont());
    rc.SetRect(0, 0, 250, 23);
    m_editSearch.Create(ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, rc, &m_title, IDC_EDIT_SEARCH);
    m_editSearch.SetFont(GetFont());
    m_editSearch.SetFocus();

	OnInitialize();

	return TRUE;
};