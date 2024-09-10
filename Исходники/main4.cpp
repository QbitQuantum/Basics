LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)

{

	static POINT apt[4] ;

	HDC          hdc ;

	int          cxClient, cyClient ;

	PAINTSTRUCT  ps ;


	switch (message)

	{

	case WM_SIZE:

		cxClient = LOWORD (lParam) ;

		cyClient = HIWORD (lParam) ;



		apt[0].x = cxClient / 4 ;

		apt[0].y = cyClient / 2 ;



		apt[1].x = cxClient / 2 ;

		apt[1].y = cyClient / 4 ;



		apt[2].x = cxClient / 2 ;

		apt[2].y = 3 * cyClient / 4 ;



		apt[3].x = 3 * cxClient / 4 ;

		apt[3].y = cyClient / 2 ;



		return 0 ;


	case WM_LBUTTONDOWN:

	case WM_RBUTTONDOWN:

	case WM_MOUSEMOVE:

		if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)

		{

			hdc = GetDC (hwnd) ;

			SelectObject (hdc, GetStockObject (WHITE_PEN)) ;

			DrawBezier (hdc, apt) ;



			if (wParam & MK_LBUTTON)

			{

				apt[1].x = LOWORD (lParam) ;

				apt[1].y = HIWORD (lParam) ;

			}



			if (wParam & MK_RBUTTON)

			{

				apt[2].x = LOWORD (lParam) ;

				apt[2].y = HIWORD (lParam) ;

			}



			SelectObject (hdc, GetStockObject (BLACK_PEN)) ;

			DrawBezier (hdc, apt) ;

			ReleaseDC (hwnd, hdc) ;

		}

		return 0 ;

	case   WM_PAINT:

		InvalidateRect (hwnd, NULL, TRUE) ;



		hdc = BeginPaint (hwnd, &ps) ;



		DrawBezier (hdc, apt) ;



		EndPaint (hwnd, &ps) ;

		return 0 ;



	case WM_DESTROY:

		PostQuitMessage (0) ;

		return 0 ;

	}

	return DefWindowProc (hwnd, message, wParam, lParam) ;

}