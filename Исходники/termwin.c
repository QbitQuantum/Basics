long CALLBACK EXPORT ConsoleFunc(HWND hwnd,unsigned message,WPARAM wParam,
                                 LPARAM lParam)
{
  CONSOLE *con;
  PAINTSTRUCT ps;
  RECT rect;

  switch (message) {
  case WM_CHAR:
    if ((con=Hwnd2Console(hwnd))!=NULL) {
      /* store in a key queue */
      if ((con->keyq_end+1)%KEYQUEUE_SIZE==con->keyq_start) {
        MessageBeep(MB_OK);
        break;
      } /* if */
      con->keyqueue[con->keyq_end]=(short)wParam;
      con->keyq_end=(con->keyq_end+1)%KEYQUEUE_SIZE;
    } /* if */
    break;

  case WM_CREATE:
    /* The "hwnd" member of the CONSOLE structure has not yet been set, which
     * means that Hwnd2Console() cannot work on the real "hwnd". There should
     * at every instant be only one CONSOLE structure with a NULL handle,
     * however.
     */
    if ((con=Hwnd2Console(NULL))!=NULL) {
      con->hwnd=hwnd;
      SetConsoleFont(con,con->cheight);
      GetWindowRect(hwnd, &rect);
      SetRect(&rect,rect.left,rect.top,
              rect.left+con->cwidth*con->columns,
              rect.top+con->cheight*con->winlines);
      AdjustWindowRect(&rect,GetWindowLong(hwnd,GWL_STYLE),FALSE);
      if (con->winlines<con->lines)
        rect.right+=GetSystemMetrics(SM_CXVSCROLL);
      ClampToScreen(&rect);
      SetWindowPos(hwnd,NULL,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,
                   SWP_NOZORDER);
    } /* if */
    break;

  case WM_DESTROY:
    if ((con=Hwnd2Console(hwnd))!=NULL)
      DoDeleteConsole(con);
    break;

  case WM_GETMINMAXINFO:
    if ((con=Hwnd2Console(hwnd))!=NULL) {
      MINMAXINFO FAR *lpmmi=(MINMAXINFO FAR*)lParam;
      int rx,ry,hsize,vsize;
      GetClientRect(hwnd,&rect);
      rx= (rect.right < con->columns*con->cwidth) ? con->columns*con->cwidth-rect.right : 0;
      ry= (rect.bottom < con->lines*con->cheight) ? con->lines*con->cheight-rect.bottom : 0;
      hsize= (ry>0) ? GetSystemMetrics(SM_CXVSCROLL) : 0;
      vsize= (rx>0) ? GetSystemMetrics(SM_CYHSCROLL) : 0;
      SetRect(&rect,0,0,con->cwidth*con->columns+hsize,con->cheight*con->lines+vsize);
      AdjustWindowRect(&rect,GetWindowLong(hwnd,GWL_STYLE),FALSE);
      lpmmi->ptMaxTrackSize.x=rect.right-rect.left;
      lpmmi->ptMaxTrackSize.y=rect.bottom-rect.top;
      lpmmi->ptMaxSize=lpmmi->ptMaxTrackSize;
    } /* if */
    break;

  case WM_SYSKEYDOWN:
  case WM_KEYDOWN:
    if ((con=Hwnd2Console(hwnd))!=NULL) {
      TCHAR str[20];
      int i;
      str[0]=__T('\0');
      switch (LOWORD(wParam)) {
      case VK_F1:
      case VK_F2:
      case VK_F3:
      case VK_F4:
      case VK_F5:
      case VK_F6:
      case VK_F7:
      case VK_F8:
      case VK_F9:
      case VK_F10:
      case VK_F11:
      case VK_F12:
        if (LOWORD(wParam)<=VK_F5)
          _stprintf(str,__T("\033[%d~\n"),LOWORD(wParam)-VK_F1+11);
        else if (LOWORD(wParam)==VK_F10)
          _stprintf(str,__T("\033[%d~\n"),LOWORD(wParam)-VK_F6+17);
        else
          _stprintf(str,__T("\033[%d~\n"),LOWORD(wParam)-VK_F11+23);
        break;
      case VK_ADD:
      case VK_SUBTRACT:
        /* check Ctrl key */
        if ((GetKeyState(VK_CONTROL) & 0x8000)!=0) {
          POINT pt;
          int newheight=con->cheight;
          int oldheight=newheight;
          int incr= (LOWORD(wParam)==VK_SUBTRACT) ? -1 : 1;
          do {
            newheight+=incr;
            /* make a new font, re-create a caret and redraw everything */
            SetConsoleFont(con,newheight);
          } while (newheight>5 && (oldheight==con->cheight || con->hfont==NULL));
          if (con->hfont==NULL) /* reset to original on failure */
            SetConsoleFont(con,oldheight);
          GetClientRect(hwnd,&rect);
          DestroyCaret();
          CreateCaret(hwnd,NULL,con->cwidth,2);
          RefreshCaretPos(con);
          /* redraw the window */
          InvalidateRect(hwnd,NULL,TRUE);
          /* resize the window */
          SetRect(&rect,0,0,con->cwidth*con->columns,con->cheight*con->winlines);
          AdjustWindowRect(&rect,GetWindowLong(hwnd,GWL_STYLE),FALSE);
          pt.x=pt.y=0;
          ClientToScreen(hwnd,&pt);
          OffsetRect(&rect,pt.x,pt.y);
          ClampToScreen(&rect);
          SetWindowPos(hwnd,NULL,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,
                       SWP_NOZORDER);
        } /* if */
        break;
      case VK_UP:
        _tcscpy(str,__T("\033[A"));
        break;
      case VK_DOWN:
        _tcscpy(str,__T("\033[B"));
        break;
      case VK_RIGHT:
        _tcscpy(str,__T("\033[C"));
        break;
      case VK_LEFT:
        _tcscpy(str,__T("\033[D"));
        break;
      case VK_HOME:
        _tcscpy(str,__T("\033[1~"));
        break;
      case VK_END:
        _tcscpy(str,__T("\033[4~"));
        break;
      case VK_INSERT:
        _tcscpy(str,__T("\033[2~"));
        break;
      case VK_DELETE:
        _tcscpy(str,__T("\033[3~"));
        break;
      case VK_PRIOR:  /* PageUp */
        _tcscpy(str,__T("\033[5~"));
        break;
      case VK_NEXT:   /* PageDown */
        _tcscpy(str,__T("\033[6~"));
        break;
      default:
        return DefWindowProc(hwnd,message,wParam,lParam);
      } /* switch */
      for (i=0; str[i]!=__T('\0'); i++) {
        if ((con->keyq_end+1)%KEYQUEUE_SIZE!=con->keyq_start) {
          con->keyqueue[con->keyq_end]=(short)str[i];
          con->keyq_end=(con->keyq_end+1)%KEYQUEUE_SIZE;
        } /* if */
      } /* for */
    } /* if */
    break;

  case WM_KILLFOCUS:
    HideCaret(hwnd);
    DestroyCaret();
    break;
  case WM_SETFOCUS:
    if ((con=Hwnd2Console(hwnd))!=NULL) {
      CreateCaret(hwnd,NULL,con->cwidth,2);
      RefreshCaretPos(con);
      ShowCaret(hwnd);
    } /* if */
    break;

  case WM_LBUTTONDOWN:
    SetFocus(hwnd);
    break;

  case WM_PAINT:
    HideCaret(hwnd);
    BeginPaint(hwnd, &ps);
    if ((con=Hwnd2Console(hwnd))!=NULL && con->buffer!=NULL) {
      TCHAR *string;
      string=malloc(con->columns*sizeof(TCHAR));
      if (string!=NULL) {
        int l,c,bpos,start;
        TCHAR attr;
        HFONT hfontOrg;
        int scrollx=GetScrollPos(hwnd,SB_HORZ);
        int scrolly=GetScrollPos(hwnd,SB_VERT);
        GetClientRect(hwnd,&rect);
        hfontOrg=SelectObject(ps.hdc,con->hfont);
        SetBkMode(ps.hdc,OPAQUE);
        for (l=0; l<con->lines; l++) {
          bpos=l*con->columns*2;
          c=0;
          while (c<con->columns) {
            /* find stretches with the same attribute */
            attr=con->buffer[bpos+1];
            start=c;
            while (c<con->columns && con->buffer[bpos+1]==attr) {
              assert(c-start>=0);
              assert(c-start<con->columns);
              string[c-start]=con->buffer[bpos];
              c++;
              bpos+=2;
            } /* if */
            SetTextAttribute(ps.hdc,attr);
            TextOut(ps.hdc,start*con->cwidth-scrollx,l*con->cheight-scrolly,string,c-start);
          } /* while */
        } /* for */
        SelectObject(ps.hdc,hfontOrg);
        free(string);
      } /* if */
    } /* if */
    EndPaint(hwnd, &ps);
    ShowCaret(hwnd);
    break;

  case WM_SIZE:
    if ((con=Hwnd2Console(hwnd))!=NULL) {
      int rx,ry;
      /* add/remove/recalculate scroll bars */
      GetClientRect(hwnd,&rect);
      rx= (rect.right < con->columns*con->cwidth) ? con->columns*con->cwidth-rect.right : 0;
      ry= (rect.bottom < con->lines*con->cheight) ? con->lines*con->cheight-rect.bottom : 0;
      /* adjust scrolling position, if necessary */
      if (GetScrollPos(hwnd,SB_HORZ)>=rx) {
        SetScrollPos(hwnd,SB_HORZ,rx,FALSE);
        InvalidateRect(hwnd,NULL,FALSE);
      } /* if */
      if (GetScrollPos(hwnd,SB_VERT)>=ry) {
        SetScrollPos(hwnd,SB_VERT,ry,FALSE);
        InvalidateRect(hwnd,NULL,FALSE);
      } /* if */
      SetScrollRange(hwnd,SB_HORZ,0,rx,TRUE);
      SetScrollRange(hwnd,SB_VERT,0,ry,TRUE);
    } /* if */
    break;

  case WM_HSCROLL:
    if ((con=Hwnd2Console(hwnd))!=NULL) {
      int scrollx=GetScrollPos(hwnd,SB_HORZ);
      int oldpos=scrollx;
      int min,max;
      GetScrollRange(hwnd,SB_HORZ,&min,&max);
      switch (LOWORD(wParam)) {
      case SB_TOP:
        scrollx=min;
        break;
      case SB_BOTTOM:
        scrollx=max;
        break;
      case SB_LINELEFT:
        scrollx=(scrollx>min) ? scrollx-1 : min;
        break;
      case SB_LINERIGHT:
        scrollx=(scrollx<max) ? scrollx+1 : max;
        break;
      case SB_PAGELEFT:
        scrollx=(scrollx>min) ? scrollx-50 : min;
        break;
      case SB_PAGERIGHT:
        scrollx=(scrollx<max) ? scrollx+50 : max;
        break;
      case SB_THUMBTRACK:
        scrollx=(int)HIWORD(wParam);
        break;
      } /* switch */
      if (oldpos!=scrollx) {
        SetScrollPos(hwnd,SB_HORZ,scrollx,TRUE);
        InvalidateRect(hwnd,NULL,FALSE);
        RefreshCaretPos(con);
      } /* if */
    } /* if */
    break;
  case WM_VSCROLL:
    if ((con=Hwnd2Console(hwnd))!=NULL) {
      int scrolly=GetScrollPos(hwnd,SB_VERT);
      int oldpos=scrolly;
      int min,max;
      GetScrollRange(hwnd,SB_VERT,&min,&max);
      switch (LOWORD(wParam)) {
      case SB_TOP:
        scrolly=min;
        break;
      case SB_BOTTOM:
        scrolly=max;
        break;
      case SB_LINELEFT:
        scrolly=(scrolly>min) ? scrolly-1 : min;
        break;
      case SB_LINERIGHT:
        scrolly=(scrolly<max) ? scrolly+1 : max;
        break;
      case SB_PAGELEFT:
        scrolly=(scrolly>min) ? scrolly-50 : min;
        break;
      case SB_PAGERIGHT:
        scrolly=(scrolly<max) ? scrolly+50 : max;
        break;
      case SB_THUMBTRACK:
        scrolly=(int)HIWORD(wParam);
        break;
      } /* switch */
      if (oldpos!=scrolly) {
        SetScrollPos(hwnd,SB_VERT,scrolly,TRUE);
        InvalidateRect(hwnd,NULL,FALSE);
        RefreshCaretPos(con);
      } /* if */
    } /* if */
    break;

  default:
    return DefWindowProc(hwnd,message,wParam,lParam);
  } /* switch */
  return 0L;
}