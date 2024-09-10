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
	RECT rect;

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
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	//画图
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		
		//MoveToEx(hdc,50,50,0);
		//LineTo(hdc,100,100);
		for (int i=1;i<nCount;i++)
		{
			MoveToEx(hdc,xPosition[i-1],yPosition[i-1],0);
			LineTo(hdc,xPosition[i],yPosition[i]);
		}

		//MoveToEx(hdc,xPosition[nCount-1],yPosition[nCount-1],0);
		//LineTo(hdc,xPosition[0],yPosition[0]);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		xPosition[nCount] = GET_X_LPARAM(lParam); 
		yPosition[nCount] = GET_Y_LPARAM(lParam); 
		nCount++;

		GetClientRect(hWnd,&rect);
		InvalidateRect(hWnd,&rect,TRUE);

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}