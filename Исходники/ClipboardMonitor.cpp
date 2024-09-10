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

	static HWND hwndNextViewer; 
	HGLOBAL hGlobal;
	PTSTR pGlobal;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		hwndNextViewer = SetClipboardViewer(hWnd);
		break;
	case WM_CHANGECBCHAIN:
		if((HWND)wParam == hwndNextViewer)
			hwndNextViewer = (HWND)lParam;
		else if(hwndNextViewer)
			SendMessage(hwndNextViewer, message, wParam, lParam);
		//return 0;
		break;
	case WM_DRAWCLIPBOARD:
		if(hwndNextViewer)
			SendMessage(hwndNextViewer, message, wParam, lParam);
		InvalidateRect(hWnd, NULL, TRUE);
		//return 0;
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
		// OpenClipboard, GetClipboardData, CloseClipboard
		GetClientRect(hWnd, &rect);
		OpenClipboard(hWnd);
#ifdef UNICODE
		hGlobal = GetClipboardData(CF_UNICODETEXT);
#else 
		hGlobal = GetClipboardData(CF_TEXT);
#endif
		if(hGlobal != NULL)
		{
			pGlobal = (PTSTR)GlobalLock(hGlobal);
			DrawText(hdc, pGlobal, -1, &rect, DT_EXPANDTABS);
			GlobalUnlock(hGlobal);
		}
		CloseClipboard();

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		ChangeClipboardChain(hWnd, hwndNextViewer);
		PostQuitMessage(0);
		//return 0;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}