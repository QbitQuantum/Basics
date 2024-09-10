//A simple example of call tips
void CCppDocContentView::OnDwellStart(_Inout_ SCNotification* pSCNotification)
{
	CScintillaCtrl& rCtrl = GetCtrl();

	//Only display the call tip if the scintilla window has focus
	CWnd* pFocusWnd = GetFocus();
	if (pFocusWnd)
	{
		if (pFocusWnd->GetSafeHwnd() == rCtrl.GetSafeHwnd())
		{
			//Get the previous 7 characters and next 7 characters around
			//the current dwell position and if it is "author " case insensitive
			//then display "PJ Naughter" as a call tip
			Sci_TextRange tr;
			tr.chrg.cpMin = max(0, pSCNotification->position - 7);
			tr.chrg.cpMax = min(pSCNotification->position + 7, rCtrl.GetLength());
			char sText[15];
			sText[0] = '\0';
			tr.lpstrText = sText;
			rCtrl.GetTextRange(&tr);

			//Display the call tip
			_strupr_s(sText, sizeof(sText));
			if (strstr(sText, "AUTHOR "))
				rCtrl.CallTipShow(pSCNotification->position, _T("PJ Naughter"));
		}
	}
}