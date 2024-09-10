void CxStatic::SetWindowText( LPCTSTR strText)
{
	m_strText = strText;

	CRect Rect;
	GetClientRect(&Rect);

	if ( m_bTransparentBk ){
		ClientToScreen(&Rect);
		Rect.InflateRect(1,1,1,1);
		CWnd *Parent = GetParent();
		Parent->ScreenToClient(&Rect);
		Parent->InvalidateRect(&Rect);
		Parent->UpdateWindow();
		//SendMessage(WM_ERASEBKGND);
	}
	else
		RedrawWindow();
}