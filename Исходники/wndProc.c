/*
	BOOL NEAR ScrollHorz(HWND, WORD, WORD)

	PURPOSE: Scrolls the window horizontally

	PARAMETERS:
		hWnd		- Handle to the terminal window
		wScrollCmd	- The type of scrolling we're doing
		wScrollPos	- The scroll bar's position
*/
BOOL NEAR ScrollHorz(HWND hWnd, WORD wScrollCmd, WORD wScrollPos) {
	SCROLLINFO	si;
	int			iScrollPos;

	si.cbSize	= sizeof(si);
	si.fMask	= SIF_ALL;
	GetScrollInfo(ghWndMain, SB_HORZ, &si);

	// Save the current position for comparison
	iScrollPos = si.nPos;

	switch (wScrollCmd) {
		case SB_TOP: // moved to the top
			si.nPos = si.nMin;
			break;

		case SB_BOTTOM: // moved to the bottom
			si.nPos = si.nMax;
			break;

		case SB_PAGEUP: // moved up by a page
			si.nPos -= si.nPage;
			break;

		case SB_PAGEDOWN: // moved down by a page
			si.nPos += si.nPage;
			break;

		case SB_LINEUP:	// move up a line
			si.nPos -= 10;
			break;

		case SB_LINEDOWN: // move down a line
			si.nPos += 10;
			break;

		case SB_THUMBTRACK: // manually positioned
			si.nPos = si.nTrackPos;
			break;

		default:
			return FALSE;
	}

	// Set the position and then retrieve it. Due to adjustments
	// by Windows, it may not be the same as the value set.
	si.fMask = SIF_POS;
	SetScrollInfo(ghWndMain, SB_HORZ, &si, TRUE);
	GetScrollInfo(ghWndMain, SB_HORZ, &si);

	// If the position has changed, scroll the window and update it
	if (si.nPos != iScrollPos) {
		ScrollWindow(ghWndMain, iScrollPos - si.nPos, 0, NULL, NULL);
		UpdateWindow(hWnd);
	}

	return TRUE;
}