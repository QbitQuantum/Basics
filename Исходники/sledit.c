static int
edtProcessKeyDown(
	HWND hWnd,
	WPARAM wParam,
	LPARAM lParam
)
{
	PWindowsTree pWin;
	PSLEditData pEditData;
	BOOL bChange, bScroll;
	int iNewStartPos;
	int scrollStep,moveStep,deleted;
	int iLimit;
	RECT InvRect;
		
	pWin = (PWindowsTree)hWnd;
	if(!pWin)
		return -1;

	pEditData = (PSLEditData)(pWin->dwData);
	if(!pEditData)
		return -1;
	bChange = false;
	switch(LOWORD(wParam)){
	case SCANCODE_ENTER:
		NotifyParent (hWnd, EN_ENTER);
		break;
	case SCANCODE_HOME:
		if (pEditData->iEditPos == 0)
			break;
		pEditData->iEditPos  = 0;
		pEditData->iCaretPos = 0;
		
		SetCaretPos (hWnd,
			pEditData->iCaretPos * GetSysCharWidth ()
			+ pEditData->iLeftMargin,
			pEditData->iTopMargin);
			
		if (pEditData->iStartPos != 0)
			InvalidateRect (hWnd, NULL, TRUE);
		
		pEditData->iStartPos = 0;
		break;
	case SCANCODE_END:
		if (pEditData->iEditPos == pEditData->iDataLen)
			return 0;
		
		iNewStartPos = GetStartPos (hWnd, pEditData);
		
		pEditData->iEditPos = pEditData->iDataLen;
		pEditData->iCaretPos = pEditData->iEditPos - iNewStartPos;
		
		SetCaretPos (hWnd,
			pEditData->iCaretPos * GetSysCharWidth ()
			+ pEditData->iLeftMargin,
			pEditData->iTopMargin);
		
		if (pEditData->iStartPos != iNewStartPos)
			InvalidateRect (hWnd, NULL, TRUE);
		
		pEditData->iStartPos = iNewStartPos;
		break;	
	case SCANCODE_LEFT:
		//
		bScroll = FALSE;
		if (pEditData->iEditPos == 0)
			return 0;
		
		if (IsACCharBeforePos (pEditData->buffer, pEditData->iEditPos)) {
			scrollStep = 2;
			pEditData->iEditPos -= 2;
		}
		else {
			scrollStep = 1;
			pEditData->iEditPos --;
		}
		
		pEditData->iCaretPos -= scrollStep;
		if (pEditData->iCaretPos == 0 && pEditData->iEditPos != 0) {
			bScroll = TRUE;
			if (IsACCharBeforePos(pEditData->buffer,
				pEditData->iEditPos)) {
				pEditData->iStartPos -= 2;
				pEditData->iCaretPos = 2;
			}
			else{
				pEditData->iStartPos --;
				pEditData->iCaretPos = 1;
			}
		}
		else if (pEditData->iCaretPos < 0) {
			pEditData->iStartPos = 0;
			pEditData->iCaretPos = 0;
		}
		
		SetCaretPos (hWnd,
			pEditData->iCaretPos * GetSysCharWidth ()
			+ pEditData->iLeftMargin,
			pEditData->iTopMargin);
		
		if (bScroll)
			InvalidateRect (hWnd, NULL, TRUE);
		break;	
	case SCANCODE_RIGHT:
		bScroll = FALSE;
		if (pEditData->iEditPos == pEditData->iDataLen)
			return 0;
		
		if (IsACCharAtPos (pEditData->buffer,
				pEditData->iDataLen,
				pEditData->iStartPos)) {
			if (IsACCharAtPos (pEditData->buffer,
					pEditData->iDataLen,
					pEditData->iEditPos)) {
				scrollStep = 2;
				moveStep = 2;
				pEditData->iEditPos  += 2;
			}
			else {
				scrollStep = 2;
				moveStep = 1;
				pEditData->iEditPos ++;
			}
		}
		else {// isn't a chinese character at start position
			if (IsACCharAtPos (pEditData->buffer,
					pEditData->iDataLen,
					pEditData->iEditPos)) {
			
				if (IsACCharAtPos (pEditData->buffer,
						pEditData->iDataLen,
						pEditData->iStartPos + 1))
					scrollStep = 3;
				else
					scrollStep = 2;
				
				moveStep = 2;
				pEditData->iEditPos += 2;
			}
			else {
				scrollStep = 1;
				moveStep = 1;
				pEditData->iEditPos ++;
			}
		}
		iLimit = pWin->rect.right - pWin->rect.left + 1 - 2 * wndGetBorder(hWnd) 
			 - pEditData->iLeftMargin - pEditData->iRightMargin;

		pEditData->iCaretPos += moveStep;
		if (pEditData->iCaretPos * GetSysCharWidth () > iLimit) {
			bScroll = TRUE;
			pEditData->iStartPos += scrollStep;
			
			pEditData->iCaretPos =
					pEditData->iEditPos - pEditData->iStartPos;
		}
		SetCaretPos (hWnd,
				pEditData->iCaretPos * GetSysCharWidth ()
				+ pEditData->iLeftMargin,
				pEditData->iTopMargin);
		
		if (bScroll)
			InvalidateRect (hWnd, NULL, TRUE);
		break;				
	case SCANCODE_INS:
		pEditData = (PSLEditData) (pWin->dwData);
		pEditData->dwStatus ^= EST_REPLACE;
		break;
	case SCANCODE_DEL:
	{
		int i;
		pEditData = (PSLEditData) (pWin->dwData);
		if ((pWin->dwStyle & ES_READONLY)
				|| (pEditData->iEditPos == pEditData->iDataLen)){
			return 0;
		}
		
		if (IsACCharAtPos (pEditData->buffer,
				pEditData->iDataLen,
				pEditData->iEditPos))
			deleted = 2;
		else
			deleted = 1;
	
		for(i=pEditData->iEditPos; i<pEditData->iDataLen; i++)
			pEditData->buffer[i] = pEditData->buffer[i+deleted];	
		//for (i = pEditData->iEditPos;
		//		i < pEditData->iDataLen - deleted; i++)
		//	pEditData->buffer [i] = pEditData->buffer [i + deleted];
		
		pEditData->iDataLen -= deleted;
		bChange = TRUE;
		
		InvRect.left = pEditData->iLeftMargin
				+ pEditData->iCaretPos * GetSysCharWidth ();
		InvRect.top = pEditData->iTopMargin;
		InvRect.right = pWin->rect.right - pWin->rect.left;
		InvRect.bottom = pWin->rect.bottom - pWin->rect.top;
		
		InvalidateRect (hWnd, &InvRect, TRUE);
		break;
	}	
	case SCANCODE_BACKSPACE:
	{
		int i;
		pEditData = (PSLEditData) (pWin->dwData);
		if ((pEditData->dwStatus & ES_READONLY) || (pEditData->iEditPos == 0)) {
			return 0;
		}
		
		if (IsACCharBeforePos (pEditData->buffer, pEditData->iEditPos))
			deleted = 2;
		else
			deleted = 1;
		
		for (i = pEditData->iEditPos - deleted; i < pEditData->iDataLen; i++)
			pEditData->buffer [i] = pEditData->buffer [i + deleted];
		
		pEditData->iDataLen -= deleted;
		pEditData->iEditPos -= deleted;
		bChange = TRUE;
		
		pEditData->iCaretPos -= deleted;
		if (pEditData->iCaretPos == 0 && pEditData->iEditPos != 0) {
			if (IsACCharBeforePos (pEditData->buffer, 
					pEditData->iEditPos)) {
				pEditData->iStartPos -= 2;
				pEditData->iCaretPos = 2;
			}
			else {
				pEditData->iStartPos --;
				pEditData->iCaretPos = 1;
			}
		
			InvRect.left = pEditData->iLeftMargin;
			InvRect.top = pEditData->iTopMargin;
			InvRect.right = pWin->rect.right - pWin->rect.left;
			InvRect.bottom = pWin->rect.bottom - pWin->rect.top;
		}
		else {
			InvRect.left = pEditData->iLeftMargin
					+ pEditData->iCaretPos * GetSysCharWidth ();
			InvRect.top = pEditData->iTopMargin;
			InvRect.right = pWin->rect.right - pWin->rect.left;
			InvRect.bottom = pWin->rect.bottom - pWin->rect.top;
		}
		
		SetCaretPos (hWnd,
				pEditData->iCaretPos * GetSysCharWidth ()
				+ pEditData->iLeftMargin,
				pEditData->iTopMargin);
				
		InvalidateRect (hWnd, &InvRect, TRUE);
		break;
	}
	}
	if (bChange)
		NotifyParent (hWnd, EN_CHANGE);
	return 0;
}