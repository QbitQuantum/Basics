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
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int id;
	RECT rc;
	HICON hIcon;

	CComPtr<IUnknown> pfunc;

	switch (msg)
	{
	case WM_CREATE:
		//ATLコントロールコンテナコードの初期化
		//これで、ActiveXコントロールを生成できるようになる
		if(!AtlAxWinInit()){
			MessageBox(hWnd, L"初期化エラー", L"エラー", MB_OK);
		}

		//ActiveXコントロールを生成
		hMyIE = CreateWindow( L"AtlAxWin7",	//クラス名
			L"Shell.Explorer.2",	//タイトル、GUID, ProgID, URLのいずれかを指定。
								//"Shell.Explorer.2"を指定すると必要に応じてスクロールバーが出てくる
			WS_CHILD | WS_VISIBLE , 0, 0, 0, 0, 
			hWnd, (HMENU)NULL, hInst, NULL);
		if(hMyIE == NULL){
			MessageBox(hWnd, L"hMyIE Error", L"エラー", MB_OK);
		}

		//このままでは、内容が何も見えないので、作成したウインドウのハンドルを指定して
		//ATLコントロールのダイレクトインターフェースポインタを取得
		AtlAxGetControl(hMyIE, &pfunc);
		pMyBr = pfunc;	//これをコントロールインターフェースポインタに格納

		//これでpMyBrを使って直接コントロールに命令できる
		//メンバーについては、"IWebBrowser2 Interface"のヘルプを参照
		pMyBr->GoHome();	//Home画面に行く

		break;
	case WM_SIZE:
		GetClientRect(hWnd, &rc);	//親ウインドウの表示領域を取得
		//hMyIEのサイズを親ウインドウのサイズにする
		MoveWindow(hMyIE, 0, 0, rc.right - rc.left, rc.bottom - rc.top, TRUE);
		break;
	case WM_COMMAND:
		// 選択されたメニューの解析:
		switch (LOWORD(wp))
		{
		case IDM_NAVI:
			if(DialogBox(hInst, L"MYURL", hWnd, (DLGPROC)MyUrlProc) == IDOK){
				//szUrlにジャンプする
				pMyBr->Navigate(CComBSTR(szUrl), NULL, NULL, NULL, NULL);
			}
			break;
		case IDM_RELOAD:
			pMyBr->Refresh();
			break;
		case IDM_END:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case IDM_HOME:
			pMyBr->GoHome();
			break;
		case IDM_PREVIOUS:
			pMyBr->GoBack();
			break;
		case IDM_NEXT:
			pMyBr->GoForward();
			break;
		case IDM_STOP:
			pMyBr->Stop();
			break;
		case IDM_ABOUT:
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_INETBR));
			ShellAbout(hWnd, L"猫でもわかるブラウザ#ブラウザ Ver0.9", L"Copyright(C) 2006 粂井康孝", hIcon);
			break;
		}
		break;
	case WM_CLOSE:
		id = MessageBox(hWnd, L"終了してもよろしいですか", (LPCWSTR)szAppName, MB_YESNO | MB_ICONQUESTION);
		if (id == IDYES)
			DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		//メモリをリリースする
		pMyBr.Release();
		pfunc.Release();
		_Module.Term();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
	return 0;
}