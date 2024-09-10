LRESULT CSetPgFonts::OnInitDialog(HWND hDlg, bool abInitial)
{
	SetDlgItemText(hDlg, tFontFace, gpFontMgr->FontFaceName());
	SetDlgItemText(hDlg, tFontFace2, gpFontMgr->BorderFontFaceName());

	if (abInitial)
	{
		// Добавить шрифты рисованные ConEmu
		for (INT_PTR j = 0; j < gpFontMgr->m_RegFonts.size(); ++j)
		{
			const RegFont* iter = &(gpFontMgr->m_RegFonts[j]);

			if (iter->pCustom)
			{
				BOOL bMono = iter->pCustom->GetFont(0,0,0,0)->IsMonospace();

				int nIdx = SendDlgItemMessage(hDlg, tFontFace, CB_ADDSTRING, 0, (LPARAM)iter->szFontName);
				SendDlgItemMessage(hDlg, tFontFace, CB_SETITEMDATA, nIdx, bMono ? 1 : 0);

				nIdx = SendDlgItemMessage(hDlg, tFontFace2, CB_ADDSTRING, 0, (LPARAM)iter->szFontName);
				SendDlgItemMessage(hDlg, tFontFace2, CB_SETITEMDATA, nIdx, bMono ? 1 : 0);
			}
		}

		CSetDlgFonts::StartEnumFontsThread();

		CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, tFontSizeY), CSetDlgLists::eFSizesY, gpSet->FontSizeY, true);

		CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, tFontSizeX), CSetDlgLists::eFSizesX, gpSet->FontSizeX, true);
		CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, tFontSizeX2), CSetDlgLists::eFSizesX, gpSet->FontSizeX2, true);
		CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, tFontSizeX3), CSetDlgLists::eFSizesX, gpSet->FontSizeX3, true);

		CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, lbExtendFontBoldIdx), CSetDlgLists::eColorIdx, gpSet->AppStd.nFontBoldColor, false);
		CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, lbExtendFontItalicIdx), CSetDlgLists::eColorIdx, gpSet->AppStd.nFontItalicColor, false);
		CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, lbExtendFontNormalIdx), CSetDlgLists::eColorIdx, gpSet->AppStd.nFontNormalColor, false);

		CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, tFontCharset), CSetDlgLists::eCharSets, gpFontMgr->LogFont.lfCharSet, false);
	}
	else
	{
		//TODO: Обновить значения в списках?
	}

	checkDlgButton(hDlg, cbExtendFonts, gpSet->AppStd.isExtendFonts);
	CSetDlgLists::EnableDlgItems(hDlg, CSetDlgLists::eExtendFonts, gpSet->AppStd.isExtendFonts);

	checkDlgButton(hDlg, cbFontAuto, gpSet->isFontAutoSize);

	MCHKHEAP

	checkRadioButton(hDlg, rNoneAA, rCTAA,
		(gpFontMgr->LogFont.lfQuality == CLEARTYPE_NATURAL_QUALITY) ? rCTAA :
		(gpFontMgr->LogFont.lfQuality == ANTIALIASED_QUALITY) ? rStandardAA : rNoneAA);

	// 3d state - force center symbols in cells
	checkDlgButton(hDlg, cbMonospace, BST(gpSet->isMonospace));

	checkDlgButton(hDlg, cbBold, (gpFontMgr->LogFont.lfWeight == FW_BOLD) ? BST_CHECKED : BST_UNCHECKED);

	checkDlgButton(hDlg, cbItalic, gpFontMgr->LogFont.lfItalic ? BST_CHECKED : BST_UNCHECKED);

	/* Alternative font, initially created for prettifying Far Manager borders */
	{
		checkDlgButton(hDlg, cbFixFarBorders, BST(gpSet->isFixFarBorders));

		checkDlgButton(hDlg, cbFont2AA, gpSet->isAntiAlias2 ? BST_CHECKED : BST_UNCHECKED);

		LPCWSTR cszFontRanges[] = {
			L"Far Manager borders: 2500-25C4;",
			L"Dashes and Borders: 2013-2015;2500-25C4;",
			L"Pseudographics: 2013-25C4;",
			L"CJK: 2E80-9FC3;AC00-D7A3;F900-FAFF;FE30-FE4F;FF01-FF60;FFE0-FFE6;",
			NULL
		};
		CEStr szCharRanges(gpSet->CreateCharRanges(gpSet->mpc_CharAltFontRanges));
		LPCWSTR pszCurrentRange = szCharRanges.ms_Val;
		bool bExist = false;

		HWND hCombo = GetDlgItem(hDlg, tUnicodeRanges);
		SendDlgItemMessage(hDlg, tUnicodeRanges, CB_RESETCONTENT, 0,0);

		// Fill our drop down with font ranges
		for (INT_PTR i = 0; cszFontRanges[i]; i++)
		{
			LPCWSTR pszRange = wcsstr(cszFontRanges[i], L": ");
			if (!pszRange) { _ASSERTE(pszRange); continue; }

			SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)cszFontRanges[i]);

			if (!bExist && (lstrcmpi(pszRange+2, pszCurrentRange) == 0))
			{
				pszCurrentRange = cszFontRanges[i];
				bExist = true;
			}
		}
		if (pszCurrentRange && *pszCurrentRange && !bExist)
			SendMessageW(hCombo, CB_ADDSTRING, 0, (LPARAM)pszCurrentRange);
		// And show current value
		SetWindowText(hCombo, pszCurrentRange ? pszCurrentRange : L"");
	}
	/* Alternative font ends */

	checkDlgButton(hDlg, cbFontMonitorDpi, gpSet->FontUseDpi ? BST_CHECKED : BST_UNCHECKED);
	checkDlgButton(hDlg, cbFontAsDeviceUnits, gpSet->FontUseUnits ? BST_CHECKED : BST_UNCHECKED);

	gpSetCls->mn_LastChangingFontCtrlId = 0;
	return 0;
}