BOOL ReloadFarInfoW995(/*BOOL abFull*/)
{
	if (!InfoW995 || !FSFW995) return FALSE;

	if (!gpFarInfo)
	{
		_ASSERTE(gpFarInfo!=NULL);
		return FALSE;
	}

	// Заполнить gpFarInfo->
	//BYTE nFarColors[col_LastIndex]; // Массив цветов фара
	//DWORD nFarInterfaceSettings;
	//DWORD nFarPanelSettings;
	//DWORD nFarConfirmationSettings;
	//BOOL  bFarPanelAllowed, bFarLeftPanel, bFarRightPanel;   // FCTL_CHECKPANELSEXIST, FCTL_GETPANELSHORTINFO,...
	//CEFAR_SHORT_PANEL_INFO FarLeftPanel, FarRightPanel;
	DWORD ldwConsoleMode = 0;	GetConsoleMode(/*ghConIn*/GetStdHandle(STD_INPUT_HANDLE), &ldwConsoleMode);
#ifdef _DEBUG
	static DWORD ldwDbgMode = 0;

	if (IsDebuggerPresent())
	{
		if (ldwDbgMode != ldwConsoleMode)
		{
			wchar_t szDbg[128]; _wsprintf(szDbg, SKIPLEN(countof(szDbg)) L"Far.ConEmuW: ConsoleMode(STD_INPUT_HANDLE)=0x%08X\n", ldwConsoleMode);
			OutputDebugStringW(szDbg);
			ldwDbgMode = ldwConsoleMode;
		}
	}

#endif
	gpFarInfo->nFarConsoleMode = ldwConsoleMode;
	
	LoadFarColorsW995(gpFarInfo->nFarColors);

	//_ASSERTE(FPS_SHOWCOLUMNTITLES==0x20 && FPS_SHOWSTATUSLINE==0x40); //-V112
	LoadFarSettingsW995(&gpFarInfo->FarInterfaceSettings, &gpFarInfo->FarPanelSettings);

	//gpFarInfo->nFarConfirmationSettings =
	//    (DWORD)InfoW995->AdvControl(InfoW995->ModuleNumber, ACTL_GETCONFIRMATIONS, 0);

	gpFarInfo->bMacroActive = IsMacroActiveW995();
	ActlKeyMacro area = {MCMD_GETAREA};
	INT_PTR nArea = InfoW995->AdvControl(InfoW995->ModuleNumber, ACTL_KEYMACRO, &area);
	switch(nArea)
	{
		case MACROAREA_SHELL:
		case MACROAREA_INFOPANEL:
		case MACROAREA_QVIEWPANEL:
		case MACROAREA_TREEPANEL:
		case MACROAREA_SEARCH:
			gpFarInfo->nMacroArea = fma_Panels;
			break;
		case MACROAREA_VIEWER:
			gpFarInfo->nMacroArea = fma_Viewer;
			break;
		case MACROAREA_EDITOR:
			gpFarInfo->nMacroArea = fma_Editor;
			break;
		case MACROAREA_DIALOG:
		case MACROAREA_DISKS:
		case MACROAREA_FINDFOLDER:
		case MACROAREA_AUTOCOMPLETION:
		case MACROAREA_MAINMENU:
		case MACROAREA_MENU:
		case MACROAREA_USERMENU:
			gpFarInfo->nMacroArea = fma_Dialog;
			break;
		default:
			gpFarInfo->nMacroArea = fma_Unknown;
	}

	gpFarInfo->bFarPanelAllowed = InfoW995->Control(PANEL_NONE, FCTL_CHECKPANELSEXIST, 0, 0);
	gpFarInfo->bFarPanelInfoFilled = FALSE;
	gpFarInfo->bFarLeftPanel = FALSE;
	gpFarInfo->bFarRightPanel = FALSE;
	// -- пока, во избежание глюков в FAR при неожиданных запросах информации о панелях
	//if (FALSE == (gpFarInfo->bFarPanelAllowed)) {
	//	gpConMapInfo->bFarLeftPanel = FALSE;
	//	gpConMapInfo->bFarRightPanel = FALSE;
	//} else {
	//	PanelInfo piA = {}, piP = {};
	//	BOOL lbActive  = InfoW995->Control(PANEL_ACTIVE, FCTL_GETPANELINFO, 0, (LONG_PTR)&piA);
	//	BOOL lbPassive = InfoW995->Control(PANEL_PASSIVE, FCTL_GETPANELINFO, 0, (LONG_PTR)&piP);
	//	if (!lbActive && !lbPassive)
	//	{
	//		gpConMapInfo->bFarLeftPanel = FALSE;
	//		gpConMapInfo->bFarRightPanel = FALSE;
	//	} else {
	//		PanelInfo *ppiL = NULL;
	//		PanelInfo *ppiR = NULL;
	//		if (lbActive) {
	//			if (piA.Flags & PFLAGS_PANELLEFT) ppiL = &piA; else ppiR = &piA;
	//		}
	//		if (lbPassive) {
	//			if (piP.Flags & PFLAGS_PANELLEFT) ppiL = &piP; else ppiR = &piP;
	//		}
	//		gpConMapInfo->bFarLeftPanel = ppiL!=NULL;
	//		gpConMapInfo->bFarRightPanel = ppiR!=NULL;
	//		if (ppiL) FarPanel2CePanel(ppiL, &(gpConMapInfo->FarLeftPanel));
	//		if (ppiR) FarPanel2CePanel(ppiR, &(gpConMapInfo->FarRightPanel));
	//	}
	//}
	return TRUE;
}