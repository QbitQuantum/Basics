LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int id;
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	switch (msg) {
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			hPen = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
			hOldPen = (HPEN)SelectObject(hdc, hPen);
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, 10, 10, 100, 100);
			
			DeleteObject(hBrush);
			hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			Rectangle(hdc, 50, 50, 150, 150);
			DeleteObject(hBrush);
			hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			Rectangle(hdc, 100, 100, 200, 200);
			DeleteObject(hBrush);
			hBrush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 255));
			SelectObject(hdc,hBrush);
			Rectangle(hdc, 150, 150, 250, 250);
			DeleteObject(hBrush);
			hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			Rectangle(hdc, 200, 200, 300, 300);
			DeleteObject(hBrush);
			hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			SelectObject(hdc, hBrush);
			Rectangle(hdc, 250, 250, 350, 350);
			DeleteObject(hPen);
			SelectObject(hdc, hOldPen);
			SelectObject(hdc, hOldBrush);
			EndPaint(hWnd, &ps);
			break;
		case WM_CLOSE:
			id = MessageBox(hWnd,
				TEXT("終了してもよろしいですか"),
				TEXT("確認"),
				MB_YESNO | MB_ICONQUESTION);
			if (id == IDYES)
				DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return (DefWindowProc(hWnd, msg, wp, lp));
	}
	return 0;
}