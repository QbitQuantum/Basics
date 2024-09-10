LRESULT CALLBACK WndProc ( HWND hwnd, UINT message, WPARAM wParam,LPARAM lParam)
        
{
	static int startx = START_X, starty = START_Y;
	static HBITMAP hBitmap;
	static int                    cxClient, cyClient, cxSource, cySource ;
	HDC                           hdc, hdcMem ;
	int                           x, y ;
	PAINTSTRUCT                  ps ;

 	int i;

	switch (message)
	{
		case   WM_CREATE:
			test_init();
			return 0 ;
			
		case   WM_SIZE:
			return 0 ;
		case   WM_TIMER:
			OutputDebugString("TIMER");
			//Invalidate();
			g_frame_id+=1;
			if(g_frame_id >= g_frame_num)
				g_frame_id=0;
			//SendMessage(hwnd, WM_PAINT, 0, 0);
			InvalidateRect(hwnd, NULL, FALSE);
			return 1;
			
		case   WM_PAINT:
			cxSource      = WIDTH;
			cySource      = HEIGHT;
			cxClient = WIDTH;
			cyClient = HEIGHT;
			OutputDebugString("Paint\n");
			
			hdc = GetDC (hwnd);
			hdcMem = CreateCompatibleDC (hdc);
			hBitmap = CreateCompatibleBitmap (hdc, WIDTH, HEIGHT);

			fill_datas();
			
			SetBitmapBits(hBitmap, sizeof datas, datas);
			GetBitmapBits(hBitmap, sizeof datas, datas);				

			ReleaseDC (hwnd, hdc) ;
			SelectObject (hdcMem, hBitmap) ;
			
			hdc = BeginPaint(hwnd, &ps);
			for (y = starty ; y < starty + cyClient ; y += cySource)
			{
				for (x = startx ; x < startx + cxClient ; x += cxSource)
				{
					BitBlt (hdc, x, y, cxSource, cySource, hdcMem, 0, 0, SRCCOPY) ;
					//StretchBlt (hdc, x, y, cxClient, cyClient,hdcMem, 0, 0, cxSource, cySource, MERGECOPY) ;
				}
			}
			EndPaint (hwnd, &ps) ;
			DeleteDC (hdcMem) ;
			DeleteObject (hBitmap) ;
			return 0 ;
			
		case   WM_DESTROY:
			PostQuitMessage (0) ;
			test_end();
			return 0 ;
	}
	return DefWindowProc (hwnd, message, wParam, lParam) ;
}