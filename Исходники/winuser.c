/* remove region from window update region*/
BOOL WINAPI
ValidateRgn(HWND hwnd, HRGN hrgn)
{
	if(hwnd) {
		if(!hrgn)
			/* remove client area from update region*/
			return ValidateRect(hwnd, NULL);

		/* passed region is in client coords, convert to screen*/
		GdOffsetRegion(((MWRGNOBJ *)hrgn)->rgn,
			hwnd->clirect.left, hwnd->clirect.top);
		GdSubtractRegion(hwnd->update, hwnd->update,
			((MWRGNOBJ *)hrgn)->rgn);
		GdOffsetRegion(((MWRGNOBJ *)hrgn)->rgn,
			-hwnd->clirect.left, -hwnd->clirect.top);

		/* if update region empty, mark window as painted*/
		if(hwnd->update->numRects == 0)
			if(hwnd->gotPaintMsg == PAINT_NEEDSPAINT)
				hwnd->gotPaintMsg = PAINT_PAINTED;
	}
	return TRUE;
}