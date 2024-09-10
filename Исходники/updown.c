/***********************************************************************
 *           UpDownWndProc
 */
static LRESULT WINAPI UpDownWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UPDOWN_INFO *infoPtr = UPDOWN_GetInfoPtr (hwnd);
    static const WCHAR themeClass[] = {'S','p','i','n',0};
    HTHEME theme;

    TRACE("hwnd=%p msg=%04x wparam=%08lx lparam=%08lx\n", hwnd, message, wParam, lParam);

    if (!infoPtr && (message != WM_CREATE))
        return DefWindowProcW (hwnd, message, wParam, lParam);

    switch(message)
    {
        case WM_CREATE:
            infoPtr = Alloc (sizeof(UPDOWN_INFO));
	    SetWindowLongPtrW (hwnd, 0, (DWORD_PTR)infoPtr);

	    /* initialize the info struct */
	    infoPtr->Self = hwnd;
	    infoPtr->Notify = ((LPCREATESTRUCTW)lParam)->hwndParent;
            infoPtr->dwStyle = ((LPCREATESTRUCTW)lParam)->style;
	    infoPtr->AccelCount = 0;
	    infoPtr->AccelVect = 0;
	    infoPtr->AccelIndex = -1;
	    infoPtr->CurVal = 0;
	    infoPtr->MinVal = 100;
	    infoPtr->MaxVal = 0;
	    infoPtr->Base  = 10; /* Default to base 10  */
	    infoPtr->Buddy = 0;  /* No buddy window yet */
	    infoPtr->Flags = 0;  /* And no flags        */

            SetWindowLongW (hwnd, GWL_STYLE, infoPtr->dwStyle & ~WS_BORDER);

            /* Do we pick the buddy win ourselves? */
	    if (infoPtr->dwStyle & UDS_AUTOBUDDY)
		UPDOWN_SetBuddy (infoPtr, GetWindow (hwnd, GW_HWNDPREV));

            OpenThemeData (hwnd, themeClass);

	    TRACE("UpDown Ctrl creation, hwnd=%p\n", hwnd);
	    break;

	case WM_DESTROY:
	    Free (infoPtr->AccelVect);

	    if(infoPtr->Buddy) RemovePropW(infoPtr->Buddy, BUDDY_UPDOWN_HWND);

	    Free (infoPtr);
	    SetWindowLongPtrW (hwnd, 0, 0);
            theme = GetWindowTheme (hwnd);
            CloseThemeData (theme);
	    TRACE("UpDown Ctrl destruction, hwnd=%p\n", hwnd);
	    break;

	case WM_ENABLE:
	    if (wParam) {
		infoPtr->dwStyle &= ~WS_DISABLED;
	    } else {
		infoPtr->dwStyle |= WS_DISABLED;
	    	UPDOWN_CancelMode (infoPtr);
	    }
	    InvalidateRect (infoPtr->Self, NULL, FALSE);
	    break;

        case WM_STYLECHANGED:
            if (wParam == GWL_STYLE) {
                infoPtr->dwStyle = ((LPSTYLESTRUCT)lParam)->styleNew;
	        InvalidateRect (infoPtr->Self, NULL, FALSE);
            }
            break;

        case WM_THEMECHANGED:
            theme = GetWindowTheme (hwnd);
            CloseThemeData (theme);
            OpenThemeData (hwnd, themeClass);
            InvalidateRect (hwnd, NULL, FALSE);
            break;

	case WM_TIMER:
	   /* is this the auto-press timer? */
	   if(wParam == TIMER_AUTOPRESS) {
		KillTimer(hwnd, TIMER_AUTOPRESS);
		infoPtr->Flags &= ~(FLAG_PRESSED | FLAG_ARROW);
		InvalidateRect(infoPtr->Self, NULL, FALSE);
	   }

	   /* if initial timer, kill it and start the repeat timer */
  	   if(wParam == TIMER_AUTOREPEAT) {
		int temp;

		KillTimer(hwnd, TIMER_AUTOREPEAT);
		/* if no accel info given, used default timer */
		if(infoPtr->AccelCount==0 || infoPtr->AccelVect==0) {
		    infoPtr->AccelIndex = -1;
		    temp = REPEAT_DELAY;
		} else {
		    infoPtr->AccelIndex = 0; /* otherwise, use it */
		    temp = infoPtr->AccelVect[infoPtr->AccelIndex].nSec * 1000 + 1;
		}
		SetTimer(hwnd, TIMER_ACCEL, temp, 0);
      	    }

	    /* now, if the mouse is above us, do the thing...*/
	    if(infoPtr->Flags & FLAG_MOUSEIN) {
		int temp;

		temp = infoPtr->AccelIndex == -1 ? 1 : infoPtr->AccelVect[infoPtr->AccelIndex].nInc;
		UPDOWN_DoAction(infoPtr, temp, infoPtr->Flags & FLAG_ARROW);

		if(infoPtr->AccelIndex != -1 && infoPtr->AccelIndex < infoPtr->AccelCount-1) {
		    KillTimer(hwnd, TIMER_ACCEL);
		    infoPtr->AccelIndex++; /* move to the next accel info */
		    temp = infoPtr->AccelVect[infoPtr->AccelIndex].nSec * 1000 + 1;
	  	    /* make sure we have at least 1ms intervals */
		    SetTimer(hwnd, TIMER_ACCEL, temp, 0);
		}
	    }
	    break;

	case WM_CANCELMODE:
	  return UPDOWN_CancelMode (infoPtr);

	case WM_LBUTTONUP:
	    if (GetCapture() != infoPtr->Self) break;

	    if ( (infoPtr->Flags & FLAG_MOUSEIN) &&
		 (infoPtr->Flags & FLAG_ARROW) ) {

	    	SendMessageW( infoPtr->Notify,
			      (infoPtr->dwStyle & UDS_HORZ) ? WM_HSCROLL : WM_VSCROLL,
                  	      MAKELONG(SB_ENDSCROLL, infoPtr->CurVal),
			      (LPARAM)hwnd);
		if (UPDOWN_IsBuddyEdit(infoPtr))
		    SendMessageW(infoPtr->Buddy, EM_SETSEL, 0, MAKELONG(0, -1));
	    }
	    UPDOWN_CancelMode(infoPtr);
	    break;

	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
        case WM_MOUSELEAVE:
	    if(UPDOWN_IsEnabled(infoPtr))
		UPDOWN_HandleMouseEvent (infoPtr, message, (SHORT)LOWORD(lParam), (SHORT)HIWORD(lParam));
	    break;

        case WM_MOUSEWHEEL:
            UPDOWN_MouseWheel(infoPtr, wParam);
            break;

	case WM_KEYDOWN:
	    if((infoPtr->dwStyle & UDS_ARROWKEYS) && UPDOWN_IsEnabled(infoPtr))
		return UPDOWN_KeyPressed(infoPtr, (int)wParam);
	    break;

	case WM_PRINTCLIENT:
	case WM_PAINT:
	    return UPDOWN_Paint (infoPtr, (HDC)wParam);

	case UDM_GETACCEL:
	    if (wParam==0 && lParam==0) return infoPtr->AccelCount;
	    if (wParam && lParam) {
		int temp = min(infoPtr->AccelCount, wParam);
	        memcpy((void *)lParam, infoPtr->AccelVect, temp*sizeof(UDACCEL));
	        return temp;
      	    }
	    return 0;

	case UDM_SETACCEL:
	{
	    unsigned temp;

	    TRACE("UDM_SETACCEL\n");

	    if(infoPtr->AccelVect) {
		Free (infoPtr->AccelVect);
		infoPtr->AccelCount = 0;
		infoPtr->AccelVect  = 0;
      	    }
	    if(wParam==0) return TRUE;
	    infoPtr->AccelVect = Alloc (wParam*sizeof(UDACCEL));
	    if(infoPtr->AccelVect == 0) return FALSE;
	    memcpy(infoPtr->AccelVect, (void*)lParam, wParam*sizeof(UDACCEL));
            infoPtr->AccelCount = wParam;

            for (temp = 0; temp < wParam; temp++)
                TRACE("%d: nSec %u nInc %u\n", temp, infoPtr->AccelVect[temp].nSec, infoPtr->AccelVect[temp].nInc);

    	    return TRUE;
	}
	case UDM_GETBASE:
	    return infoPtr->Base;

	case UDM_SETBASE:
	    TRACE("UpDown Ctrl new base(%ld), hwnd=%p\n", wParam, hwnd);
	    if (wParam==10 || wParam==16) {
		WPARAM temp = infoPtr->Base;
		infoPtr->Base = wParam;
		return temp;
	    }
	    break;

	case UDM_GETBUDDY:
	    return (LRESULT)infoPtr->Buddy;

	case UDM_SETBUDDY:
	    return (LRESULT)UPDOWN_SetBuddy (infoPtr, (HWND)wParam);

	case UDM_GETPOS:
	{
	    int temp = UPDOWN_GetBuddyInt (infoPtr);
	    return MAKELONG(infoPtr->CurVal, temp ? 0 : 1);
	}
	case UDM_SETPOS:
	{
	    int temp = (short)LOWORD(lParam);

	    TRACE("UpDown Ctrl new value(%d), hwnd=%p\n", temp, hwnd);
	    if(!UPDOWN_InBounds(infoPtr, temp)) {
		if(temp < infoPtr->MinVal) temp = infoPtr->MinVal;
		if(temp > infoPtr->MaxVal) temp = infoPtr->MaxVal;
	    }
	    wParam = infoPtr->CurVal;
	    infoPtr->CurVal = temp;
	    UPDOWN_SetBuddyInt (infoPtr);
	    return wParam;            /* return prev value */
	}
	case UDM_GETRANGE:
	    return MAKELONG(infoPtr->MaxVal, infoPtr->MinVal);

	case UDM_SETRANGE:
                                                     /* we must have:     */
	    infoPtr->MaxVal = (short)(lParam);       /* UD_MINVAL <= Max <= UD_MAXVAL */
	    infoPtr->MinVal = (short)HIWORD(lParam); /* UD_MINVAL <= Min <= UD_MAXVAL */
                                                     /* |Max-Min| <= UD_MAXVAL        */
	    TRACE("UpDown Ctrl new range(%d to %d), hwnd=%p\n",
		  infoPtr->MinVal, infoPtr->MaxVal, hwnd);
	    break;

	case UDM_GETRANGE32:
	    if (wParam) *(LPINT)wParam = infoPtr->MinVal;
	    if (lParam) *(LPINT)lParam = infoPtr->MaxVal;
	    break;

	case UDM_SETRANGE32:
	    infoPtr->MinVal = (INT)wParam;
	    infoPtr->MaxVal = (INT)lParam;
	    if (infoPtr->MaxVal <= infoPtr->MinVal)
		infoPtr->MaxVal = infoPtr->MinVal + 1;
	    TRACE("UpDown Ctrl new range(%d to %d), hwnd=%p\n",
		  infoPtr->MinVal, infoPtr->MaxVal, hwnd);
	    break;

	case UDM_GETPOS32:
	    if ((LPBOOL)lParam != NULL) *((LPBOOL)lParam) = TRUE;
	    return infoPtr->CurVal;

	case UDM_SETPOS32:
	{
	    int temp;

	    if(!UPDOWN_InBounds(infoPtr, (int)lParam)) {
		if((int)lParam < infoPtr->MinVal) lParam = infoPtr->MinVal;
		if((int)lParam > infoPtr->MaxVal) lParam = infoPtr->MaxVal;
	    }
	    temp = infoPtr->CurVal;         /* save prev value   */
	    infoPtr->CurVal = (int)lParam;  /* set the new value */
	    UPDOWN_SetBuddyInt (infoPtr);
	    return temp;                    /* return prev value */
	}
	case UDM_GETUNICODEFORMAT:
	    /* we lie a bit here, we're always using Unicode internally */
	    return infoPtr->UnicodeFormat;

	case UDM_SETUNICODEFORMAT:
	{
	    /* do we really need to honour this flag? */
	    int temp = infoPtr->UnicodeFormat;
	    infoPtr->UnicodeFormat = (BOOL)wParam;
	    return temp;
	}
	default:
	    if ((message >= WM_USER) && (message < WM_APP) && !COMCTL32_IsReflectedMessage(message))
		ERR("unknown msg %04x wp=%04lx lp=%08lx\n", message, wParam, lParam);
	    return DefWindowProcW (hwnd, message, wParam, lParam);
    }

    return 0;
}