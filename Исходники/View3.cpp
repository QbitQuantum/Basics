void CView3::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	CFormView::OnWindowPosChanging(lpwndpos);
	
	// Hide horizontal scrollbar:
	ShowScrollBar (SB_HORZ, FALSE);
	ModifyStyle (WS_HSCROLL, 0, SWP_DRAWFRAME);
}