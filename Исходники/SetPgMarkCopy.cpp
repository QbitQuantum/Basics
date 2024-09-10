LRESULT CSetPgMarkCopy::OnInitDialog(HWND hDlg, bool abInitial)
{
	checkDlgButton(hDlg, cbCTSIntelligent, gpSet->isCTSIntelligent);
	wchar_t* pszExcept = gpSet->GetIntelligentExceptions();
	SetDlgItemText(hDlg, tCTSIntelligentExceptions, pszExcept ? pszExcept : L"");
	SafeFree(pszExcept);

	checkDlgButton(hDlg, cbCTSAutoCopy, gpSet->isCTSAutoCopy);
	checkDlgButton(hDlg, cbCTSResetOnRelease, (gpSet->isCTSResetOnRelease && gpSet->isCTSAutoCopy));
	enableDlgItem(hDlg, cbCTSResetOnRelease, gpSet->isCTSAutoCopy);

	checkDlgButton(hDlg, cbCTSIBeam, gpSet->isCTSIBeam);

	checkDlgButton(hDlg, cbCTSEndOnTyping, (gpSet->isCTSEndOnTyping != 0));
	checkDlgButton(hDlg, cbCTSEndOnKeyPress, (gpSet->isCTSEndOnTyping != 0) && gpSet->isCTSEndOnKeyPress);
	checkDlgButton(hDlg, cbCTSEndCopyBefore, (gpSet->isCTSEndOnTyping == 1));
	checkDlgButton(hDlg, cbCTSEraseBeforeReset, gpSet->isCTSEraseBeforeReset);
	enableDlgItem(hDlg, cbCTSEndOnKeyPress, gpSet->isCTSEndOnTyping!=0);
	enableDlgItem(hDlg, cbCTSEndCopyBefore, gpSet->isCTSEndOnTyping!=0);
	enableDlgItem(hDlg, cbCTSEraseBeforeReset, gpSet->isCTSEndOnTyping!=0);

	checkDlgButton(hDlg, cbCTSFreezeBeforeSelect, gpSet->isCTSFreezeBeforeSelect);
	checkDlgButton(hDlg, cbCTSBlockSelection, gpSet->isCTSSelectBlock);
	UINT VkMod = gpSet->GetHotkeyById(vkCTSVkBlock);
	CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, lbCTSBlockSelection), CSetDlgLists::eKeysAct, VkMod, true);
	checkDlgButton(hDlg, cbCTSTextSelection, gpSet->isCTSSelectText);
	VkMod = gpSet->GetHotkeyById(vkCTSVkText);
	CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, lbCTSTextSelection), CSetDlgLists::eKeysAct, VkMod, true);
	VkMod = gpSet->GetHotkeyById(vkCTSVkAct);

	UINT idxBack = CONBACKCOLOR(gpSet->isCTSColorIndex);
	UINT idxFore = CONFORECOLOR(gpSet->isCTSColorIndex);
	CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, lbCTSForeIdx), CSetDlgLists::eColorIdx16, idxFore, false);
	CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, lbCTSBackIdx), CSetDlgLists::eColorIdx16, idxBack, false);

	if (abInitial)
	{
		mf_MarkCopyPreviewProc = (WNDPROC)SetWindowLongPtr(GetDlgItem(hDlg, stCTSPreview), GWLP_WNDPROC, (LONG_PTR)MarkCopyPreviewProc);
	}

	checkDlgButton(hDlg, cbCTSDetectLineEnd, gpSet->AppStd.isCTSDetectLineEnd);
	checkDlgButton(hDlg, cbCTSBashMargin, gpSet->AppStd.isCTSBashMargin);
	checkDlgButton(hDlg, cbCTSTrimTrailing, gpSet->AppStd.isCTSTrimTrailing);
	CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, lbCTSEOL), CSetDlgLists::eCRLF, gpSet->AppStd.isCTSEOL, false);

	checkDlgButton(hDlg, cbCTSShiftArrowStartSel, gpSet->AppStd.isCTSShiftArrowStart);

	CSetDlgLists::FillListBoxItems(GetDlgItem(hDlg, lbCopyFormat), CSetDlgLists::eCopyFormat, gpSet->isCTSHtmlFormat, false);

	gpSetCls->CheckSelectionModifiers(hDlg);

	return 0;
}