LRESULT CSetPgTransparent::OnInitDialog(HWND hDlg, bool abInitial)
{
	// +Color key
	ColorSetEdit(hDlg, c38);

	checkDlgButton(hDlg, cbTransparent, (gpSet->nTransparent!=MAX_ALPHA_VALUE) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(hDlg, slTransparent, TBM_SETRANGE, (WPARAM) true, (LPARAM) MAKELONG(MIN_ALPHA_VALUE, MAX_ALPHA_VALUE));
	SendDlgItemMessage(hDlg, slTransparent, TBM_SETPOS  , (WPARAM) true, (LPARAM) gpSet->nTransparent);
	checkDlgButton(hDlg, cbTransparentSeparate, gpSet->isTransparentSeparate ? BST_CHECKED : BST_UNCHECKED);
	//EnableWindow(GetDlgItem(hDlg, cbTransparentInactive), gpSet->isTransparentSeparate);
	//checkDlgButton(hDlg, cbTransparentInactive, (gpSet->nTransparentInactive!=MAX_ALPHA_VALUE) ? BST_CHECKED : BST_UNCHECKED);
	EnableWindow(GetDlgItem(hDlg, slTransparentInactive), gpSet->isTransparentSeparate);
	EnableWindow(GetDlgItem(hDlg, stTransparentInactive), gpSet->isTransparentSeparate);
	EnableWindow(GetDlgItem(hDlg, stOpaqueInactive), gpSet->isTransparentSeparate);
	SendDlgItemMessage(hDlg, slTransparentInactive, TBM_SETRANGE, (WPARAM) true, (LPARAM) MAKELONG(MIN_INACTIVE_ALPHA_VALUE, MAX_ALPHA_VALUE));
	SendDlgItemMessage(hDlg, slTransparentInactive, TBM_SETPOS  , (WPARAM) true, (LPARAM) gpSet->isTransparentSeparate ? gpSet->nTransparentInactive : gpSet->nTransparent);
	checkDlgButton(hDlg, cbUserScreenTransparent, gpSet->isUserScreenTransparent ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbColorKeyTransparent, gpSet->isColorKeyTransparent);

	return 0;
}