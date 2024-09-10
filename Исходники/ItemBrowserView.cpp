BOOL CItemBrowserView::OnEraseBkgnd(CDC* pDC) 
{
	// This is not a perfect solution, but it prevents much of the flickering as the
	// controls are being moved around. The controls themselves will still flicker 
	// as they redraw themselves. This pervents the controls being covered by the
	// erasing of the background which is really noticable and ugly.
	CRect rExclude;
	CWnd *pWnd = GetWindow(GW_CHILD);
	while(pWnd)
	{
		if (pWnd->IsWindowVisible())
		{
			pWnd->GetWindowRect(&rExclude);
			ScreenToClient(&rExclude);
			pDC->ExcludeClipRect(&rExclude);
		}

		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	} 

	return CFormView::OnEraseBkgnd(pDC);
}