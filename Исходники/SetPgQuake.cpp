LRESULT CSetPgQuake::OnInitDialog(HWND hDlg, bool abInitial)
{
	// Quake style
	checkDlgButton(hDlg, cbQuakeStyle, gpSet->isQuakeStyle ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbQuakeAutoHide, (gpSet->isQuakeStyle == 2) ? BST_CHECKED : BST_UNCHECKED);
	// Show/Hide/Slide timeout
	SetDlgItemInt(hDlg, tQuakeAnimation, gpSet->nQuakeAnimation, FALSE);

	EnableWindow(GetDlgItem(hDlg, cbQuakeAutoHide), gpSet->isQuakeStyle);

	// Frame hide options
	SetDlgItemInt(hDlg, tHideCaptionAlwaysFrame, gpSet->HideCaptionAlwaysFrame(), TRUE);
	SetDlgItemInt(hDlg, tHideCaptionAlwaysDelay, gpSet->nHideCaptionAlwaysDelay, FALSE);
	SetDlgItemInt(hDlg, tHideCaptionAlwaysDissapear, gpSet->nHideCaptionAlwaysDisappear, FALSE);

	checkDlgButton(hDlg, cbAlwaysOnTop, gpSet->isAlwaysOnTop);

	return 0;
}