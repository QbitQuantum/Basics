/****************************************************************************
 *                                                                          *
 * Function: HypCtrlWndProc                                                 *
 *                                                                          *
 * Purpose : Process Hyperlink control messages.                            *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/
static LRESULT CALLBACK HypCtrlWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg){
		case WM_LBUTTONUP: {
			HYPCTRL* pHcWnd = (HYPCTRL*) GetWindowLong(hWnd, WND_HYPSTRUCT);

			if (pHcWnd->bPlaySound) PlayNavigatingSound();
		
			if (pHcWnd->cbFn != NULL) {
				// call user function (callback)
				pHcWnd->cbFn(pHcWnd->cbID);
			} else {
				// jump to link
				ShellExecute(NULL, _T("open"), pHcWnd->szLink, NULL, NULL, SW_SHOW);
			}
			return FALSE;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc;
			RECT rect;

			HYPCTRL* pHcWnd     = (HYPCTRL*) GetWindowLong(hWnd, WND_HYPSTRUCT);
			BOOL bIsOverControl = (BOOL) GetWindowWord(hWnd, WND_ISHOVER);

			rect.left	= (LONG) GetWindowLong(hWnd, WND_LEFT);
			rect.top	= (LONG) GetWindowLong(hWnd, WND_TOP);
			rect.right	= (LONG) GetWindowLong(hWnd, WND_RIGHT);
			rect.bottom	= (LONG) GetWindowLong(hWnd, WND_BOTTOM);

			hdc = BeginPaint(hWnd, &ps);

			if (bIsOverControl) {
				// draws hover state
     		    SetBkColor(hdc, (COLORREF) pHcWnd->bgcHover);
				SelectObject(hdc, (HFONT) GetWindowLong(hWnd, WND_FONTH));
				SetTextColor(hdc, pHcWnd->fgcHover);
			} else {
				// draws normal state
       		    SetBkColor(hdc, (COLORREF) pHcWnd->bgcNormal);
				SelectObject(hdc, (HFONT) GetWindowLong(hWnd, WND_FONTN));
				SetTextColor(hdc, pHcWnd->fgcNormal);
			}
			// draw the text
			DrawText(hdc, pHcWnd->szText, -1, &rect, pHcWnd->dtStyle);
            
			EndPaint(hWnd, &ps);
			return FALSE;
		}
		case WM_CAPTURECHANGED:
			SetWindowWord(hWnd, WND_ISHOVER, (WORD) FALSE);
			InvalidateRect(hWnd, NULL, TRUE);
			return FALSE;
		case WM_MOUSEMOVE: {
			RECT rect;

			rect.left	= (LONG) GetWindowLong(hWnd, WND_LEFT);
			rect.top	= (LONG) GetWindowLong(hWnd, WND_TOP);
			rect.right	= (LONG) GetWindowLong(hWnd, WND_RIGHT);
			rect.bottom	= (LONG) GetWindowLong(hWnd, WND_BOTTOM);
			
			// check if mouse is over control
			if ((BOOL) GetWindowWord(hWnd, WND_ISHOVER)) {
				POINT ptMousePos;
				DWORD dwMousePos;

				dwMousePos = GetMessagePos();

				ptMousePos.x = LOWORD(dwMousePos);
				ptMousePos.y = HIWORD(dwMousePos);

				ScreenToClient(hWnd, &ptMousePos);

				if (!(BOOL) PtInRect(&rect, ptMousePos)) {
					SetWindowWord(hWnd, WND_ISHOVER, (WORD) FALSE);
					InvalidateRect(hWnd, &rect, TRUE);
				   	ReleaseCapture();
				}
			} else {
				SetWindowWord(hWnd, WND_ISHOVER, (WORD) TRUE);
				InvalidateRect(hWnd, &rect, TRUE);
				SetCapture(hWnd);
			}
			return FALSE;
		}
		case WM_CLOSE: {
			HYPCTRL* pHcWnd = (HYPCTRL*) GetWindowLong(hWnd, WND_HYPSTRUCT);
			HFONT hFontTemp;

			// clean up
			if (pHcWnd->szLink) GlobalFreePtr(pHcWnd->szLink);
			if (pHcWnd->szText) GlobalFreePtr(pHcWnd->szText);
			if (pHcWnd->szTooltip) GlobalFreePtr(pHcWnd->szTooltip);
			if (pHcWnd->cbFn) GlobalFreePtr(pHcWnd->cbFn);
			
			hFontTemp = (HFONT) GetWindowLong(hWnd, WND_FONTN);
			if (hFontTemp) DeleteObject(hFontTemp);

			hFontTemp = (HFONT) GetWindowLong(hWnd, WND_FONTH);
			if (hFontTemp) DeleteObject(hFontTemp);

			if (pHcWnd) GlobalFreePtr(pHcWnd);
			DestroyWindow(hWnd);
			return FALSE;
		}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}