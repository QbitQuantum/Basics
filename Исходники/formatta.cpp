void CFormatTabDlg::UpdateButton(CButton& button, BOOL b)
{
	if (b != button.IsWindowEnabled())
		button.EnableWindow(b);
}