//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
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
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_HELP_SPLASHSCREEN:
			ghDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_SPLASH), 0, Splash);
			ShowWindow(ghDlg, SW_SHOW);
			break;
		case ID_CONTROL_YIELD:
			if (!eval_null()){
				MessageBoxA(0, "You could only yield before a game start.", "Yield", 0);
				break;
			}
			mainboard[7][7] = 1;
			paint_board(hWnd);
			break;
		case ID_CONTROL_RESTART:
			clear_board(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:{
		Graphics *myGraphics;
		Pen *myPen;
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
		myGraphics = new Graphics(hdc);
		myPen = new Pen(Color(255, 0, 0, 0), 1);
		myGraphics->DrawRectangle(myPen, Rect(400, 20, 20, 20));
		for (int i = 0; i < 375; i += 25)
			myGraphics->DrawLine(myPen, 20, 20 + i, 370, 20 + i);
		for (int i = 0; i < 375; i += 25)
			myGraphics->DrawLine(myPen, 20 + i, 20, 20 + i, 370);
		delete myGraphics;
		delete myPen;
		EndPaint(hWnd, &ps);
		paint_board(hWnd);
	}
		break;
	case WM_DESTROY:
		GdiplusShutdown(gdiplusToken);
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		board_clicked(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}