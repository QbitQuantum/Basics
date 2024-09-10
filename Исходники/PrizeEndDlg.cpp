BOOL CPrizeEndDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMultiMonitor		multiMonitor;
	CRect				rect;
	CPoint				curPos;
	::GetCursorPos(&curPos);

#if _DEBUG
	multiMonitor.GetRectByEnum(1, rect);	// 0, 1 번 모니터 중 0 번은 무조건 주모니터이니까
	this->MoveWindow(rect);
#else
	this->MoveWindow(0, 0, m_pBackgroundImage->GetWidth(), m_pBackgroundImage->GetHeight());
#endif

	DWORD dwState;
	BOOL State = InternetGetConnectedState(&dwState,0);
	if(State == 0 || (State == 1 && (dwState & INTERNET_CONNECTION_OFFLINE))) {
		SetTimer(TID_EVENT_END_TIMEOUT, 1000 * 10, NULL);
		return TRUE;
	}

	LoadScreenText();
	SetTimer(TID_PRIZE_END_KICK_IDLE, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}