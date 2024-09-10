LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HICON		hFill, hEmpty;
	static HCURSOR		hCursor;
	static RECT			rc = { 50, 50 , 82, 82 };	// 32 * 32
	static HINSTANCE	hInst;

	static HWND hwndPrev = (HWND)-1;
	switch( msg )
	{
	case WM_MOUSEMOVE:
		// 1. 현재 마우스를 누가ㅣ 소유?? ( 본인소유..)
		if( GetCapture() == hwnd)
		{
			POINT pt;
			// 현재 마우스 포인터 위치?? 스크린 좌표...
			GetCursorPos(&pt);

			// 핸들값... 현재 마우스 포인터 아래의...
			HWND hCur = WindowFromPoint(pt);
			
			if( hCur != hwnd && hCur != hwndPrev)
			{
				// 이전의 핸들값.. 
				DrawInvertRect(hwndPrev);
				// 현재의 핸들값..
				DrawInvertRect(hCur);
				hwndPrev = hCur;
			}
		}
		return 0;

	// 마우스 캡쳐가 해지 될 때 호출되는 핸들러..
	// 이 메시지에서 화면을 무효화 하면 Icon이 다시 그려진다...
	case WM_CAPTURECHANGED:
		InvalidateRect(hwnd, &rc, TRUE);
		//---------------- 추가 ---------------------------
		DrawInvertRect(hwndPrev);
		hwndPrev = (HWND)-1;
		//--------------------------------------------------
		return 0;

	// 초기화
	case WM_CREATE:
		// Instance 얻기..
		hInst		= ( ( LPCREATESTRUCT)lParam)->hInstance;

		hFill		= LoadIcon  ( hInst, MAKEINTRESOURCE(IDI_ICONFILL));
		hEmpty		= LoadIcon  ( hInst, MAKEINTRESOURCE(IDI_ICON_EMPTY));
		hCursor		= LoadCursor( hInst, MAKEINTRESOURCE(IDC_CURSOR_TARGET));
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc			= BeginPaint(hwnd, &ps);
			DrawIcon( hdc, rc.left, rc.top, hFill);	
			EndPaint(hwnd, &ps);
		}
		return 0;

	case WM_LBUTTONDOWN:
		{
			POINT  pt		=  { LOWORD(lParam), HIWORD(lParam) };

			// 아이콘 영역 안인가??
			if( PtInRect( &rc, pt ) )
			{
				// 1. 마우스 캡쳐 
				SetCapture(hwnd);

				// 2. 아이콘 변경
				HDC  hdc = GetDC(hwnd);
				DrawIcon(hdc, rc.left, rc.top, hEmpty);

				ReleaseDC(hwnd, hdc);

				// 3. 커서 변경
				SetCursor( hCursor);
			}
		}
		return 0;

	case WM_LBUTTONUP:
		if( GetCapture() == hwnd )
			ReleaseCapture();
		return 0;

	case WM_RBUTTONDOWN:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}