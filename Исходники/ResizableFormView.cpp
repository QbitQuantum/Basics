void CResizableFormView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	CWnd* pParent = GetParent();

	// hide zise grip when parent is maximized
	if (pParent->IsZoomed())
		HideSizeGrip(&m_dwGripTempState, GHR_MAXIMIZED);
	else
		ShowSizeGrip(&m_dwGripTempState, GHR_MAXIMIZED);

	// hide size grip when there are scrollbars
	CSize size = GetTotalSize();
	if (cx < size.cx || cy < size.cy)
		HideSizeGrip(&m_dwGripTempState, GHR_SCROLLBAR);
	else
		ShowSizeGrip(&m_dwGripTempState, GHR_SCROLLBAR);

	// hide size grip when the parent window is not resizable
	// or the form is not bottom-right aligned (e.g. there's a statusbar)
	DWORD dwStyle = pParent->GetStyle();
	CRect rectParent, rectChild;
	GetWindowRect(rectChild);
	::MapWindowPoints(NULL, pParent->GetSafeHwnd(), (LPPOINT)&rectChild, 2);
	pParent->GetClientRect(rectParent);
	if (!(dwStyle & WS_THICKFRAME)
		|| (rectChild.BottomRight() != rectParent.BottomRight()))
		HideSizeGrip(&m_dwGripTempState, GHR_ALIGNMENT);
	else
		ShowSizeGrip(&m_dwGripTempState, GHR_ALIGNMENT);

	// update grip and layout
	UpdateSizeGrip();
	ArrangeLayout();
}