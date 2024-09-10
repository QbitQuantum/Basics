static void getScrollPos(HWND hwnd, int *xpos, int *ypos)
{
	SCROLLINFO si;

	ZeroMemory(&si, sizeof (SCROLLINFO));
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask = SIF_POS | SIF_TRACKPOS;
	if (GetScrollInfo(hwnd, SB_HORZ, &si) == 0)
		xpanic("error getting horizontal scroll position for Area", GetLastError());
	*xpos = si.nPos;
	// MSDN example code reinitializes this each time, so we'll do it too just to be safe
	ZeroMemory(&si, sizeof (SCROLLINFO));
	si.cbSize = sizeof (SCROLLINFO);
	si.fMask = SIF_POS | SIF_TRACKPOS;
	if (GetScrollInfo(hwnd, SB_VERT, &si) == 0)
		xpanic("error getting vertical scroll position for Area", GetLastError());
	*ypos = si.nPos;
}