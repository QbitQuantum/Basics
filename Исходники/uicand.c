void MoveCandWindow(HWND hUIWnd,LPUIEXTRA lpUIExtra, LPINPUTCONTEXT lpIMC)
{
	if (!IsWindow(lpUIExtra->uiCand.hWnd))
		CreateCandWindow( hUIWnd, lpUIExtra);

	if (IsWindow(lpUIExtra->uiCand.hWnd))
	{
	    LPCANDIDATEINFO lpCandInfo;
	    LPCANDIDATELIST lpCandList;
		HDC hDC;
		HFONT oldFont;
		SIZE sz;
		LPTSTR lpStr;

		sz.cx = 0;
		sz.cy = 0;

		if (lpCandInfo = (LPCANDIDATEINFO)ImmLockIMCC(lpIMC->hCandInfo))
		{
			lpCandList = (LPCANDIDATELIST)((LPSTR)lpCandInfo  + lpCandInfo->dwOffset[0]);
			if( lpCandList->dwCount <= 0) {
				ShowWindow(lpUIExtra->uiCand.hWnd, SW_HIDE);
				ImmUnlockIMCC(lpIMC->hCandInfo);
				return;
			}
			lpStr = GETLPCANDSTR(lpCandList,1);
			hDC = GetDC(lpUIExtra->uiCand.hWnd);
			oldFont = SelectObject(hDC, hUIFont);
			GetTextExtentPoint(hDC,lpStr,_tcslen(lpStr),&sz);
			SelectObject(hDC, oldFont);
			ReleaseDC(lpUIExtra->uiCand.hWnd,hDC);
			if(_tcslen(lpStr))	sz.cx += 3*sz.cx/_tcslen(lpStr);
			ImmUnlockIMCC(lpIMC->hCandInfo);
		}
		if(wConversionSet & CONVERSION_SET_SHAPE) {	
			sz.cx = sizeCand[1].cx;
			sz.cy = sizeCand[1].cy;
		}
		else{
			if(sz.cx < lpUIExtra->uiCand.sz.cx)
					sz.cx = lpUIExtra->uiCand.sz.cx;
			sz.cy = lpUIExtra->uiCand.sz.cy;
		}

		GetCandPosFromCompWnd(lpUIExtra,&sz);

		MoveWindow(lpUIExtra->uiCand.hWnd,
			lpUIExtra->uiCand.pt.x,
			lpUIExtra->uiCand.pt.y,
			sz.cx,
			sz.cy,
			TRUE);
		ShowWindow(lpUIExtra->uiCand.hWnd,SW_SHOWNOACTIVATE);
		InvalidateRect(lpUIExtra->uiCand.hWnd,NULL,FALSE);
	}
}