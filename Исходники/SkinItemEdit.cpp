BOOL CSkinItemEdit::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lpResult)
{
	*lpResult = CSkinItem::DefWndProc(uMsg, wParam, lParam);

	CWnd* pWnd = CWnd::FromHandle(m_hWnd);
	CDC* pDC = NULL;
	if (m_bSystemEdit)
		pDC = pWnd->GetDC();
	else 
		pDC = pWnd->GetWindowDC();

	DrawFrame(pDC);

	pWnd->ReleaseDC(pDC);

	return TRUE;
}