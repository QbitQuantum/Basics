VOID DoPaint(HWND hWnd, DWORD dwMode)
{
	HBITMAP ghBitmap = (HBITMAP)LoadImage(NULL,"startpic.bmp",IMAGE_BITMAP,0,0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	PAINTSTRUCT ps;
	RECT rect;
	HDC hdcMem;
	BITMAP bm;
	HDC hDC = BeginPaint(hWnd, &ps);
	GetClientRect(hWnd, &rect);
	SetStretchBltMode(hDC, HALFTONE);
	hdcMem = CreateCompatibleDC(hDC);
	SelectObject(hdcMem, ghBitmap);
	if (ghBitmap)
	{
		if (GetObject(ghBitmap, sizeof(BITMAP), &bm))
		{
			if(dwMode == 1)
			{
				StretchBlt(hDC, 0, 0, rect.right, rect.bottom,
					hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
			}
			else
			{
				INT ixStart = (rect.right - rect.left - bm.bmWidth)/2;
				INT iyStart = (rect.bottom - rect.top - bm.bmHeight)/2;
				ixStart = ixStart < 0 ? 0 : ixStart;
				iyStart = iyStart < 0 ? 0 : iyStart;
				BitBlt(hDC, 0, 0, rect.right, rect.bottom,
					hdcMem,-ixStart,-iyStart, SRCCOPY);
			}
			DeleteDC(hdcMem);
		}
	}

	else
	{
		PatBlt(hDC, 0, 0, rect.right, rect.bottom, BLACKNESS);
	}
	//EndPaint(hWnd, &ps);
}