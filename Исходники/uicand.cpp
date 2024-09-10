void PaintCandWindow( HWND hCandWnd)
{
	PAINTSTRUCT ps;
	HIMC hIMC = NULL;
	LPINPUTCONTEXT lpIMC = NULL;
	LPCANDIDATEINFO lpCandInfo = NULL;
	LPCANDIDATELIST lpCandList = NULL;
	HDC hDC = NULL;
	HFONT oldFont = NULL;
	RECT rc;
	LPTSTR lpstr = NULL;
	TCHAR szStr[100];
	int height,width;
	DWORD i;
	SIZE sz;
	HWND hSvrWnd = NULL;
	HBRUSH hBrush = NULL, hOldBrush = NULL;	
	HPEN hPen = NULL, hOldPen = NULL;	 

	hDC = BeginPaint(hCandWnd,&ps);
	oldFont = (HFONT)SelectObject(hDC, hUIFont);

	GetClientRect(hCandWnd,&rc);
	hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(hDC,hBrush);
	PatBlt(hDC,	rc.left, rc.top ,	rc.right, rc.bottom, PATCOPY);
	if(hBrush && hOldBrush)
	{
		SelectObject(hDC,hOldBrush);
	}

	hPen = (HPEN)GetStockObject(WHITE_PEN);
	hOldPen = (HPEN)SelectObject(hDC,hPen);
	MoveToEx(hDC,0,rc.bottom - GetSystemMetrics(SM_CXEDGE)/2,NULL);
	LineTo(hDC,rc.right-GetSystemMetrics(SM_CXEDGE)/2,rc.bottom - GetSystemMetrics(SM_CXEDGE)/2);
	LineTo(hDC,rc.right-GetSystemMetrics(SM_CXEDGE)/2,0);

	hPen = CreatePen(PS_SOLID ,0,RGB(128,128,128));
	SelectObject(hDC,hPen);
	MoveToEx(hDC,rc.right-GetSystemMetrics(SM_CXEDGE)/2,0,NULL);
	LineTo(hDC,0,0);
	LineTo(hDC,0,rc.bottom-GetSystemMetrics(SM_CYEDGE)/2);

	SelectObject(hDC,hOldPen);
	DeleteObject(hPen);

	hSvrWnd = (HWND)GetWindowLong(hCandWnd,FIGWL_SVRWND);

	if (hIMC = (HIMC)GetWindowLong(hSvrWnd,IMMGWL_IMC))
	{
		lpIMC = ImmLockIMC(hIMC);
		if (lpCandInfo = (LPCANDIDATEINFO)ImmLockIMCC(lpIMC->hCandInfo))
		{
			DWORD dwMaxPaintPos;
			WORD  wCount;

			height = 3;
			width = 1;
			lpCandList = (LPCANDIDATELIST)((LPTSTR)lpCandInfo  + lpCandInfo->dwOffset[0]);
			SetBkMode(hDC, TRANSPARENT);
			SetPaintColor(hDC, wConversionMode);

			if(wConversionSet & CONVERSION_SET_SHAPE) 
			{
				lpstr = GETLPCANDSTR(lpCandList, 0);
				TextOut(hDC, width, height, lpstr, _tcslen(lpstr));
				GetTextExtentPoint(hDC, lpstr, _tcslen(lpstr), &sz);
				width += sz.cx * 3 / 2;
			}

			dwMaxPaintPos = lpCandList->dwPageStart +lpCandList->dwPageSize ;
			if(dwMaxPaintPos > lpCandList->dwCount + 2)  
				dwMaxPaintPos = lpCandList->dwCount + 2;

			wCount = 0;
			for (i = lpCandList->dwPageStart; i < dwMaxPaintPos; i++)
			{
				wCount++;
				lpstr = GETLPCANDSTR(lpCandList,i);
				GetTextExtentPoint(hDC,lpstr, _tcslen(lpstr), &sz);
				if(wConversionSet & CONVERSION_SET_SHAPE) 
				{
					_stprintf(szStr, TEXT("%d%s "), wCount % 10, lpstr);
					TextOut(hDC,width,height,szStr,_tcslen(szStr));
					GetTextExtentPoint(hDC,szStr,_tcslen(szStr),&sz);
					width += sz.cx;
				}
				else 
				{
					_stprintf(szStr,TEXT("%d %s "), wCount%10,lpstr);
					TextOut(hDC,width,height,szStr,_tcslen(szStr));
					GetTextExtentPoint(hDC,szStr,_tcslen(szStr),&sz);
					height += sz.cy;
				}
			}
			if(wConversionSet & CONVERSION_SET_SHAPE) 
			{
				lpstr = GETLPCANDSTR(lpCandList, 1);
				if(_tcslen(lpstr)) 
				{
					GetTextExtentPoint(hDC, TEXT("A"), 1, &sz);
					width = sizeCand[1].cx - sz.cx * 3 / 2;
					TextOut(hDC, width, height, lpstr, _tcslen(lpstr));
				}
			}

			ImmUnlockIMCC(lpIMC->hCandInfo);
		}
		ImmUnlockIMC(hIMC);
	}
	SelectObject(hDC, oldFont);
	EndPaint(hCandWnd, &ps);
}