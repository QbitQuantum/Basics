LONG NotifyHandle(HIMC hUICurIMC, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LONG lRet = 0L;
    LPINPUTCONTEXT lpIMC;
    HGLOBAL hUIExtra;
    LPUIEXTRA lpUIExtra;

    if (!(lpIMC = ImmLockIMC(hUICurIMC)))
        return 0L;

    hUIExtra = (HGLOBAL)GetWindowLong(hWnd,IMMGWL_PRIVATE);
    lpUIExtra = (LPUIEXTRA)GlobalLock(hUIExtra);

    switch (wParam)
    {
	case IMN_CLOSESTATUSWINDOW:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_CLOSESTATUSWINDOW\n"));
		if (IsWindow(lpUIExtra->uiStatus.hWnd)) {
			ShowWindow(lpUIExtra->uiStatus.hWnd,SW_HIDE);
		}
		break;
		
	case IMN_OPENSTATUSWINDOW:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_OPENSTATUSWINDOW\n"));
		CreateStatusWindow( hWnd, lpUIExtra);
		break;
		
	case IMN_OPENCANDIDATE:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_OPENCANDIDATE\n"));
		break;
		
	case IMN_CHANGECANDIDATE:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_CHANGECANDIDATE\n"));
		break;
		
	case IMN_CLOSECANDIDATE:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_CLOSECANDIDATE\n"));
		break;
		
	case IMN_SETCONVERSIONMODE:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_SETCONVERSIONMODE\n"));
		UpdateStatusWindow(lpUIExtra);
		break;
		
	case IMN_SETSENTENCEMODE:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_SETSENTENCEMODE\n"));
		break;
		
	case IMN_SETOPENSTATUS:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_SETOPENSTATUS\n"));
		if(!IsIMEOpen(hUICurIMC)) {
			MakeResultString(hUICurIMC,FALSE);
		}
		UpdateStatusWindow(lpUIExtra);
		break;
		
	case IMN_SETCANDIDATEPOS:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_SETCANDIDATEPOS\n"));
		break;
		
	case IMN_SETCOMPOSITIONFONT:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_SETCOMPOSITIONFONT\n"));
		break;
		
	case IMN_SETCOMPOSITIONWINDOW:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_SETCOMPOSITIONWINDOW\n"));
		if(wConversionSet & CONVERSION_SET_FOLLOW) {
			POINT ptSrc;
			SIZE szOffset;
			HDC hDC;
			HFONT oldFont;

			ptSrc = lpIMC->cfCompForm.ptCurrentPos;
			ClientToScreen(lpIMC->hWnd, &ptSrc);
			hDC = GetDC(lpIMC->hWnd);
			oldFont = SelectObject(hDC, hUIFont);
			GetTextExtentPoint(hDC,"A",1,&szOffset);
			SelectObject(hDC, oldFont);
			ReleaseDC(lpIMC->hWnd,hDC);

			lpUIExtra->uiComp.pt.x = ptSrc.x + szOffset.cx;
			lpUIExtra->uiComp.pt.y = ptSrc.y + szOffset.cy;
		}
	    if (IsWindow(lpUIExtra->uiComp.hWnd))
			InvalidateRect(lpUIExtra->uiComp.hWnd,NULL,FALSE);

		break;
		
	case IMN_GUIDELINE:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_GUIDELINE\n"));
		break;
		
	case IMN_SETSTATUSWINDOWPOS:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_SETSTATUSWINDOWPOS\n"));
		break;
		
	case IMN_PRIVATE:
		DebugLog(1,(DebugLogFile,"UIWnd:WM_IME_NOTIFY:IMN_PRIVATE\n"));
		break;
		
	default:
		break;
    }
    GlobalUnlock(hUIExtra);
    ImmUnlockIMC(hUICurIMC);

    return lRet;
}