LRESULT CSetPgFeatures::OnInitDialog(HWND hDlg, bool abInitial)
{
	checkDlgButton(hDlg, cbAutoRegFonts, gpSet->isAutoRegisterFonts);

	checkDlgButton(hDlg, cbDebugSteps, gpSet->isDebugSteps);

	checkDlgButton(hDlg, cbDebugLog, gpSet->isLogging());
	UpdateLogLocation();

	checkDlgButton(hDlg, cbMonitorConsoleLang, gpSet->isMonitorConsoleLang ? BST_CHECKED : BST_UNCHECKED);

	checkDlgButton(hDlg, cbSleepInBackground, gpSet->isSleepInBackground);

	checkDlgButton(hDlg, cbRetardInactivePanes, gpSet->isRetardInactivePanes);

	checkDlgButton(hDlg, cbVisible, gpSet->isConVisible);

	checkDlgButton(hDlg, cbUseInjects, gpSet->isUseInjects);

	checkDlgButton(hDlg, cbProcessAnsi, gpSet->isProcessAnsi);

	checkDlgButton(hDlg, cbAnsiLog, gpSet->isAnsiLog);
	SetDlgItemText(hDlg, tAnsiLogPath, gpSet->pszAnsiLog ? gpSet->pszAnsiLog : L"");

	checkDlgButton(hDlg, cbProcessNewConArg, gpSet->isProcessNewConArg);
	checkDlgButton(hDlg, cbProcessCmdStart, gpSet->isProcessCmdStart);
	checkDlgButton(hDlg, cbProcessCtrlZ, gpSet->isProcessCtrlZ);

	checkDlgButton(hDlg, cbSuppressBells, gpSet->isSuppressBells);

	checkDlgButton(hDlg, cbConsoleExceptionHandler, gpSet->isConsoleExceptionHandler);

	checkDlgButton(hDlg, cbUseClink, gpSet->isUseClink() ? BST_CHECKED : BST_UNCHECKED);

	checkDlgButton(hDlg, cbDosBox, gpConEmu->mb_DosBoxExists);
	// изменение пока запрещено
	// или чтобы ругнуться, если DosBox не установлен
	EnableWindow(GetDlgItem(hDlg, cbDosBox), !gpConEmu->mb_DosBoxExists);
	//EnableWindow(GetDlgItem(hDlg, bDosBoxSettings), FALSE); // изменение пока запрещено
	ShowWindow(GetDlgItem(hDlg, bDosBoxSettings), SW_HIDE);

	checkDlgButton(hDlg, cbDisableAllFlashing, gpSet->isDisableAllFlashing);

	checkDlgButton(hDlg, cbFocusInChildWindows, gpSet->isFocusInChildWindows);

	return 0;
}