void CCommentsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CWnd *pEdit = GetDlgItem(IDC_COMMENTS);
	CWnd *pOk = GetDlgItem(IDC_OK);
	CWnd *pCancel = GetDlgItem(IDC_CANCEL);
	CWnd *pCheckBox = GetDlgItem(IDC_SHOWONOPEN);

	CRect dlgRect;
	GetClientRect(dlgRect);

	if (pEdit != NULL) {
		dlgRect.bottom -= 39;
		pEdit->MoveWindow(dlgRect);
		CRect buttonRect;
		pOk->GetClientRect(buttonRect);
		buttonRect.MoveToY(dlgRect.bottom + 8);
		buttonRect.MoveToX(dlgRect.right - buttonRect.Width() * 2 - 10);
		pOk->MoveWindow(buttonRect);
		pCancel->GetClientRect(buttonRect);
		buttonRect.MoveToY(dlgRect.bottom + 8);
		buttonRect.MoveToX(dlgRect.right - buttonRect.Width() - 7);
		pCancel->MoveWindow(buttonRect);
		pCheckBox->GetClientRect(buttonRect);
		buttonRect.MoveToY(dlgRect.bottom + 14);
		buttonRect.MoveToX(8);
		pCheckBox->MoveWindow(buttonRect);
	}
}