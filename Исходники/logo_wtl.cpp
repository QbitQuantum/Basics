	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint( &ps );

		HDC hdcMem, hdcBB;
		HBITMAP hbmOld, hbmOldBB;
		BLENDFUNCTION func = { AC_SRC_OVER, 0, 0, 0 };

		ps.rcPaint.right -= ps.rcPaint.left;
		ps.rcPaint.bottom -= ps.rcPaint.top;

		if (frame < 400)
		{
			hdcMem = CreateCompatibleDC( hdc );
			hbmOld = (HBITMAP) SelectObject( hdcMem, frames[0] );

			BitBlt( hdc, ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right, ps.rcPaint.bottom, hdcMem,
				ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);

			SelectObject( hdcMem, hbmOld );
			DeleteDC( hdcMem );
		}
		else if (frame < 500)
		{
			hdcBB = CreateCompatibleDC( hdc );
			hbmOldBB = (HBITMAP) SelectObject( hdcBB, backbuffer );

			hdcMem = CreateCompatibleDC( hdc );
			hbmOld = (HBITMAP) SelectObject( hdcMem, frames[0] );

			BitBlt( hdcBB, ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right, ps.rcPaint.bottom, hdcMem,
				ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);

			SelectObject( hdcMem, frames[1] );

			func.SourceConstantAlpha = (frame - 400) * 255 / 100;

			AlphaBlend( hdcBB, ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right, ps.rcPaint.bottom, hdcMem,
				ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right, ps.rcPaint.bottom, func);

			SelectObject( hdcMem, hbmOld );
			DeleteDC( hdcMem );

			BitBlt( hdc, ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right, ps.rcPaint.bottom, hdcBB,
				ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);

			SelectObject( hdcBB, hbmOldBB );
			DeleteDC( hdcBB );
		}
		else if (frame < 900)
		{
			hdcMem = CreateCompatibleDC( hdc );
			hbmOld = (HBITMAP) SelectObject( hdcMem, frames[1] );

			BitBlt( hdc, ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right, ps.rcPaint.bottom, hdcMem,
				ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);

			SelectObject( hdcMem, hbmOld );
			DeleteDC( hdcMem );
		}
		else if (frame < 1000)
		{
			hdcBB = CreateCompatibleDC( hdc );
			hbmOldBB = (HBITMAP) SelectObject( hdcBB, backbuffer );

			hdcMem = CreateCompatibleDC( hdc );
			hbmOld = (HBITMAP) SelectObject( hdcMem, frames[1] );

			BitBlt( hdcBB, ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right, ps.rcPaint.bottom, hdcMem,
				ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);

			SelectObject( hdcMem, frames[0] );

			func.SourceConstantAlpha = (frame - 900) * 255 / 100;

			AlphaBlend( hdcBB, ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right, ps.rcPaint.bottom, hdcMem,
				ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right, ps.rcPaint.bottom, func);

			SelectObject( hdcMem, hbmOld );
			DeleteDC( hdcMem );

			BitBlt( hdc, ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right, ps.rcPaint.bottom, hdcBB,
				ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);

			SelectObject( hdcBB, hbmOldBB );
			DeleteDC( hdcBB );
		}

		EndPaint( &ps );

		return 0;
	}