LONG WINAPI ListboxWndProc(HWND hWnd,UINT messg,UINT wParam,LONG lParam)
{
	int idListbox;
	HDC hdc;
	static int xClientView,yClientView;
	static HWND hInst;

	idListbox = GetWindowLong(hWnd, GWL_ID);
	switch (messg)
	{

          case WM_CREATE:
	    hdc =GetDC(hWnd);
	    GetTextMetrics(hdc, &tm);
	    ReleaseDC(hWnd,hdc);
	    return 0;

	  case WM_SETFOCUS:
#if 0
	    CreateCaret(hWnd,(HBITMAP)1,0,0);
	    SetCaretPos(wins[idListbox]->nCaretPosX,
		wins[idListbox]->nCaretPosY * wins[idListbox]->dwCharY);
	    ShowCaret(hWnd);
	    break;
#endif
#if 0
	  case WM_KILLFOCUS:
	    HideCaret(hWnd);
	    DestroyCaret();
	    break;
#endif

	  case WM_DESTROY:
	    PostQuitMessage(0);
	    break;

	  case WM_COMMAND:
	    switch (HIWORD(wParam)) {
	     case LBN_DBLCLK:
		DEBUG_MSG("Got LBN_DBLCLK");
	        return(DefWindowProc(hWnd,messg,wParam,lParam));
		break;
	     case LBN_KILLFOCUS:
		DEBUG_MSG("Got LBN_KILLFOCUS");
	        return(DefWindowProc(hWnd,messg,wParam,lParam));
		break;
	     case LBN_SELCANCEL:
		DEBUG_MSG("Got LBN_SELCANCEL");
	        return(DefWindowProc(hWnd,messg,wParam,lParam));
		break;
	     case LBN_SELCHANGE:
		DEBUG_MSG("Got LBN_SELCHANGE");
	        return(DefWindowProc(hWnd,messg,wParam,lParam));
		break;
	     case LBN_SETFOCUS:
		DEBUG_MSG("Got LBN_SETFOCUS");
	        return(DefWindowProc(hWnd,messg,wParam,lParam));
		break;
	     case WM_VKEYTOITEM:
		DEBUG_MSG("Got LBN_VKEYTOITEM");
	        return(DefWindowProc(hWnd,messg,wParam,lParam));
		break;
	     default:
	        return(DefWindowProc(hWnd,messg,wParam,lParam));
	    }
	    break;
	  case WM_VSCROLL:
	  case WM_HSCROLL:
	  default:
	    return(DefWindowProc(hWnd,messg,wParam,lParam));
	}
	return(0L);
}