int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	//HACCEL hAccelTable;
	int bnum;
	RECT screen;
	TCHAR ini_fname[256];

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CONEMU_WIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 表示領域の定義
	// 必要以外の再書き換えを防止する
	screen.left = 0;
	screen.right = 650;
	screen.top = 0;
	screen.bottom = 399;

	// ini ファイルから設定を読む
	if (MakeIniFileName(_T("CONEMU.ini"), ini_fname)) {
		int value;
		value = GetPrivateProfileInt(_T("FRAMERATE"), _T("FPS"), 7, ini_fname);
		switch (value)
		{
		case 60:
			FPSmode = FPS60;
			break;
		case 30:
			FPSmode = FPS30;
			break;
		case 15:
			FPSmode = FPS15;
			break;
		default:
			FPSmode = FPS07;
			break;
		}
		Offset_X2 = GetPrivateProfileInt(_T("200LINES"), _T("OFFSET_X"), 20, ini_fname);
		Offset_Y2 = GetPrivateProfileInt(_T("200LINES"), _T("OFFSET_Y"), 34, ini_fname);
		Offset_X4 = GetPrivateProfileInt(_T("400LINES"), _T("OFFSET_X"), 20, ini_fname);
		Offset_Y4 = GetPrivateProfileInt(_T("400LINES"), _T("OFFSET_Y"), 34, ini_fname);
	}

	// USB 初期化
	if (InitUSB()) {
		MessageBox(NULL, _T("初期化に失敗しました。\r\nケーブルの接続を確認してください。"), _T("エラー"), MB_OK);
		return 1;
	}

	reallocDIB();
	ImmDisableIME(-1);

	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	// 画面描画ポジションテーブル
	for (size_t i = 0; i < 400; i++)
	{
		ppos[i] = g_lppxDIB + RowBytes * ((Lines - 1) - i);
	}

	// メイン メッセージ ループ:
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!(GetMessage(&msg, NULL, 0, 0)))
			{
				// USB 解放
				TrashUSB();

				// ini ファイルに設定を書き込み
				if (MakeIniFileName(_T("CONEMU.ini"), ini_fname)) {
					TCHAR cstr[10];
					switch (FPSmode)
					{
					case FPS60:
						wsprintf(cstr, _T("60"));
						break;
					case FPS30:
						wsprintf(cstr, _T("30"));
						break;
					case FPS15:
						wsprintf(cstr, _T("15"));
						break;
					case FPS07:
						wsprintf(cstr, _T("07"));
						break;
					default:
						break;
					}
					WritePrivateProfileString(_T("FRAMERATE"), _T("FPS"), cstr, ini_fname);
					wsprintf(cstr, _T("%d"), Offset_X2);
					WritePrivateProfileString(_T("200LINES"), _T("OFFSET_X"), cstr, ini_fname);
					wsprintf(cstr, _T("%d"), Offset_Y2);
					WritePrivateProfileString(_T("200LINES"), _T("OFFSET_Y"), cstr, ini_fname);
					wsprintf(cstr, _T("%d"), Offset_X4);
					WritePrivateProfileString(_T("400LINES"), _T("OFFSET_X"), cstr, ini_fname);
					wsprintf(cstr, _T("%d"), Offset_Y4);
					WritePrivateProfileString(_T("400LINES"), _T("OFFSET_Y"), cstr, ini_fname);
				}

				return (int)msg.wParam;
			}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
		}
		else
		{
			bnum = ConvPixel();
			switch (bnum)
			{
			case 0:		// まだ1ライン分のデータが揃ってない
				break;
			case 399:	// 最下行のデータを受信
				InvalidateRect(hWnd, &screen, FALSE);
				break;
			default:
				break;
			}
		}
	}

}