// A function which is called from RefreshScreen
void NetGseEx::RefreshScreenProcess(HINSTANCE hinst, HWND hwnd, HDC hdc)
{
	int EleCnt = 0;

	// Draw background
	OfficeGSE::DrawBackground(hinst, hwnd, hdc);

	for (int i = 0; i < m_CurrentRequest; i++) {
		int c = m_ActReq[i]->GetActorId();
		int r = m_ActReq[i]->GetRequest();
		if (c != 0 && r >= 100) {
			// Draw Link of each element
			DrawOfficeASELink(hinst, hwnd, hdc, m_ActReq[i]);
		} else if (c == 0) {
			// Draw OfficeManagerASE
			OfficeGSE::DrawOfficeManagerASE(hinst, hwnd, hdc, m_ActReq[i]);
		}
	}
	for (int i = 0; i < m_CurrentRequest; i++) {
		int c = m_ActReq[i]->GetActorId();
		int r = m_ActReq[i]->GetRequest();
		// Draw OfficeASE
		if (c != 0 && r < 100) {
			EleCnt++;
			DrawOfficeASE(hinst, hwnd, hdc, m_ActReq[i]);
		}
	}

	// RunTime information
	static DWORD ctime = 0;
	static DWORD ptime = 0;
	ctime = GetTickCount();
	if (ptime != 0) {
		RtiRefreshInterval = ctime - ptime;
	} else {
		RtiRefreshInterval = 0;
	}
	ptime = ctime;
	RtiElementCount = EleCnt;
	RtiRequestCount = m_CurrentRequest;
	RtiRunningCount = GetNumOfRunStkThread();

	SetMouseAction(0);

	// When some threads are running...
	if (GetNumOfRunStkThread() != 0) {
		int ArsWidth = m_ActiveRSRight - m_ActiveRSLeft;
		int ArsHeight = m_ActiveRSBottom - m_ActiveRSTop;
		static int StatusRunX[4];
		static int StatusRunY[4];
		static int RunningRefreshInterval = 0;
		if (RunningRefreshInterval >= 1000) {
			RunningRefreshInterval = 0;
		}
		if (RunningRefreshInterval == 0) {
			for (int Loop = 0; Loop < 4; Loop++) {
				StatusRunX[Loop] = rand() % (ArsWidth - 200) + m_ActiveRSLeft;
				StatusRunY[Loop] = rand() % (ArsHeight - 80) + m_ActiveRSTop;
			}
		}
		RunningRefreshInterval += RtiRefreshInterval;

		int NumOfOut = 1;
		if (ArsWidth * ArsHeight >= 1310720) { // >= SXGA
			NumOfOut = 4;
		} else if (ArsWidth * ArsHeight >= 786432) { // >= XGA
			NumOfOut = 3;
		} else if (ArsWidth * ArsHeight >= 480000) { // >= SVGA
			NumOfOut = 2;
		}
		for (int Loop = 0; Loop < NumOfOut; Loop++) {
			StkFont::GetInstance()->ArialFontLargeTextOut(hdc, StatusRunX[Loop], StatusRunY[Loop], MyMsgProc::GetMsg(MyMsgProc::STKFW_RUNNING), RGB(255, 255, 255), FALSE);
		}

		EnterCriticalSection(&CritSect);
		ResetWorkspace(3);
		GetViewFromDb();
		LeaveCriticalSection(&CritSect);
	}

	ClearRequest();
}