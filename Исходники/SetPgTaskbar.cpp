LRESULT CSetPgTaskbar::OnInitDialog(HWND hDlg, bool abInitial)
{
	checkDlgButton(hDlg, cbMinToTray, gpSet->mb_MinToTray);
	EnableWindow(GetDlgItem(hDlg, cbMinToTray), !gpConEmu->ForceMinimizeToTray);

	checkDlgButton(hDlg, cbAlwaysShowTrayIcon, gpSet->isAlwaysShowTrayIcon());

	Settings::TabsOnTaskbar tabsOnTaskbar = gpSet->GetRawTabsOnTaskBar();
	checkRadioButton(hDlg, rbTaskbarBtnActive, rbTaskbarBtnHidden,
		(tabsOnTaskbar == Settings::tot_DontShow) ? rbTaskbarBtnHidden :
		(tabsOnTaskbar == Settings::tot_AllTabsWin7) ? rbTaskbarBtnWin7 :
		(tabsOnTaskbar == Settings::tot_AllTabsAllOS) ? rbTaskbarBtnAll
		: rbTaskbarBtnActive);
	checkDlgButton(hDlg, cbTaskbarOverlay, gpSet->isTaskbarOverlay);
	checkDlgButton(hDlg, cbTaskbarProgress, gpSet->isTaskbarProgress);

	//
	checkDlgButton(hDlg, cbCloseConEmuWithLastTab, gpSet->isCloseOnLastTabClose() ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbCloseConEmuOnCrossClicking, gpSet->isCloseOnCrossClick() ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbMinimizeOnLastTabClose, gpSet->isMinOnLastTabClose() ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbHideOnLastTabClose, gpSet->isHideOnLastTabClose() ? BST_CHECKED : BST_UNCHECKED);
	//
	enableDlgItem(hDlg, cbCloseConEmuOnCrossClicking, !gpSet->isCloseOnLastTabClose());
	enableDlgItem(hDlg, cbMinimizeOnLastTabClose, !gpSet->isCloseOnLastTabClose());
	enableDlgItem(hDlg, cbHideOnLastTabClose, !gpSet->isCloseOnLastTabClose() && gpSet->isMinOnLastTabClose());


	checkDlgButton(hDlg, cbMinimizeOnLoseFocus, gpSet->mb_MinimizeOnLoseFocus);
	EnableWindow(GetDlgItem(hDlg, cbMinimizeOnLoseFocus), (gpSet->isQuakeStyle == 0));


	checkRadioButton(hDlg, rbMinByEscAlways, rbMinByEscNever,
		(gpSet->isMultiMinByEsc == Settings::mbe_NoConsoles) ? rbMinByEscEmpty : gpSet->isMultiMinByEsc ? rbMinByEscAlways : rbMinByEscNever);
	checkDlgButton(hDlg, cbMapShiftEscToEsc, gpSet->isMapShiftEscToEsc);
	EnableWindow(GetDlgItem(hDlg, cbMapShiftEscToEsc), (gpSet->isMultiMinByEsc == Settings::mbe_Always));

	checkDlgButton(hDlg, cbCmdTaskbarTasks, gpSet->isStoreTaskbarkTasks);
	checkDlgButton(hDlg, cbCmdTaskbarCommands, gpSet->isStoreTaskbarCommands);
	EnableWindow(GetDlgItem(hDlg, cbCmdTaskbarUpdate), (gnOsVer >= 0x601));

	return 0;
}