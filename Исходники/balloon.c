LRESULT CALLBACK _export BalloonProc(HWND hwnd, UINT message, WPARAM wParam,
                                     LPARAM lParam)
{
static DWORD lasttime;  // ??? should be a property
static POINT ttpos;
  RECT rect;
  POINT point;
  int x, y, width, height;
  SIZE size;
  LPSTR ptr;
  char text[256];

  switch (message) {
  case WM_CREATE: {
    HFONT hfont = CreateFont(-11, 0, 0, 0, FW_NORMAL, FALSE, 0, 0, DEFAULT_CHARSET,
                             OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS,
                             PROOF_QUALITY, FF_DONTCARE, "MS Sans Serif");
    SetProp(hwnd,MAKEINTRESOURCE(atomFont),hfont);
    break;
  } /* case */

  case WM_DESTROY: {
    HFONT hfont = (HFONT)GetProp(hwnd,MAKEINTRESOURCE(atomFont));
    if (hfont)
      DeleteObject(hfont);
    RemoveProp(hwnd,MAKEINTRESOURCE(atomAlignStyle));
    RemoveProp(hwnd,MAKEINTRESOURCE(atomTailSize));
    RemoveProp(hwnd,MAKEINTRESOURCE(atomTimeout));
    RemoveProp(hwnd,MAKEINTRESOURCE(atomFont));
    break;
  } /* case */

  case WM_ERASEBKGND:
    return 0L;

  case WM_LBUTTONDOWN:
  case WM_RBUTTONDOWN:
  case WM_LBUTTONUP:
  case WM_RBUTTONUP:
    ShowWindow(hwnd, SW_HIDE);
    if (IsWindow(GetParent(hwnd)))
      PostMessage(GetParent(hwnd), BAN_VISIBLE, (WPARAM)hwnd, 0L);
    break;

  case WM_WINDOWPOSCHANGING:
  case WM_WINDOWPOSCHANGED:
    return 0L;

  case WM_PAINT: {
    PAINTSTRUCT ps;
    COLORREF clrBackgr;
    HBRUSH hbrBackgr;
    HRGN hrgn;
    int AlignStyle=(int)GetProp(hwnd,MAKEINTRESOURCE(atomAlignStyle));
    HFONT hfont = (HFONT)GetProp(hwnd,MAKEINTRESOURCE(atomFont));

    HDC hdc = BeginPaint(hwnd, &ps);
    GetClientRect(hwnd, &rect);

    clrBackgr=GetNearestColor(hdc, RGB(255,255,192));
    hbrBackgr = CreateSolidBrush(clrBackgr);
    #if defined __WIN32__
      hrgn=CreateRectRgn(0,0,1,1);
      GetWindowRgn(hwnd,hrgn);      /* Win32-only */
    #else
      #if BM_RADIUS==0
        hrgn=CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
      #else
        hrgn=CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, BM_RADIUS, BM_RADIUS);
      #endif
    #endif
    FillRgn(hdc,hrgn,hbrBackgr);
    FrameRgn(hdc,hrgn,GetStockObject(BLACK_BRUSH),1,1);
    DeleteObject(hbrBackgr);

    hfont = SelectObject(hdc, hfont);
    GetWindowText(hwnd, text, sizeof text);
    GetTextExtentPoint(hdc, text, lstrlen(text), &size);
    SetBkMode(hdc, TRANSPARENT);
    y=BM_MARGINTOP;
    if (AlignStyle==BAA_TOP) {
      int TailSize=(int)GetProp(hwnd,MAKEINTRESOURCE(atomTailSize));
      y+=TailSize;
    } /* if */
    for (ptr=strtok(text,"\n"); ptr!=NULL; ptr=strtok(NULL,"\n"), y+=size.cy) {
      GetTextExtentPoint(hdc, ptr, lstrlen(ptr), &size);
      x = ((rect.right-rect.left) - size.cx) / 2;
      TextOut(hdc, x, y, ptr, lstrlen(ptr));
    } /* for */
    SelectObject(hdc, hfont);

    EndPaint(hwnd, &ps);
    break;
  } /* case */

  case WM_TIMER: {
    DWORD timeout=(DWORD)GetProp(hwnd,MAKEINTRESOURCE(atomTimeout));
    DWORD curtime=GetTickCount();
    GetCursorPos(&point);
    if (timeout==0)
      break;
    if (curtime >= lasttime+timeout)
      SendMessage(hwnd, BAM_SHOW, 0, 0L);
    break;
  } /* if */

  case BAM_SETPOS:
    ttpos=*(LPPOINT)lParam;
    break;

  case BAM_SHOW:
    if (wParam) {
      HDC hdc;
      HRGN hrgn;
      int AlignStyle=(int)GetProp(hwnd,MAKEINTRESOURCE(atomAlignStyle));
      int TailSize=(int)GetProp(hwnd,MAKEINTRESOURCE(atomTailSize));
      HFONT hfont=(HFONT)GetProp(hwnd,MAKEINTRESOURCE(atomFont));
      ASSERT(lParam!=0);
      lstrcpy(text, (LPSTR)lParam);
      SetWindowText(hwnd, text);
      InvalidateRect(hwnd, NULL, FALSE);
      hdc = GetDC(hwnd);
      hfont = SelectObject(hdc, hfont);
      for (ptr=strtok(text,"\n"), width=height=0; ptr!=NULL; ptr=strtok(NULL,"\n")) {
        GetTextExtentPoint(hdc, ptr, lstrlen(ptr), &size);
        width = max(width, size.cx);
        height += size.cy;
      } /* for */
      SelectObject(hdc, hfont);
      ReleaseDC(hwnd, hdc);
      width += 2*BM_MARGINX;
      height += BM_MARGINTOP + BM_MARGINBOTTOM;
      #if 0
        // round width up to multiple of 16 pixels and height up to a multiple
        // of 8 pixels
        width+=16-1;
        width=width - (width%16);
        height+=8-1;
        height=height - (height%8);
      #endif
      // also add the tail size to the height
      height+=TailSize;
      // check alignment
      switch (AlignStyle) {
      case BAA_TOP:
        x = ttpos.x - width/4;
        y = ttpos.y;
        break;
      case BAA_BOTTOM:
        x = ttpos.x - width/4;
        y = ttpos.y - height;
        break;
      } /* switch */
      // check screen position against the screen size (width)
      if (x < 0)
        x = 0;
      else if (x+width >= GetSystemMetrics(SM_CXSCREEN)-1)
        x = GetSystemMetrics(SM_CXSCREEN) - width - 1;
      if (y < 0)
        y = 0;
      else if (y+height >= GetSystemMetrics(SM_CYSCREEN)-1)
        y = GetSystemMetrics(SM_CYSCREEN) - height - 1;
      GetWindowRect(hwnd,&rect);  // get first, check later (for new region)
      SetWindowPos(hwnd, HWND_TOPMOST, x, y, width, height, SWP_SHOWWINDOW|SWP_NOACTIVATE);
      hrgn=MakeBalloonRegion(width+1,height+1,BM_RADIUS,AlignStyle,TailSize,ttpos.x-x,ttpos.y-y);
      ASSERT(hrgn!=NULL);
      SetWindowRgn(hwnd, hrgn, TRUE);
      UpdateWindow(hwnd);
      lasttime=GetTickCount();
    } else {
      ShowWindow(hwnd, SW_HIDE);
      lasttime=GetTickCount();
    } /* if */
    break;

  default:
    return DefWindowProc(hwnd, message, wParam, lParam);
  } /* switch */
  return 0L;
}