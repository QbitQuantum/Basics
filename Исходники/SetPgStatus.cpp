LRESULT CSetPgStatus::OnInitDialog(HWND hDlg, bool abInitial)
{
	SetDlgItemText(hDlg, tStatusFontFace, gpSet->sStatusFontFace);

	if (CSetDlgFonts::EnumFontsFinished())  // Если шрифты уже считаны
	{
		CSetPgFonts* pFonts = NULL;
		if (gpSetCls->GetPageObj(pFonts))
		{
			pFonts->CopyFontsTo(hDlg, tStatusFontFace, 0); // можно скопировать список с вкладки [thi_Fonts]
		}
	}

	UINT nVal = gpSet->nStatusFontHeight;
	CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, tStatusFontHeight), CSetDlgLists::eFSizesSmall, nVal, true);

	CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, tStatusFontCharset), CSetDlgLists::eCharSets, gpSet->nStatusFontCharSet, false);

	// Colors
	for (uint c = c35; c <= c37; c++)
		CSetDlgColors::ColorSetEdit(hDlg, c);

	checkDlgButton(hDlg, cbStatusVertSep, (gpSet->isStatusBarFlags & csf_VertDelim) ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbStatusHorzSep, (gpSet->isStatusBarFlags & csf_HorzDelim) ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbStatusVertPad, (gpSet->isStatusBarFlags & csf_NoVerticalPad)==0 ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbStatusSystemColors, (gpSet->isStatusBarFlags & csf_SystemColors) ? BST_CHECKED : BST_UNCHECKED);

	CSetDlgLists::EnableDlgItems(hDlg, CSetDlgLists::eStatusColorIds, !(gpSet->isStatusBarFlags & csf_SystemColors));

	checkDlgButton(hDlg, cbShowStatusBar, gpSet->isStatusBarShow);

	//for (size_t i = 0; i < countof(SettingsNS::StatusItems); i++)
	//{
	//	checkDlgButton(hDlg, SettingsNS::StatusItems[i].nDlgID, !gpSet->isStatusColumnHidden[SettingsNS::StatusItems[i].stItem]);
	//}

	UpdateStatusItems(hDlg);

	return 0;
}