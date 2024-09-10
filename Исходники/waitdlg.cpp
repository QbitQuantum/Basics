void CWaitDlg::AllowCancel( bool enable ) {
	// this shows or hides the Cancel button
	CWnd* pCancelButton = GetDlgItem (IDCANCEL);
	ASSERT (pCancelButton);
	if ( enable ) {
		pCancelButton->ShowWindow (SW_NORMAL);
	} else {
		pCancelButton->ShowWindow (SW_HIDE);
	}
}