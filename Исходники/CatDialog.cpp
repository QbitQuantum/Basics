void CCatDialog::OnDDBnClicked()
{
	CWnd* box = GetDlgItem(IDC_REGEXP);
	box->SetFocus();
	box->SetWindowText(_T(""));
	box->SendMessage(WM_KEYDOWN, VK_DOWN, 0x00510001);
}