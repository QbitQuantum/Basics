LRESULT CSetPgDebug::OnInitDialog(HWND hDlg, bool abInitial)
{
	if (abInitial)
	{
		checkDlgButton(hDlg, rbActivityDisabled, BST_CHECKED);

		HWND hList = GetDlgItem(hDlg, lbActivityLog);
		ListView_SetExtendedListViewStyleEx(hList,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);
		ListView_SetExtendedListViewStyleEx(hList,LVS_EX_LABELTIP|LVS_EX_INFOTIP,LVS_EX_LABELTIP|LVS_EX_INFOTIP);

		LVCOLUMN col = {
			LVCF_WIDTH|LVCF_TEXT|LVCF_FMT, LVCFMT_LEFT,
			gpSetCls->EvalSize(60, esf_Horizontal|esf_CanUseDpi)};
		wchar_t szTitle[4]; col.pszText = szTitle;
		wcscpy_c(szTitle, L" ");		ListView_InsertColumn(hList, 0, &col);

		HWND hTip = ListView_GetToolTips(hList);
		SetWindowPos(hTip, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
	}

	return 0;
}