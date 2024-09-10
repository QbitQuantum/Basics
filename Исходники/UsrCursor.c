int WINAPI
ShowCursor(BOOL fShow)
{
    LPVOID lpWinData;
    LPCURSORINFO lpCursorInfo;

    APISTR((LF_API,"ShowCursor: %x\n",fShow));

    if (fShow) {
	if (++(InternalCursor.nCount) == 0)
	    if (!(DRVCALL_CURSORS(PCH_SHOWCURSOR,0L,0L,0L)) &&
				InternalCursor.hCursor) {
		TWIN_DefineCursorWindow();
		lpWinData = (LPVOID)((InternalCursor.hWnd)?
			(LPVOID)WIN_GETDRVDATA(InternalCursor.hWnd):
			NULL);
		DRVCALL_CURSORS(PCH_SETCURSOR,InternalCursor.lpDrvData,
					lpWinData,0L);
	    }
    }
    else {
	if (--(InternalCursor.nCount) == -1) {
	    if (!DRVCALL_CURSORS(PCH_HIDECURSOR,0L,0L,0L)) {
		if (!hNullCursor)
		    hNullCursor = LoadCursor(0,"NULLCURSOR");
		lpCursorInfo = GETCURSORINFO(hNullCursor);
		TWIN_DefineCursorWindow();
		lpWinData = (LPVOID)((InternalCursor.hWnd)?
			(LPVOID)WIN_GETDRVDATA(InternalCursor.hWnd):
			NULL);
		DRVCALL_CURSORS(PCH_SETCURSOR,lpCursorInfo->lpCurData,
					lpWinData,0L);
		RELEASECURSORINFO(lpCursorInfo);
	    }
	}
    }
	    
    return InternalCursor.nCount;
}