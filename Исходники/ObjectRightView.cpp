void CObjectRightView::OnSize(UINT nType, int cx, int cy) 
{
	SetScrollSizes( MM_TEXT, CSize(cx, cy) );

	CFormView::OnSize(nType, cx, cy);

	if	(initialized) {
		CRect rc;

		m_iWidth = cx;
		m_iHeight = cy;

		// Save static reference to the render window
		CWnd* pGroup = GetDlgItem(IDC_RENDERWINDOW);
		pGroup->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
		pGroup->GetClientRect(&rc);
		pGroup->MapWindowPoints(this, &rc);

		m_hwndRenderWindow = GetDlgItem(IDC_RENDERWINDOW)->GetSafeHwnd();
		
		InitializeDevice();
		InitializeDeviceBuffer();

		Render();
	}
}