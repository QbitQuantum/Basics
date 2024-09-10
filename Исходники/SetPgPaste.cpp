LRESULT CSetPgPaste::OnInitDialog(HWND hDlg, bool abInitial)
{
	PasteLinesMode mode;

	mode = gpSet->AppStd.isPasteAllLines;
	checkRadioButton(hDlg, rPasteM1MultiLine, rPasteM1Nothing,
		(mode == plm_FirstLine) ? rPasteM1FirstLine
		: (mode == plm_SingleLine) ? rPasteM1SingleLine
		: (mode == plm_Nothing) ? rPasteM1Nothing
		: rPasteM1MultiLine);

	mode = gpSet->AppStd.isPasteFirstLine;
	checkRadioButton(hDlg, rPasteM2MultiLine, rPasteM2Nothing,
		(mode == plm_MultiLine) ? rPasteM2MultiLine
		: (mode == plm_FirstLine) ? rPasteM2FirstLine
		: (mode == plm_Nothing) ? rPasteM2Nothing
		: rPasteM2SingleLine);

	checkDlgButton(hDlg, cbClipConfirmEnter, gpSet->isPasteConfirmEnter);

	checkDlgButton(hDlg, cbClipConfirmLimit, (gpSet->nPasteConfirmLonger!=0));
	SetDlgItemInt(hDlg, tClipConfirmLimit, gpSet->nPasteConfirmLonger, FALSE);

	return 0;
}