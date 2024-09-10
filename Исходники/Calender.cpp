HBITMAP GetCalendarBackGnd(HWND hwndDlg,HDC hDC,COLORREF clrDrawingColor)
{
	RECT CurrentPos;HBRUSH hBrush; HPEN hPen;TOOLINFO ti;

	HDC hMemDC;
	HBITMAP hMemBitMap,hOldBitmap;	
	int Width,Height,Top,Left,iRatioX,iRatioY;
	
	ti.cbSize=sizeof(ti);
	ti.uFlags = TTF_TRANSPARENT | TTF_SUBCLASS;
	ti.hwnd = hwndDlg;
	
	GetClientRect(hwndDlg,&CurrentPos);
	Left=CurrentPos.left;
	Top=CurrentPos.top;
	Width=CurrentPos.right-CurrentPos.left+1;
	Height=CurrentPos.bottom-CurrentPos.top+1;

	hMemDC = CreateCompatibleDC(hDC);	
	hMemBitMap= CreateCompatibleBitmap(hDC, Width, Height);
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hMemBitMap);
	
	iRatioX=Width/50;
	iRatioY=Height/50;

	//clear all
	hBrush=CreateSolidBrush(clrDrawingColor);
	FillRect(hMemDC,&CurrentPos,hBrush);
	DeleteObject(hBrush);
	
	//draw gradiant backgnd
	for (int i=0;i<=25;i++)
	{
		hBrush=CreateSolidBrush(ColorAdjustLuma(clrDrawingColor,i*10));
		SelectObject(hMemDC,hBrush); 
		hPen=CreatePen(PS_SOLID,1,ColorAdjustLuma(clrDrawingColor,i*10));
		SelectObject(hMemDC,hPen);
		RoundRect(hMemDC,iRatioX*i ,iRatioY*i ,Width-iRatioX*i,Height-iRatioY*i,25,25);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}

	POINT pPoint;

	rDateRects[31].top=3;
	rDateRects[31].bottom=18;
	rDateRects[31].left=Width-30;
	rDateRects[31].right=Width-10;
	//add a tooltip
	ti.uId = 0;
	ti.lpszText = TEXT("Close");
	ti.rect = rDateRects[31];
	SendMessage(hToolTipWindow, TTM_ADDTOOL, 0, (LPARAM)&ti);
	
	pPoint.x=long(rDateRects[31].left+(rDateRects[31].right-rDateRects[31].left)/2);
	pPoint.y=long(rDateRects[31].top+(rDateRects[31].bottom-rDateRects[31].top)/2);	
	DrawText(hMemDC,TEXT("X"),pPoint,clrCalendarDate/3,1.3);

	rDateRects[32].top=2;
	rDateRects[32].bottom=20;
	rDateRects[32].left=Width/2-40;
	rDateRects[32].right=Width/2+40;
	//add a tooltip
	ti.uId = 1;
	ti.lpszText = TEXT("Change Current Calendar Year");
	ti.rect = rDateRects[32];
	SendMessage(hToolTipWindow, TTM_ADDTOOL, 0, (LPARAM)&ti);
	
	SelectObject(hMemDC,hOldBitmap);
	DeleteDC(hMemDC);

	return hMemBitMap; 
}