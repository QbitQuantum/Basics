//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:  メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 選択されたメニューの解析:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 描画コードをここに追加してください...
				int x, y;

		// 画像の表示
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				SetPixel(hdc, x, y, RGB(r[y][x], g[y][x], b[y][x]));
			}
		}

#if 0
		// 課題1
		// 左右を反転して表示
		/*
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				SetPixel(hdc, IMG_WIDTH - x, y, RGB(r[y][x], g[y][x], b[y][x]));
			}
		}
		*/

		// 課題2
		// 画像を明るくする
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				if (r[y][x] * KADAI2_VAL > UCHAR_MAX
					|| g[y][x] * KADAI2_VAL > UCHAR_MAX
					|| b[y][x] * KADAI2_VAL > UCHAR_MAX) {
					SetPixel(hdc, x, y, RGB(255, 255, 255));
				} else {
					SetPixel(hdc, x, y, RGB(r[y][x], g[y][x], b[y][x]));
				}
			}
		}

		// 倍率を自動的に見つける
		{
			int max = 0; // 最大値
			double m;    // 倍率

			// RGBの最大値を求める
			for (y = 0; y < IMG_HEIGHT; y++) {
				for (x = 0; x < IMG_WIDTH; x++) {
					if (max < r[y][x]) max = r[y][x];
					if (max < g[y][x]) max = g[y][x];
					if (max < b[y][x]) max = b[y][x];
				}
			}
			// 倍率を求める
			m = (double)UCHAR_MAX / max;

			// 倍率だけRGBをそれぞれ値を増やして表示
			for (y = 0; y < IMG_HEIGHT; y++) {
				for (x = 0; x < IMG_WIDTH; x++) {
					SetPixel(hdc, x, y, RGB(
						(unsigned char)(r[y][x] * m),
						(unsigned char)(g[y][x] * m),
						(unsigned char)(b[y][x] * m)));
				}
			}
		}
#endif
		// 課題3
		// ブレンド
		for (y = 0; y < IMG_HEIGHT; y++) {
			for (x = 0; x < IMG_WIDTH; x++) {
				// RGBそれぞれの平均を表示
				SetPixel(hdc, x, y, RGB(
					(r[y][x] + r2[y][x]) / 2,
					(g[y][x] + g2[y][x]) / 2,
					(b[y][x] + b2[y][x]) / 2));
			}
		}

		// 課題4
		// モーフィングの基礎
		{
			double n; // ブレンドする割合

			// 1枚目の画像をブレンドする割合を増やしながら画像を表示
			// (1枚目の割合がnなら2枚目は(1-n))
			for (n = 0.0; n <= KADAI4_N_MAX; n += KADAI4_N_IVAL) {
				for (y = 0; y < IMG_HEIGHT; y++) {
					for (x = 0; x < IMG_WIDTH; x++) {
						SetPixel(hdc, x, y, RGB(
							r[y][x] * n + r2[y][x] * (KADAI4_N_MAX - n),
							g[y][x] * n + g2[y][x] * (KADAI4_N_MAX - n),
							b[y][x] * n + b2[y][x] * (KADAI4_N_MAX - n)));
					}
				}
			}
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}