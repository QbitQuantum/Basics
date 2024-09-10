BOOL FAR PASCAL ScrReSize (HWND hWnd, UINT wParam, WORD cx, WORD cy)

/* returns TRUE only if real resizing performed */
{
    BOOL    ChgWidth, ChgHeight;

    if ((wParam != SIZENORMAL) && (wParam != SIZEFULLSCREEN)) {
        return FALSE;
    }
    ChgWidth = (cx != GetWindowWord (hWnd, GWW_SCRCX));
    ChgHeight = (cy != GetWindowWord (hWnd, GWW_SCRCY));
    if (!ChgWidth && !ChgHeight) return FALSE;

    SetWindowWord (hWnd, GWW_SCRCX, cx);
    SetWindowWord (hWnd, GWW_SCRCY, cy);
    if (!InternalRequest) {
        SCREEN  *TopScreen;

        InternalRequest = TRUE;
        TopScreen = first_screen;
	select_screen ((SCREEN *)GetWindowLong (hWnd, GWL_SCRPTR), FALSE);
	if (ChgWidth) {
            newwidth (TRUE, DisplayableColumns (hWnd, cx, &EmacsCM));
        }
	if (ChgHeight) {
	    newsize (TRUE, DisplayableRows (hWnd, cy, &EmacsCM));
	}
	select_screen (TopScreen, FALSE);
	update (FALSE);
	InternalRequest = FALSE;
    }
    return TRUE;
} /* ScrReSize */