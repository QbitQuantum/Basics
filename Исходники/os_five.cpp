DWORD WINAPI ThreadProcSquare(LPVOID pParam){
	HWND hWnd = g_hWnd;
	HDC hdc = g_hdc;;
	PAINTSTRUCT ps;
	HBRUSH hBrush;
	SetDCBrushColor(hdc, BLACK);
	hBrush = GetStockBrush(DC_BRUSH);
	SelectObject(hdc, hBrush);
	int x, y;
	//顺时针方向描点画矩形
	for (x = 160; x < 340; x++){
		SetPixel(hdc, x, 160, BLACK);
		Sleep(50);
	}
	for (y = 160; y < 340; y++){
		SetPixel(hdc, 340, y, BLACK);
		Sleep(50);
	}
	for (x = 340; x > 160; x--){
		SetPixel(hdc, x, 340, BLACK);
		Sleep(50);
	}
	for (y = 340; y > 160; y--){
		SetPixel(hdc, 160, y, BLACK);
		Sleep(50);
	}
	DeleteObject(hBrush);
	EndPaint(hWnd, &ps);
	ReleaseDC(hWnd, hdc);
	return 0;
}