INT_PTR CALLBACK LastResultDialogWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvt;
	switch(message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvt = HIWORD(wParam);
		switch (wmId)
		{
		case IDOK:
			EndDialog(hDlg, IDOK);
			return INT_PTR(TRUE);
		default:
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, IDOK);
		return (INT_PTR)TRUE;
	case WM_SHOWWINDOW:
		{
			HighScores::HighScoresRepository scoresRepository;
			std::vector<HighScores::MatchResult> lastMatchResults = scoresRepository.select(50, 0);
			SendDlgItemMessageA(hDlg, IDC_LSTHIGHSCORES, LB_RESETCONTENT, 0, 0);
			for(auto item = lastMatchResults.begin(); item != lastMatchResults.end(); ++item) {
				SendDlgItemMessageA(hDlg, IDC_LSTHIGHSCORES, LB_ADDSTRING, 0, (LPARAM)item->strRepr().c_str());	
			}
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}