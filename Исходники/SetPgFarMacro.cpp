LRESULT CSetPgFarMacro::OnInitDialog(HWND hDlg, bool abInitial)
{
	_ASSERTE(gpSet->isRClickSendKey==0 || gpSet->isRClickSendKey==1 || gpSet->isRClickSendKey==2);

	checkDlgButton(hDlg, cbRClick, gpSet->isRClickSendKey);
	checkDlgButton(hDlg, cbSafeFarClose, gpSet->isSafeFarClose);

	struct MacroItem {
		int nDlgItem;
		LPCWSTR pszEditor;
		LPCWSTR pszVariants[6];
	} Macros[] = {
		{tRClickMacro, gpSet->RClickMacro(fmv_Default),
			{FarRClickMacroDefault2, FarRClickMacroDefault3, NULL}},
		{tSafeFarCloseMacro, gpSet->SafeFarCloseMacro(fmv_Default),
		{FarSafeCloseMacroDefault2, FarSafeCloseMacroDefault3, FarSafeCloseMacroDefaultD2, FarSafeCloseMacroDefaultD3, L"#Close(0)", NULL}},
		{tCloseTabMacro, gpSet->TabCloseMacro(fmv_Default),
			{FarTabCloseMacroDefault2, FarTabCloseMacroDefault3, NULL}},
		{tSaveAllMacro, gpSet->SaveAllMacro(fmv_Default),
			{FarSaveAllMacroDefault2, FarSaveAllMacroDefault3, NULL}},
		{0}
	};

	for (MacroItem* p = Macros; p->nDlgItem; p++)
	{
		HWND hCombo = GetDlgItem(hDlg, p->nDlgItem);

		CSetDlgLists::FillCBList(hCombo, abInitial, p->pszVariants, p->pszEditor);
	}

	return 0;
}