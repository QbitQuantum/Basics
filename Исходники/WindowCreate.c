static void
FillCursorData(LPWINCREATESTRUCT lpwcs,HCURSOR hCursor)
{
    LPCURSORINFO lpCursorInfo;

    if (!hCursor) 
	hCursor = LoadCursor(0,IDC_ARROW);

    if ((lpCursorInfo = GETCURSORINFO(hCursor)))
    {
	lpwcs->Cursor = lpCursorInfo->lpCurData;
	RELEASECURSORINFO(lpCursorInfo);
    }
    else
	lpwcs->Cursor = NULL;
}