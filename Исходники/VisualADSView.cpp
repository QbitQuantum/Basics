void CVisualADSView::OnSize(UINT nType, int cx, int cy) 
{
	CFODrawView::OnSize(nType, cx, cy);

	CMainFrame *pMainFrm = (CMainFrame *) AfxGetMainWnd();
	if (pMainFrm->m_hWndJava)
	{
		CView *pView = (CView *) this;
		RECT rect, rect2;
		pView->GetClientRect(&rect);
		pView->ClientToScreen (&rect);
		pMainFrm->GetWindowRect(&rect2);
		rect.left = rect.left - rect2.left - 8;
		rect.bottom = rect.bottom - rect2.top + 0;
		rect.right = rect.right - rect2.left - 8;
		rect.top = rect.top - rect2.top + 0;
		int nWidht = GetSystemMetrics(SM_CXVSCROLL);
		int nHeight = GetSystemMetrics(SM_CYVSCROLL);
		::MoveWindow(pMainFrm->m_hWndJava, rect.left, rect.top, rect.right - rect.left + nWidht, rect.bottom - rect.top + nHeight, TRUE);
		//::SetWindowPos(pMainFrm->m_hWndJava, m_hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW | SWP_NOACTIVATE);
	}
}