// OBS£UGA ZDARZEÑ
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			RECT screen;
			GetClientRect(hwnd, &screen);
			SetMapMode(hdc, MM_ANISOTROPIC);
			SetWindowExtEx(hdc, 700, 500, 0);
			SetViewportExtEx(hdc, screen.right, screen.bottom, 0);
			
			Test.draw(hdc);
			//tiles->draw(hdc);
			EndPaint(hwnd, &ps);
		}
		break;
	case WM_CLOSE:
		{
		DestroyWindow( hwnd );
		break;
		}
	case WM_DESTROY:
		{
		PostQuitMessage( 0 );
		break;
		}
	default:
		return DefWindowProc( hwnd, msg, wParam, lParam );
	}

	return 0;
}