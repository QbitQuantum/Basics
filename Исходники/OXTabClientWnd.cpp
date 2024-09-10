BOOL COXTabWorkspace::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CRect rect;
	GetWindowRect(rect);
	ScreenToClient(rect);
	rect.right += m_dwOffset;
	rect.bottom += m_dwOffset;

	CBrush brush;
	brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
	brush.UnrealizeObject();

	pDC->FillRect(rect, &brush);
	return TRUE;
}