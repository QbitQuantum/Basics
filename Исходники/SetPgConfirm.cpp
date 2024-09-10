LRESULT CSetPgConfirm::OnInitDialog(HWND hDlg, bool abInitial)
{
	checkDlgButton(hDlg, cbNewConfirm, gpSet->isMultiNewConfirm);
	checkDlgButton(hDlg, cbDupConfirm, gpSet->isMultiDupConfirm);
	checkDlgButton(hDlg, cbCloseWindowConfirm, (gpSet->nCloseConfirmFlags & Settings::cc_Window) ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbCloseConsoleConfirm, (gpSet->nCloseConfirmFlags & Settings::cc_Console) ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbConfirmCloseRunning, (gpSet->nCloseConfirmFlags & Settings::cc_Running) ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbCloseEditViewConfirm, (gpSet->nCloseConfirmFlags & Settings::cc_FarEV) ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbConfirmDetach, gpSet->isMultiDetachConfirm);
	checkDlgButton(hDlg, cbShowWasHiddenMsg, gpSet->isDownShowHiddenMessage ? BST_UNCHECKED : BST_CHECKED);
	checkDlgButton(hDlg, cbShowWasSetOnTopMsg, gpSet->isDownShowExOnTopMessage ? BST_UNCHECKED : BST_CHECKED);

	return 0;
}