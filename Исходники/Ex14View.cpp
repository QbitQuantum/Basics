void CEx14View::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	// resize components to take up all real estate
	CWnd* pWnd = GetDlgItem(IDC_GRID);
	if(pWnd)
		pWnd->SetWindowPos(NULL, 0, 0, cx, cy/2, SWP_NOZORDER);

	pWnd = GetDlgItem(IDC_NOTIFICATION_OUT);
	if(pWnd)
		pWnd->SetWindowPos(NULL, 0, cy/2+3, cx,cy/2-4, SWP_NOZORDER);
}