void CSetPgApps::DoFillControls(const AppSettings* pApp)
{
	if (!pApp)
	{
		_ASSERTE(pApp);
		return;
	}

	checkRadioButton(mh_Dlg, rbAppDistinctElevatedOn, rbAppDistinctElevatedIgnore,
		(pApp->Elevated == 1) ? rbAppDistinctElevatedOn :
		(pApp->Elevated == 2) ? rbAppDistinctElevatedOff : rbAppDistinctElevatedIgnore);

	BYTE b;

	checkDlgButton(mh_Child, cbExtendFontsOverride, pApp->OverrideExtendFonts);
	checkDlgButton(mh_Child, cbExtendFonts, pApp->isExtendFonts);

	b = pApp->nFontBoldColor;
	CSetDlgLists::FillListBoxItems(GetDlgItem(mh_Child, lbExtendFontBoldIdx), CSetDlgLists::eColorIdx, b, false);
	b = pApp->nFontItalicColor;
	CSetDlgLists::FillListBoxItems(GetDlgItem(mh_Child, lbExtendFontItalicIdx), CSetDlgLists::eColorIdx, b, false);
	b = pApp->nFontNormalColor;
	CSetDlgLists::FillListBoxItems(GetDlgItem(mh_Child, lbExtendFontNormalIdx), CSetDlgLists::eColorIdx, b, false);

	checkDlgButton(mh_Child, cbCursorOverride, pApp->OverrideCursor);
	CSetPgCursor::InitCursorCtrls(mh_Child, pApp);

	checkDlgButton(mh_Child, cbColorsOverride, pApp->OverridePalette);
	// Don't add unknown palettes in the list!
	int nIdx = SendDlgItemMessage(mh_Child, lbColorsOverride, CB_FINDSTRINGEXACT, -1, (LPARAM)pApp->szPaletteName);
	SendDlgItemMessage(mh_Child, lbColorsOverride, CB_SETCURSEL, klMax(nIdx, 0), 0);

	checkDlgButton(mh_Child, cbClipboardOverride, pApp->OverrideClipboard);
	//
	checkDlgButton(mh_Child, cbCTSDetectLineEnd, pApp->isCTSDetectLineEnd);
	checkDlgButton(mh_Child, cbCTSBashMargin, pApp->isCTSBashMargin);
	checkDlgButton(mh_Child, cbCTSTrimTrailing, pApp->isCTSTrimTrailing);
	b = pApp->isCTSEOL;
	CSetDlgLists::FillListBoxItems(GetDlgItem(mh_Child, lbCTSEOL), CSetDlgLists::eCRLF, b, false);

	//
	PasteLinesMode mode;
	mode = pApp->isPasteAllLines;
	checkRadioButton(mh_Child, rPasteM1MultiLine, rPasteM1Nothing,
		(mode == plm_FirstLine) ? rPasteM1FirstLine
		: (mode == plm_SingleLine) ? rPasteM1SingleLine
		: (mode == plm_Nothing) ? rPasteM1Nothing
		: rPasteM1MultiLine);
	checkDlgButton(mh_Child, cbPasteM1Posix, (pApp->isPosixAllLines != pxm_Intact) ? BST_CHECKED : BST_UNCHECKED);
	mode = pApp->isPasteFirstLine;
	checkRadioButton(mh_Child, rPasteM2MultiLine, rPasteM2Nothing,
		(mode == plm_MultiLine) ? rPasteM2MultiLine
		: (mode == plm_FirstLine) ? rPasteM2FirstLine
		: (mode == plm_Nothing) ? rPasteM2Nothing
		: rPasteM2SingleLine);
	checkDlgButton(mh_Child, cbPasteM2Posix, (pApp->isPosixFirstLine != pxm_Intact) ? BST_CHECKED : BST_UNCHECKED);
	//
	checkDlgButton(mh_Child, cbCTSClickPromptPosition, pApp->isCTSClickPromptPosition);
	//
	checkDlgButton(mh_Child, cbCTSDeleteLeftWord, pApp->isCTSDeleteLeftWord);

}