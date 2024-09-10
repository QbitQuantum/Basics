LRESULT WINAPI SmpEditFrameProc
(
	HWND     hWnd,
	UINT	 message,
	WPARAM   wParam,
	LPARAM   lParam
)
{ // 1
    switch (message) 
	{
		case WM_ERASEBKGND: //2
		{
			HDC hDC = (HDC)wParam;
			HBRUSH hFill;
			RECT rect = {0, 0, 0, 0};
			     
			GetClientRect(hWnd, &rect);
			
			if (hFill = CreateSolidBrush(GetSysColor(COLOR_WINDOW))) //3
			{
				FillRect(hDC, (LPRECT)&rect, hFill);
				DeleteObject(hFill);
			}
			
			break;
		}

		// Nonsense code added for test
		case 0: //4
			if (hWnd) //5 
			{
				MessageBox (hWnd,"","",MB_OK);
			}
			else
			{
				MessageBox (hWnd,"","",MB_OK);
			}
			break;

		// Nonsense code added for test
		case 1: //6
			if (hWnd) //7
			{
				MessageBox (hWnd,"","",MB_OK);
			}
			else
			{
				MessageBox (hWnd,"","",MB_OK);
			}
			break;

		// Nonsense code added for test
		case 2: //8
			if (hWnd) //9
			{
				MessageBox (hWnd,"","",MB_OK);
			}
			else
			{
				MessageBox (hWnd,"","",MB_OK);
			}
			break;

		// Nonsense code added for test
		default:
			if (hWnd) //10
				if (hWnd)
					if (hWnd)
						if (hWnd)
							if (hWnd)
								if (hWnd)
									if (hWnd)
										if (hWnd)
											if (hWnd)
												if (hWnd)
													if (hWnd) // 20
														if (hWnd) 
															if (hWnd) //22
			{
				MessageBox (hWnd,"","",MB_OK);
			}
			else
			{
				MessageBox (hWnd,"","",MB_OK);
			}
			break;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}