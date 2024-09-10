LRESULT AmbiguousRecipientsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CAxDialogImpl<AmbiguousRecipientsDlg>::OnInitDialog(uMsg, wParam, lParam, bHandled);

	CWSUIExtras::SetWSDialogWindowText(m_hWnd, Workshare::Products::WS_PROD_DEFAULT);

	AddRecipientListColumns();
	PopulateRecipientListView();

	// NJW 08/01/2008 - Initially disable the OK button (until user selects a recipient)
	ATLControls::CButton	btnOK = GetDlgItem(IDOK);
	btnOK.EnableWindow(FALSE);

	bHandled = TRUE;
	return 1;  // Let the system set the focus
}