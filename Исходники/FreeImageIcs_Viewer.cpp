//
//	Main window procedure
//
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int width, height;

	switch(msg)
	{
		case WM_PAINT:
		{
			//PaintRect(hwnd, hdc, RGB(255,0,0));
			HDC          hdc;
			PAINTSTRUCT  ps;
	
			// Get a device context for this window
			hdc = BeginPaint(hwnd, &ps);

			PaintRect(hwnd, hdc, RGB(255,0,0) );

			SetStretchBltMode(hdc, COLORONCOLOR);

			BitBlt(hdc, 0, 0, 800, 600, hbitmap_hdc, 0, 0, SRCCOPY); 

			// Release the device context
			EndPaint(hwnd, &ps);

			return 0;
		}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}