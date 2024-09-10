LRESULT CSetPgEnvironment::OnInitDialog(HWND hDlg, bool abInitial)
{
	checkDlgButton(hDlg, cbAddConEmu2Path, (gpSet->ComSpec.AddConEmu2Path & CEAP_AddConEmuExeDir) ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbAddConEmuBase2Path, (gpSet->ComSpec.AddConEmu2Path & CEAP_AddConEmuBaseDir) ? BST_CHECKED : BST_UNCHECKED);

	SetDlgItemText(hDlg, tSetCommands, gpSet->psEnvironmentSet ? gpSet->psEnvironmentSet : L"");

	return 0;
}