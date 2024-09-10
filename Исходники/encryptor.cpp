LRESULT CALLBACK EncProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
	PAINTSTRUCT ps;
	static HWND hButton;
	HDC hdc, hMdc;
	TCHAR buf[256];
	static int flag = 0;
	static WCHAR chr[MAXLENGTH + MAX_PATH];
	char filename[MAXLENGTH + MAX_PATH], outfilename[MAXLENGTH + MAX_PATH] = { '\0' };
	static BITMAP bm;
	static OPENFILENAME ofn = { 0 };
	static TCHAR strFile[MAX_PATH], strCustom[256] = TEXT("Before files\0*.*\0\0");
	static HBITMAP hBitmap;

	switch (msg){
	case WM_CREATE:
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFilter = TEXT("Bitmap files {*.bmp}\0*.bmp\0")
			/*TEXT("他のファイルも同様の形式で")*/;
		ofn.lpstrCustomFilter = strCustom;
		ofn.nMaxCustFilter = 256;
		ofn.nFilterIndex = 0;
		ofn.lpstrFile = strFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_FILEMUSTEXIST;
		GetOpenFileName(&ofn);

		// プッシュボタンを作成する
		hButton = CreateWindow(
			_T("BUTTON"),                            // ウィンドウクラス名
			_T("GO"),                             // キャプション
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,   // スタイル指定
			bm.bmWidth + 20, 200,                                // 座標
			60, 40,                                  // サイズ
			hWnd,                                    // 親ウィンドウのハンドル
			(HMENU)BUTTON_ID,                        // メニューハンドル
			((LPCREATESTRUCT)lp)->hInstance,                                   // インスタンスハンドル
			NULL                                     // その他の作成データ
			);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);     // 描画処理を開始します。
		SetBkMode(hdc, TRANSPARENT);    // 背景を透過モードにします
		if (flag==0){
			hBitmap = (HBITMAP)LoadImage(NULL, (LPCWSTR)ofn.lpstrFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			//エラー処理
			if (hBitmap == NULL){
				MessageBox(hWnd, TEXT("FailedToOpenFile"), TEXT("はい..."), MB_OK);
				PostMessage(hWnd, WM_CLOSE, 0, 0);
				EndPaint(hWnd, &ps);
				break;
			}
			hMdc = CreateCompatibleDC(hdc);
			SelectObject(hMdc, hBitmap);
			GetObject(hBitmap, sizeof(BITMAP), &bm);
			BitBlt(hdc, 5, 5, bm.bmWidth, bm.bmHeight, hMdc, 0, 0, SRCCOPY);
		}
		else{
			//ひらいた画像ファイルを表示
			hBitmap = (HBITMAP)LoadImage(NULL, (LPCWSTR)chr, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			if (hBitmap == NULL){
				MessageBox(hWnd, TEXT("FailedToOpenFileofOutput"), TEXT("はい..."), MB_OK);
				PostMessage(hWnd, WM_CLOSE, 0, 0);
				EndPaint(hWnd, &ps);
				break;
			}
			hMdc = CreateCompatibleDC(hdc);
			SelectObject(hMdc, hBitmap);
			if (!BitBlt(hdc, bm.bmWidth + 100, 5, bm.bmWidth, bm.bmHeight, hMdc, 0, 0, SRCCOPY))
				MessageBox(hWnd, TEXT("FailedTobitbltofoutput"), TEXT("はい..."), MB_OK);
		}
		MoveWindow(
			hButton,      // ウィンドウのハンドル
			bm.bmWidth + 25,          // 横方向の位置
			200,          // 縦方向の位置
			60,     // 幅
			40,    // 高さ
			false   // 再描画オプション
			);
	/*	DeleteDC(hMdc);
		DeleteObject(hBitmap);
		EndPaint(hWnd, &ps);*/
		break;
	case WM_COMMAND:
		GetClassName(hWnd, buf, 255);
		switch (LOWORD(wp)){
		case BUTTON_ID:
			setlocale(LC_ALL, "japanese");
			//ひらいた画像ファイルを表示
			wcstombs_s(0, filename, MAXLENGTH + MAX_PATH, ofn.lpstrFile, _TRUNCATE);
			if (!Encryption(filename)){
				MessageBox(hWnd, TEXT("4545"), TEXT("変換に失敗した..."), MB_OK);
				return -1;
			}
			else{
				wcscpy(chr,ofn.lpstrFile);
				wcscat(chr,_T("_conv.bmp"));
				++flag; //ここでスイッチを切れ変える。
				flag &= 1;
				InvalidateRect(
					hWnd,           // ウィンドウのハンドル
					NULL,  // 長方形の座標
					false          // 消去するかどうかの状態
					);
			}
			break;
		default:
			return (DefWindowProc(hWnd, msg, wp, lp));
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}