LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT pPaint;
    HDC         hDC;
    HPEN        hPen, hOldPen;
    HBRUSH      hBrush;
    float       rad, x0, y0, x1, y1;

    switch (uMsg) {
    case WM_CREATE:
      SetTimer(hWnd, 1000, 1000, NULL);
      return 0;

    case WM_PAINT:
      hDC = BeginPaint(hWnd, &pPaint);

      hPen    = CreatePen(PS_DOT, 2, RGB(0, 255, 0));
      hOldPen = SelectObject(hDC, hPen);
      for (rad = 0; rad < 2 * PI; rad += (2 * PI) / 60) {
	x0 = sin(rad) * 100 + 200;
	y0 = cos(rad) * 100 + 200;

	x1 = sin(rad) * 90 + 200;
	y1 = cos(rad) * 90 + 200;

	MoveToEx(hDC, x0, y0, NULL);
	LineTo(hDC, x1, y1);
      }
      SelectObject(hDC, hOldPen);
      DeleteObject(hPen);

      hPen    = CreatePen(PS_DOT, 2, RGB(255, 0, 0));
      hOldPen = SelectObject(hDC, hPen);
      for (rad = 0; rad < 2 * PI; rad += (2 * PI) / 12) {
	x0 = sin(rad) * 100 + 200;
	y0 = cos(rad) * 100 + 200;

	x1 = sin(rad) * 80 + 200;
	y1 = cos(rad) * 80 + 200;

	MoveToEx(hDC, x0, y0, NULL);
	LineTo(hDC, x1, y1);
      }
      SelectObject(hDC, hOldPen);
      DeleteObject(hPen);

      hPen    = CreatePen(PS_DOT, 5, RGB(0, 0, 0));
      hOldPen = SelectObject(hDC, hPen);

      x1 = sin(((2.0 * PI) / 12.0) * 3.0) * 70 + 200;
      y1 = cos(((2.0 * PI) / 12.0) * 3.0) * 70 + 200;
      MoveToEx( hDC, 200, 200, NULL );
      LineTo( hDC, x1, y1 );

      x1 = sin(((2.0 * PI) / 12.0) * 5.0) * 50 + 200;
      y1 = cos(((2.0 * PI) / 12.0) * 5.0) * 50 + 200;
      MoveToEx( hDC, 200, 200, NULL );
      LineTo( hDC, x1, y1 );

      SelectObject(hDC, hOldPen);
      DeleteObject(hPen);

      EndPaint( hWnd, &pPaint );

      break;

    case WM_TIMER:
      {
	// dprintf(" WM Timer \n");
	SYSTEMTIME local;
	GetLocalTime( &local );
      }
      return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}