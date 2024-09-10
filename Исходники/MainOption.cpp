void CMainPropertyPage::OnCheckExternalNewTab(WORD /*wNotifyCode*/, WORD /*wID*/, HWND hWndCtl)
{
	bool bCheck = CButton(GetDlgItem(IDC_CHECK_EXTERNALNEWTAB)).GetCheck() != 0;
	CButton btn = GetDlgItem(IDC_CHECK_EXTERNALNEWTABACTIVE);
	btn.EnableWindow(bCheck);
	if (bCheck == false)
		btn.SetCheck(FALSE);
}