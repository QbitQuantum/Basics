static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int res = 0;

	switch (message)
	{
		case WM_PAINT:
		{
			if (s_buffer)
			{
				StretchDIBits(s_hdc, 0, 0, s_width, s_height, 0, 0, s_width, s_height, s_buffer, 
							  &s_bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

				ValidateRect(hWnd, NULL);
			}

			break;
		}

		case WM_KEYDOWN:
		{
			if ((wParam&0xFF) == 27) 
				s_close = 1;

			break;
		}

		case WM_CLOSE:
		{
			s_close = 1;
			break;
		}

		default:
		{
			res = DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	return res;
}