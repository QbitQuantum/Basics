LRESULT GetVal::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (message==WM_INITDIALOG)
	{
		CEdit *ed = (CEdit*)GetDlgItem(IDC_EDIT_ADD_TERRITOIRE);
		ed->SetFocus();
		ed->SetLimitText(100);
	}

	return CDialog::WindowProc(message, wParam, lParam);
}