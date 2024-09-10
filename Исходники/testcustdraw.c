//
//	function for drawing the custom-draw inserted buttons
//	Called from the WM_NOTIFY handler (HandleCustomDraw)
//
UINT CALLBACK CoolSB_DrawProc(HDC hdc, UINT uCmdId, UINT uButflags, RECT *rect)
{
	RECT rc;
	POINT pt;
	HPEN hpen, hold;

	HBITMAP hbm, oldbm;
	HDC hdcmem;

	if(hemf == 0)
		InitMetaFile();

	SetRect(&rc, 0, 0, 120, rect->bottom-rect->top);

	hdcmem = CreateCompatibleDC(hdc);
	hbm = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	oldbm = SelectObject(hdcmem, hbm);

	SetWindowOrgEx(hdc, -rect->left, -rect->top, &pt);
	PlayEnhMetaFile(hdcmem, hemf, &rc);
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcmem, 0, 0, SRCCOPY);
	
	SetRect(&rc, 120, 0, rect->right-rect->left, rect->bottom-rect->top);
	FillRect(hdc, &rc, GetSysColorBrush(COLOR_3DFACE));
	
	hpen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DSHADOW));
	hold = SelectObject(hdc, hpen);
	MoveToEx(hdc, 120, 0, 0);
	LineTo(hdc, rect->right-rect->left, 0);
	
	SetWindowOrgEx(hdc, pt.x, pt.y, 0);		

	
	SelectObject(hdc, hold);
	SelectObject(hdcmem, oldbm);
	DeleteObject(hbm);
	DeleteDC(hdcmem);
	DeleteObject(hpen);
	
	UNREFERENCED_PARAMETER(uButflags);
	UNREFERENCED_PARAMETER(uCmdId);
	return 0;
}