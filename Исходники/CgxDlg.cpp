void CCgxDlg::OnBnClickedStart()
{
	CComboBox* gameList = (CComboBox*)GetDlgItem(IDC_GAME_LIST);
	CButton* startBtn = (CButton *)GetDlgItem(IDC_START);
	CEdit* script = (CEdit *)GetDlgItem(IDC_SCRIPT);
	CString strLine;

	int index = gameList->GetCurSel();
	if(gameManager.gameSize == 0 || index > gameManager.gameSize)
		return;
	if(gameManager.games[index]->isAIStart)
	{
		gameManager.games[index]->stopAI();
		startBtn->SetWindowTextW(TEXT("启动"));
	} 
	else
	{
		script->GetWindowTextW(strLine);
		gameManager.games[index]->script.loadScript((LPCWSTR)strLine);
		gameManager.games[index]->startAI();
		startBtn->SetWindowTextW(TEXT("停止"));
	}
}