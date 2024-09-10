//---------------------------------------------------------------------
// WM_CREATEメッセージ処理
//---------------------------------------------------------------------
LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam) {

	// 電源状態変数を初期化
	GetSystemPowerStatus(&g_sps);

	// 起動時の電源状態を記録
	SaveSystemPowerStatus(0, 0);

	RECT rcWork;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0);

	RECT rc;
	GetWindowRect(hwnd, &rc);

	SetWindowPos(
		hwnd,
		NULL,
		rcWork.right - (rc.right - rc.left),
		rcWork.bottom - (rc.bottom - rc.top),
		0, 0,
		SWP_NOREDRAW | SWP_NOSIZE | SWP_NOZORDER);

	return 0;
}