static LRESULT CALLBACK TollbarButtonProc(HWND hwndDlg, UINT  msg, WPARAM wParam, LPARAM lParam)
{
	TBBUTTONDATA *lpSBData = (TBBUTTONDATA *) GetWindowLongPtr(hwndDlg, 0);
	switch (msg) 
	{
	case WM_NCCREATE:
		{
			SetWindowLong(hwndDlg, GWL_STYLE, GetWindowLong(hwndDlg, GWL_STYLE) | BS_OWNERDRAW);
			lpSBData = (TBBUTTONDATA *)malloc(sizeof(TBBUTTONDATA));
			if (lpSBData == NULL)
				return FALSE;
			memset(lpSBData,0,sizeof(TBBUTTONDATA)); //I prefer memset to guarantee zeros
			lpSBData->hWnd = hwndDlg;
			lpSBData->nStateId = PBS_NORMAL;
			lpSBData->fFocused = FALSE;
			lpSBData->hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
			lpSBData->hIconPrivate = NULL;
			lpSBData->cHot = '\0';
			lpSBData->szText[0] = '\0';
			lpSBData->szButtonID[0] = '?';
			lpSBData->szButtonID[1] = '\0';
			lpSBData->pushBtn = FALSE;
			lpSBData->pbState = 0;
			lpSBData->fSendOnDown = FALSE;
			lpSBData->fHotMark = FALSE;
			lpSBData->nFontID = -1;
			SetWindowLongPtr(hwndDlg, 0, (LONG_PTR) lpSBData);
			if (((CREATESTRUCTA *) lParam)->lpszName)
				SetWindowText(hwndDlg, ((CREATESTRUCT *) lParam)->lpszName);
			lpSBData->hThemeButton = xpt_AddThemeHandle(lpSBData->hWnd, L"BUTTON");
			lpSBData->hThemeToolbar = xpt_AddThemeHandle(lpSBData->hWnd, L"TOOLBAR");
			WindowList_Add(hButtonWindowList, hwndDlg, NULL);				
			return TRUE;
		}
	case WM_DESTROY:
		{
			/* #ifdef _DEBUG
			if (GetWindowLong(hwndButton, GWL_USERDATA))
			DebugBreak();
			#endif */

			xpt_FreeThemeForWindow(hwndDlg);
			WindowList_Remove(hButtonWindowList, hwndDlg);
			if (lpSBData) 
			{
				if (hwndToolTips) 
				{
					TOOLINFO ti;

					ZeroMemory(&ti, sizeof(ti));
					ti.cbSize = sizeof(ti);
					ti.uFlags = TTF_IDISHWND;
					ti.hwnd = lpSBData->hWnd;
					ti.uId = (UINT_PTR) lpSBData->hWnd;
					if (SendMessage(hwndToolTips, TTM_GETTOOLINFO, 0, (LPARAM) &ti)) 
					{
						SendMessage(hwndToolTips, TTM_DELTOOL, 0, (LPARAM) &ti);
					}
					if (SendMessage(hwndToolTips, TTM_GETTOOLCOUNT, 0, (LPARAM) &ti) == 0) 
					{
						DestroyWindow(hwndToolTips);
						hwndToolTips = NULL;
					}
				}
				if (lpSBData->hIconPrivate)
					DestroyIcon(lpSBData->hIconPrivate);
				free(lpSBData);  // lpSBData was malloced by native malloc
			}
			SetWindowLong(hwndDlg, 0, (LONG) NULL);
			break;  // DONT! fall thru
		}
	case WM_SETTEXT:
		{
			lpSBData->cHot = 0;
			if ((TCHAR*) lParam) 
			{
				TCHAR *tmp = (TCHAR *) lParam;
				while (*tmp) 
				{
					if (*tmp == '&' && *(tmp + 1)) 
					{
						lpSBData->cHot = (char)tolower(*(tmp + 1));
						break;
					}
					tmp++;
				}
				InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
				lstrcpyn(lpSBData->szText, (TCHAR *)lParam, SIZEOF(lpSBData->szText)-1);
				lpSBData->szText[SIZEOF(lpSBData->szText)-1] = '\0';
			}
			break;
		}
	case WM_SYSKEYUP:
		if (lpSBData->nStateId != PBS_DISABLED && lpSBData->cHot && lpSBData->cHot == tolower((int) wParam)) 
		{
			if (lpSBData->pushBtn) 
			{
				if (lpSBData->pbState)
					lpSBData->pbState = 0;
				else
					lpSBData->pbState = 1;
				InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
			}
			if(!lpSBData->fSendOnDown)
				SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKELONG(GetDlgCtrlID(hwndDlg), BN_CLICKED), (LPARAM) hwndDlg);
			return 0;
		}
		break;

	case WM_SETFONT:			
		{	
			// remember the font so we can use it later
			lpSBData->hFont = (HFONT) wParam; // maybe we should redraw?
			lpSBData->nFontID = (int) lParam - 1;
			break;
		}
	case BUTTONSETSENDONDOWN:
		{
			lpSBData->fSendOnDown = (BOOL) lParam;
			break;
		}
	case BUTTONSETMARGINS:
		{
			if (lParam)	lpSBData->rcMargins=*(RECT*)lParam;
			else 
			{
				RECT nillRect={0};
				lpSBData->rcMargins=nillRect;
			}
			return 0;
		}
	case BUTTONSETID:
		{
			lstrcpynA(lpSBData->szButtonID, (char *)lParam, SIZEOF(lpSBData->szButtonID)-1);
			lpSBData->szButtonID[SIZEOF(lpSBData->szButtonID)-1] = '\0';
			return 0;
		}
	case BUTTONDRAWINPARENT:
		{
			if (IsWindowVisible(hwndDlg))
				PaintWorker(lpSBData, (HDC) wParam, (POINT*) lParam);
			return 0;
		}
	case WM_NCPAINT:
	case WM_PAINT:
		{

			PAINTSTRUCT ps;
			HDC hdcPaint;
			if (g_CluiData.fDisableSkinEngine)
			{
				hdcPaint = BeginPaint(hwndDlg, &ps);
				if (hdcPaint) 
				{
					PaintWorker(lpSBData, hdcPaint, NULL);
					EndPaint(hwndDlg, &ps);
				}
			}
			ValidateRect(hwndDlg,NULL);
			return 0;
		}
	case BUTTONADDTOOLTIP:
		{
			TOOLINFO ti;

			if (!(char*) wParam)
				break;
			if (!hwndToolTips) 
			{
				hwndToolTips = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, _T(""), WS_POPUP, 0, 0, 0, 0, NULL, NULL, GetModuleHandle(NULL), NULL);
				SetWindowPos(hwndToolTips, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			}
			ZeroMemory(&ti, sizeof(ti));
			ti.cbSize = sizeof(ti);
			ti.uFlags = TTF_IDISHWND;
			ti.hwnd = lpSBData->hWnd;
			ti.uId = (UINT_PTR) lpSBData->hWnd;
			if (SendMessage(hwndToolTips, TTM_GETTOOLINFO, 0, (LPARAM) &ti)) {
				SendMessage(hwndToolTips, TTM_DELTOOL, 0, (LPARAM) &ti);
			}
			ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
			ti.uId = (UINT_PTR) lpSBData->hWnd;
			ti.lpszText = (TCHAR *) wParam;
			SendMessage(hwndToolTips, TTM_ADDTOOL, 0, (LPARAM) &ti);
			break;
		}
	case BUTTONSETASPUSHBTN:
		{

			if (lParam==0)
				lpSBData->pushBtn=1;
			else
			{
				lpSBData->pushBtn=wParam;
				lpSBData->pbState = (lParam&2) ? TRUE : FALSE;
			}
			return 0;
		}
	case WM_SETFOCUS:
		{
			// set keyboard focus and redraw
			lpSBData->fFocused = TRUE;
			InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
			break;
		}
	case WM_KILLFOCUS:
		{
			// kill focus and redraw
			lpSBData->fFocused = FALSE;
			InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
			break;
		}
	case WM_WINDOWPOSCHANGED:
		InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
		break;
	case WM_ENABLE:
		// windows tells us to enable/disable
		{
			lpSBData->nStateId = wParam ? PBS_NORMAL : PBS_DISABLED;
			InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
			break;
		}
	/*case WM_MOUSELEAVE:			
		{
			// faked by the WM_TIMER
			if (lpSBData->nStateId != PBS_DISABLED) 
			{
				// don't change states if disabled
				lpSBData->nStateId = PBS_NORMAL;
				InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
			}
			break;
		}
		*/
	case WM_CAPTURECHANGED:
		{                
			if ( (HWND)lParam != lpSBData->hWnd && lpSBData->nStateId != PBS_DISABLED) 
			{
				// don't change states if disabled
				lpSBData->nStateId = PBS_NORMAL;
				InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
			}
			break;
		}
	case WM_LBUTTONDOWN:
		{
			int xPos=( ( int )( short ) LOWORD( lParam ) );
			int yPos=( ( int )( short ) HIWORD( lParam ) );
			POINT ptMouse = { xPos, yPos };

			RECT rcClient;
			GetClientRect( lpSBData->hWnd, &rcClient );

			if ( !PtInRect( &rcClient, ptMouse ) )
			{
				lpSBData->fHotMark = FALSE;
				ReleaseCapture();
				break;
			}

			if (lpSBData->nStateId != PBS_DISABLED && lpSBData->nStateId != PBS_PRESSED) 
			{
				lpSBData->nStateId = PBS_PRESSED;
				lpSBData->fHotMark = TRUE;
				InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
				if(lpSBData->fSendOnDown) 
				{
					SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKELONG(GetDlgCtrlID(hwndDlg), BN_CLICKED), (LPARAM) hwndDlg);
					lpSBData->nStateId = PBS_NORMAL;
					InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
				}
			}
			SetCapture( lpSBData->hWnd );
			break;
		}
	case WM_LBUTTONUP:
		if ( GetCapture() == lpSBData->hWnd )
		{

			int xPos=( ( int )( short ) LOWORD( lParam ) );
			int yPos=( ( int )( short ) HIWORD( lParam ) );
			POINT ptMouse = { xPos, yPos };

			RECT rcClient;
			GetClientRect( lpSBData->hWnd, &rcClient );
			
			if ( !PtInRect( &rcClient, ptMouse ) )
			{
				lpSBData->fHotMark = FALSE;
				ReleaseCapture();
				break;
			}

			if (lpSBData->pushBtn) 
			{
				if (lpSBData->pbState)
					lpSBData->pbState = FALSE;
				else
					lpSBData->pbState = TRUE;
			}

			if (lpSBData->nStateId != PBS_DISABLED)
			{
				// don't change states if disabled
				if (msg == WM_LBUTTONUP)
					lpSBData->nStateId = PBS_HOT;
				else
					lpSBData->nStateId = PBS_NORMAL;
				InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
			}
			if(!lpSBData->fSendOnDown && lpSBData->fHotMark)
				SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKELONG(GetDlgCtrlID(hwndDlg), BN_CLICKED), (LPARAM) hwndDlg);
			lpSBData->fHotMark = FALSE;
			break;
		}
	case WM_MOUSEMOVE:
		{
			RECT rc;
			POINT pt;
			BOOL bPressed = (wParam & MK_LBUTTON) != 0;
			if ( bPressed && !lpSBData->fHotMark )
				break;
			GetWindowRect(hwndDlg, &rc);
			GetCursorPos(&pt);
			BOOL inClient = PtInRect(&rc, pt);
			if ( inClient )
			{
				SetCapture( lpSBData->hWnd );
				if ( lpSBData->nStateId == PBS_NORMAL ) 
				{
					lpSBData->nStateId = PBS_HOT;
					InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
				}
			}

			if ( !inClient && lpSBData->nStateId == PBS_PRESSED )
			{
				lpSBData->nStateId = PBS_HOT; 
				InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
			}
			else if ( inClient && lpSBData->nStateId == PBS_HOT && bPressed )
			{
				if( lpSBData->fHotMark )
				{
					lpSBData->nStateId = PBS_PRESSED;
					InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
				}
			}
			else if ( !inClient && !bPressed)
			{
				lpSBData->fHotMark = FALSE;
				ReleaseCapture();
			}
		}
	//	else
		{
			//KillTimer(hwndDlg, BUTTON_POLLID);
			//CLUI_SafeSetTimer(hwndDlg, BUTTON_POLLID, BUTTON_POLLDELAY, NULL);
		}
		// Call timer, used to start cheesy TrackMouseEvent faker
		

		break;

	case WM_NCHITTEST:
		{
			LRESULT lr = SendMessage(GetParent(hwndDlg), WM_NCHITTEST, wParam, lParam);
			if(lr == HTLEFT || lr == HTRIGHT || lr == HTBOTTOM || lr == HTTOP || lr == HTTOPLEFT || lr == HTTOPRIGHT
				|| lr == HTBOTTOMLEFT || lr == HTBOTTOMRIGHT)
				return HTTRANSPARENT;
			break;
		}
	/*case WM_TIMER: // use a timer to check if they have did a mouse out		
		{
			if (wParam == BUTTON_POLLID)
			{
				HWND hwnd=GetCapture();
				if ( hwnd == lpSBData->hWnd ) 
				{
					//KillTimer(hwndDlg, BUTTON_POLLID);
					break;
				}
				RECT rc;
				POINT pt;
				GetWindowRect(hwndDlg, &rc);
				GetCursorPos(&pt);
				BOOL bInside = ( PtInRect( &rc, pt ) && ( WindowFromPoint( pt ) == lpSBData->hWnd) );
				if ( !bInside ) 
				{
					// mouse must be gone, trigger mouse leave
					PostMessage(hwndDlg, WM_MOUSELEAVE, 0, 0L);
					KillTimer(hwndDlg, BUTTON_POLLID);
				}
			}
			break;
		}
		*/
	case WM_ERASEBKGND:
		{
			return 1;
		}
	case MBM_SETICOLIBHANDLE:
		{
			if (lpSBData->hIconPrivate) 
			{
				DestroyIcon(lpSBData->hIconPrivate);
				lpSBData->hIconPrivate = 0;
			}

			lpSBData->hIcolibHandle=(HANDLE)lParam;
			if (lpSBData->hIcolibHandle)
				lpSBData->hIcon=(HICON)CallService(MS_SKIN2_GETICONBYHANDLE, 0 , (LPARAM) lpSBData->hIcolibHandle);
			else
				lpSBData->hIcon=NULL;
			return 1;
		}
	case MBM_REFRESHICOLIBICON:
		{
			if (lpSBData->hIconPrivate) 
			{
				DestroyIcon(lpSBData->hIconPrivate);
				lpSBData->hIconPrivate = 0;
			}
			if (lpSBData->hIcolibHandle)
				lpSBData->hIcon=(HICON)CallService(MS_SKIN2_GETICONBYHANDLE, 0 , (LPARAM) lpSBData->hIcolibHandle);
			else		
				lpSBData->hIcon=NULL;
			InvalidateRect(hwndDlg,NULL,TRUE);
			pcli->pfnInvalidateRect(GetParent(GetParent(hwndDlg)),NULL,TRUE);
			return 1;
		}
	case MBM_UPDATETRANSPARENTFLAG:
		{
			LONG flag=GetWindowLong(hwndDlg,GWL_EXSTYLE);
			LONG oldFlag=flag;
			if (lParam==2) 
				lParam=(g_CluiData.fDisableSkinEngine)?0:1;
			flag&=~WS_EX_TRANSPARENT;
			if (lParam) flag|=WS_EX_TRANSPARENT;
			if (flag!=oldFlag)
			{
				SetWindowLong(hwndDlg,GWL_EXSTYLE,flag);
				RedrawWindow(hwndDlg,NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW);
			}
			return 0;
		}
	case BM_GETIMAGE:
		{
			if(wParam == IMAGE_ICON)
				return (LRESULT)(lpSBData->hIconPrivate ? lpSBData->hIconPrivate : lpSBData->hIcon);
			break;
		}
	case BM_SETIMAGE:
		{
			if(!lParam)
				break;
			if (wParam == IMAGE_ICON) 
			{
				ICONINFO ii = {0};
				BITMAP bm = {0};

				if (lpSBData->hIconPrivate) 
				{
					DestroyIcon(lpSBData->hIconPrivate);
					lpSBData->hIconPrivate = 0;
				}

				GetIconInfo((HICON) lParam, &ii);
				GetObject(ii.hbmColor, sizeof(bm), &bm);
				if (bm.bmWidth > 16 || bm.bmHeight > 16) 
				{
					HIMAGELIST hImageList;
					hImageList = ImageList_Create(16, 16, IsWinVerXPPlus() ? ILC_COLOR32 | ILC_MASK : ILC_COLOR16 | ILC_MASK, 1, 0);
					ImageList_AddIcon(hImageList, (HICON) lParam);
					lpSBData->hIconPrivate = ImageList_GetIcon(hImageList, 0, ILD_NORMAL);
					ImageList_RemoveAll(hImageList);
					ImageList_Destroy(hImageList);
					lpSBData->hIcon = 0;
				} 
				else 
				{
					lpSBData->hIcon = (HICON) lParam;
					lpSBData->hIconPrivate = NULL;
				}

				DeleteObject(ii.hbmMask);
				DeleteObject(ii.hbmColor);
				InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
			}
			else if (wParam == IMAGE_BITMAP) 
			{
				if (lpSBData->hIconPrivate)
					DestroyIcon(lpSBData->hIconPrivate);
				lpSBData->hIcon = lpSBData->hIconPrivate = NULL;
				InvalidateParentRect(lpSBData->hWnd, NULL, TRUE);
				return 0; // not supported
			}
			break;
		}
	}
	return DefWindowProc(hwndDlg, msg, wParam, lParam);
}