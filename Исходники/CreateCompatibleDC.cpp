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
	case WM_PAINT:
    {
		hdc = BeginPaint(hWnd, &ps);
		HDC comDC = CreateCompatibleDC(hdc);

        RECT rect;
        GetClientRect(hWnd, &rect);//这时还不能绘图，因为没有地方画 ^_^
        //下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小，也可以自己定义（如：有滚动条时就要大于当前窗口的大小，在BitBlt时决定拷贝内存的哪部分到屏幕上
        HBITMAP comBitmap = CreateCompatibleBitmap(hdc, 
            rect.right - rect.left, rect.bottom-rect.top);
        //将位图选入到内存显示设备中
        //只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
        HBITMAP oldBitmap = (HBITMAP)SelectObject(comDC, comBitmap);

        //先用背景色将位图清除干净，这里我用的是白色作为背景(否则会为黑色)
        //你也可以用自己应该用的颜色
        HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(comDC, &rect, brush);
        DeleteObject(brush);

        //进行绘图操作
        LineTo(comDC, 100, 100);
        LineTo(comDC, 300, 300);
        TextOut(comDC, 200, 200, L"兼容DC测试", 6);
        Rectangle(comDC, 500, 100, 800, 300);

        //将内存中的图拷贝到屏幕上进行显示
        BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom -rect.top, comDC,
            0, 0, SRCCOPY);

        //绘图完成后的清理
        DeleteObject(comBitmap);
        DeleteObject(comDC);
		EndPaint(hWnd, &ps);
		break;
    }
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}