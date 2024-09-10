// ---------------------------------------------------------------------
LRESULT WinSkinWindow::onDestroy(
	HWND hWnd,		// ウィンドウハンドル
	UINT uMsg,		// WM_DESTROY
	WPARAM wParam,	// 利用しないパラメータ
	LPARAM lParam	// 利用しないパラメータ
)
{
	// unregister CoverChangedEventHandler
	CoverManager* manager = CoveredCalcApp::GetInstance()->GetCoverManager();
	manager->UnregisterCoverChangeEventHandler(this);
	
	// MessageFilter としての自分自身を破棄
	WinCoveredCalcApp::GetInstance()->UninstallMessageFilter(this);

	// マウスキャプチャが残っていたら解除
	if (mouseCaptureNestCount > 0)
	{
		if (GetCapture() == m_hWnd)
		{
			ReleaseCapture();
		}
		mouseCaptureNestCount = 0;
	}
	// タイマが残っていたら終了
	SInt32 index;
	for (index = 0; index < TimerID_Max; index++)
	{
		if (timerNestCount[index] > 0)
		{
			KillTimer(m_hWnd, timerIdToWinTimerId(static_cast<TimerID>(index)));
			timerNestCount[index] = 0;
		}
	}

	base::wndProc(hWnd, uMsg, wParam, lParam);

	if (NULL != uiManager)
	{
		deleteUIManager(uiManager);
		uiManager = NULL;
	}
	
	::DestroyWindow(hToolTipWnd);
	hToolTipWnd = NULL;
	
	return 0;
}