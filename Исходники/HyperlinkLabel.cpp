BOOL CHyperlinkLabel::OnEraseBkgnd(CDC* pDC)
{
	// Declare variables
	CRect rcWnd;

	// Get some values
	GetWindowRect(&rcWnd);
	CWnd* pParent = GetParent();

	// Be sure we get rid of the messy hyperlink
	pParent->ScreenToClient(&rcWnd);
	pParent->RedrawWindow(&rcWnd, 0, RDW_NOCHILDREN | RDW_INVALIDATE | RDW_ERASE | RDW_ERASENOW | RDW_UPDATENOW);

	return TRUE;
}