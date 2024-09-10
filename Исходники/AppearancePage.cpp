void AppearancePage::write()
{
	PropPage::write((HWND)*this, items, listItems, GetDlgItem(IDC_APPEARANCE_BOOLEANS));
	PropPage::write((HWND)*this, items, boldItems, GetDlgItem(IDC_BOLD_BOOLEANS));
}