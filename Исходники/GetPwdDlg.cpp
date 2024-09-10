void CGetPwdDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if (!m_InitDialogDone)
		return;

	// Compute the change in width (dx)
	CRect rect;
	GetWindowRect(&rect);
	int dx = rect.Width() - m_LastRect.Width();
	// Save the new size
	m_LastRect = rect;

	// Widen the text fields by the change in width (dx) and
	GetDlgItem( IDC_STATICMSG )->GetWindowRect(&rect);
	GetDlgItem( IDC_STATICMSG )->SetWindowPos(NULL, 0, 0, rect.right - rect.left + dx, 
								    rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
	GetDlgItem( IDC_STATICMSG )->InvalidateRect(NULL);

	GetDlgItem( IDC_PASSWORD )->GetWindowRect(&rect);
	GetDlgItem( IDC_PASSWORD )->SetWindowPos(NULL, 0, 0, rect.right - rect.left + dx, 
								    rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
	GetDlgItem( IDC_PASSWORD )->InvalidateRect(NULL);

	// Slide the buttons to the right by the change in width
	CWnd *pWnd = GetDlgItem(IDOK);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(rect);
	pWnd->SetWindowPos(NULL, rect.left + dx, rect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	pWnd->InvalidateRect(NULL, TRUE);

	pWnd = GetDlgItem(IDCANCEL);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(rect);
	pWnd->SetWindowPos(NULL, rect.left + dx, rect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	pWnd->InvalidateRect(NULL, TRUE);
}