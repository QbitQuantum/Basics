LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)//视窗讯息处理程式
{
	//CS_视窗类别样式
	//CW_建立视窗
	//DT_绘制文字
	//IDI_图示ID
	//IDC_游标ID
	//MB_讯息方块
	//SND_声音
	//WM_视窗讯息
	//WS_视窗样式
	//WHITE_BRUSH、LTGRAY_BRUSH、GRAY_BRUSH、DKGRAY_BRUSH、BLACK_BRUSH 和NULL_BRUSH
	HDC hdc;
	PAINTSTRUCT ps;
	//	RECT rect;
	static POINT aptFigure[10] = { 10, 70, 50,70, 50, 10, 90, 10, 90, 50, 30, 50, 30, 90, 70, 90, 70, 30,10, 30 };
	static int cxClient,cyClient;
	int i;
	POINT apt[10];
	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(GRAY_BRUSH));
		for (i = 0; i < 10; ++i)
		{
			apt[i].x = cxClient*aptFigure[i].x / 200;
			apt[i].y = cyClient*aptFigure[i].y / 100;
		}
		SetPolyFillMode(hdc, ALTERNATE);
		Polygon(hdc, apt, 10);

		for (i = 0; i < 10;++i)
		{
			apt[i].x += cxClient / 2;
		}
		SetPolyFillMode(hdc, WINDING);
		Polygon(hdc, apt, 10);

		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	//视窗讯息处理程式不予处理的所有讯息提供内定处理
	return DefWindowProc(hwnd, message, wParam, lParam);
}