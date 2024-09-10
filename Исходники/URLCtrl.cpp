static COLORREF getParentDlgBkColor(HWND hWnd)
{
	COLORREF crRet = CLR_INVALID;
	if (hWnd && IsWindow(hWnd))
	{
		HWND hWndParent = GetParent(hWnd);
		if (hWndParent)
		{
			RECT rc;
			if (GetClientRect(hWndParent, &rc))
			{
				HDC hDC = GetDC(hWndParent);
				if (hDC)
				{
					HDC hdcMem = CreateCompatibleDC(hDC);
					if (hdcMem)
					{
						HBITMAP hBmp = CreateCompatibleBitmap(hDC,
						rc.right, rc.bottom);
						if (hBmp)
						{
							HGDIOBJ hOld = SelectObject(hdcMem, hBmp);
							if (hOld)
							{
								if (SendMessage(hWndParent,	WM_ERASEBKGND, (WPARAM)hdcMem, 0))
								{
									crRet = GetPixel(hdcMem, 0, 0);
								}
								SelectObject(hdcMem, hOld);
							}
							DeleteObject(hBmp);
						}
						DeleteDC(hdcMem);
					}
					ReleaseDC(hWndParent, hDC);
				}
			}
		}
	}
	return crRet;
}