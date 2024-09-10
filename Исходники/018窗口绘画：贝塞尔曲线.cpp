//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
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
	static POINT apt[4];
	static int cxClient, cyClient;
	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		apt[0].x = cxClient/4;
		apt[0].y = cyClient/2;

		apt[1].x = cxClient/2;
		apt[1].y = cyClient/4;

		apt[2].x = cxClient/2;
		apt[2].y = cyClient/4*3;

		apt[3].x = cxClient/4*3;
		apt[3].y = cyClient/2;
		break;
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
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		PolyBezier(hdc, apt, 4);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		SelectObject(hdc, GetStockObject(WHITE_PEN));
		PolyBezier(hdc, apt, 4);
		apt[1].x = LOWORD(lParam);
		apt[1].y = HIWORD(lParam);
		SelectObject(hdc, GetStockObject(BLACK_PEN));
		PolyBezier(hdc, apt, 4);
		ReleaseDC(hWnd, hdc);
		break;
	case  WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);
		SelectObject(hdc, GetStockObject(WHITE_PEN));
		PolyBezier(hdc, apt, 4);
		apt[2].x = LOWORD(lParam);
		apt[2].y = HIWORD(lParam);
		SelectObject(hdc, GetStockObject(BLACK_PEN));
		PolyBezier(hdc, apt, 4);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}