void DrawMap(HWND hWnd)
{
	HDC hDc = GetWindowDC(hWnd);

	HDC memDc = CreateCompatibleDC(NULL);  //缓存DC
	HBITMAP hBitMap = CreateCompatibleBitmap(hDc, 850, 650);
	SelectObject(memDc, hBitMap);
	//背景刷成绿色
	HBRUSH hBrushBack = CreateSolidBrush(RGB(0, 255, 0));
	RECT rectBack;
	rectBack.top = 0;
	rectBack.bottom = 650;
	rectBack.left = 0;
	rectBack.right = 850;
	FillRect(memDc, &rectBack, hBrushBack);

	DrawStoneAndBrike(memDc);
	
	DrawMan(memDc);

	BitBlt(hDc, 3, 25, 850, 650, memDc, 0, 0, SRCCOPY);//拷贝

	DeleteObject(memDc);
	DeleteObject(hBitMap);
	DeleteObject(hBrushBack);
	
	ReleaseDC(hWnd, hDc);
}