/**********************************************
 * [関数名]
 *	WindowProc
 *
 * [説明]
 *	ウィンドウコールバック
 *
 **********************************************/
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/**********************************************
	 * 変数宣言
	 **********************************************/
	static HWND hClickButton;
	static int iFlgClickStart = FALSE;
	static int iClickCnt = 0;
	static UINT_PTR uTimerID;
	static long lStartClock, lCurrentClock;

	/**********************************************
	 * メッセージ処理
	 **********************************************/
	switch (uMsg) {
	case WM_CREATE:
		{
			/**********************************************
			 * メニュー表示
			 **********************************************/
			g_MyWnd.SetWndMenu(hWnd, (MY_LIB_WND_MENU*)MY_MENU, MENU_NUM);

			POINT point = {SPEED_CLICK_BUTTON_POS_X, SPEED_CLICK_BUTTON_POS_Y};
			SIZE sz = {SPEED_CLICK_BUTTON_WIDTH, SPEED_CLICK_BUTTON_HEIGHT};
			g_MyWnd.AddBasicButton(&hClickButton, hWnd, TEXT("クリック"), point, sz, ID_BUTTON_CLICK);
		}
		break;
	case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;
			TCHAR strTextTime[100] = TEXT("TIME: ");
			TCHAR strTextClick[100] = TEXT("クリック回数: ");
			TCHAR strTextTmp[100];

			/**********************************************
			 * クリック回数表示文字列生成
			 **********************************************/
			wsprintf(strTextTmp, TEXT("%d"), iClickCnt);
			wcscat_s(strTextClick, 100, strTextTmp);

			/**********************************************
			 * タイマ文字列生成
			 **********************************************/
			if (iFlgClickStart == TRUE) {
				lCurrentClock = lStartClock - clock();
				if (lCurrentClock <= 0) {
					lCurrentClock = 0;
					iFlgClickStart = FALSE;

					wsprintf(strTextTmp, TEXT("記録は %d 回でした."), iClickCnt);
					MessageBox(hWnd, strTextTmp, TEXT("終了！"), MB_OK);
				}
			} else {
				lCurrentClock = 0;
			}

			wsprintf(strTextTmp, TEXT("%03d'%02d.%03d"), lCurrentClock/60000, (lCurrentClock%60000)/1000, (lCurrentClock%60000)%1000);
			wcscat_s(strTextTime, 100, strTextTmp);

			hdc = BeginPaint(hWnd, &ps);

			SetBkColor(hdc, RGB(255, 255, 255));
			FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
			TextOut(hdc, SPEED_CLICK_TEXT_TIME_POS_X, SPEED_CLICK_TEXT_TIME_POS_Y, strTextTime, _tcslen(strTextTime));
			TextOut(hdc, SPEED_CLICK_TEXT_CLICK_POS_X, SPEED_CLICK_TEXT_CLICK_POS_Y, strTextClick, _tcslen(strTextClick));

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_MENU_GAME_EXIT:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case ID_MENU_MODE:
			{
				SIZE size = {SPEED_CLICK_DLG_MODE_WIDTH, SPEED_CLICK_DLG_MODE_HEIGHT};
				g_MyWnd.ModalDialog(hWnd, TEXT("モード選択"), ModeDlgProc, size, &etMode);
			}
			break;
		case ID_MENU_ABOUT:
			MessageBox(hWnd, TEXT("SpeedClick Version.0.0.1"), TEXT("バージョン情報"), MB_OK);
			break;
		case ID_BUTTON_CLICK:
			if (iFlgClickStart == FALSE) {
				uTimerID = SetTimer(hWnd, WM_TIMER, 1, NULL);
				switch (etMode) {
				case SPEED_CLICK_MODE_1s:
					lStartClock = clock() + 1*1000;
					break;
				case SPEED_CLICK_MODE_5s:
					lStartClock = clock() + 5*1000;
					break;
				case SPEED_CLICK_MODE_10s:
					lStartClock = clock() + 10*1000;
					break;
				case SPEED_CLICK_MODE_30s:
					lStartClock = clock() + 30*1000;
					break;
				default:
					lStartClock = clock() + 5*1000;
					break;
				}
				iClickCnt = 0;
				iFlgClickStart = TRUE;
			}

			iClickCnt ++;

			{
				RECT stUpdateRect = {SPEED_CLICK_TEXT_CLICK_POS_X, SPEED_CLICK_TEXT_CLICK_POS_Y, SPEED_CLICK_TEXT_CLICK_POS_X + SPEED_CLICK_WINDOW_WIDTH, SPEED_CLICK_TEXT_CLICK_POS_Y + 20};
				InvalidateRect(hWnd, &stUpdateRect, TRUE);
				UpdateWindow(hWnd);
			}

			break;
		default:
			break;
		}
		break;
	case WM_TIMER:
		{
			RECT stUpdateRect = {SPEED_CLICK_TEXT_TIME_POS_X, SPEED_CLICK_TEXT_TIME_POS_Y, SPEED_CLICK_TEXT_TIME_POS_X + SPEED_CLICK_WINDOW_WIDTH, SPEED_CLICK_TEXT_TIME_POS_Y + 20};
			InvalidateRect(hWnd, &stUpdateRect, TRUE);
			UpdateWindow(hWnd);
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("終了しますか？"), TEXT("確認"), MB_OKCANCEL) == IDOK) {
			g_MyWnd.DestroyMyWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	/**********************************************
	 * リターン
	 **********************************************/
	return 0;
}