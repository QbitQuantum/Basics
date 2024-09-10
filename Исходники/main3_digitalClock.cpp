LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam,LPARAM lParam)
{

	static BOOL           f24Hour, fSuppress ;

	static HBRUSH         hBrushRed ;

	static int            cxClient, cyClient ;

	HDC                   hdc ;

	PAINTSTRUCT   ps ;

	TCHAR                 szBuffer [2] ;


	switch (message)
	{

	case   WM_CREATE:

		hBrushRed = CreateSolidBrush (RGB (255, 0, 0)) ;

		SetTimer (hwnd, ID_TIMER, 1000, NULL) ;// fall through


	case   WM_SETTINGCHANGE:

		GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_ITIME, szBuffer, 2) ;
		f24Hour = (szBuffer[0] == '1') ;

		GetLocaleInfo (LOCALE_USER_DEFAULT, LOCALE_ITLZERO, szBuffer, 2) ;
		fSuppress = (szBuffer[0] == '0') ;

		InvalidateRect (hwnd, NULL, TRUE) ;
		return 0 ;


	case   WM_SIZE:

		cxClient = LOWORD (lParam) ;

		cyClient = HIWORD (lParam) ;

		return 0 ;


	case   WM_TIMER:

		InvalidateRect (hwnd, NULL, TRUE) ;

		return 0 ;


	case   WM_PAINT:

		hdc = BeginPaint (hwnd, &ps) ;

		SetMapMode (hdc, MM_ISOTROPIC) ;

		SetWindowExtEx (hdc, 276, 72, NULL) ;
		SetViewportExtEx (hdc, cxClient, cyClient, NULL) ;


		SetWindowOrgEx (hdc, 138, 36, NULL) ;
		SetViewportOrgEx (hdc, cxClient / 2, cyClient / 2, NULL) ;

		SelectObject (hdc, GetStockObject (NULL_PEN)) ;
		SelectObject (hdc, hBrushRed) ;


		DisplayTime (hdc, f24Hour, fSuppress) ;


		EndPaint (hwnd, &ps) ;

		return 0 ;


	case   WM_DESTROY:

		KillTimer (hwnd, ID_TIMER) ;

		DeleteObject (hBrushRed) ;

		PostQuitMessage (0) ;

		return 0 ;

	}

	return DefWindowProc (hwnd, message, wParam, lParam) ;

}