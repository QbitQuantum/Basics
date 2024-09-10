void CInfoDisplay::OnPaint()
{
  CPaintDC dc(this); // device context for painting

  CFont *pFont = GetFont();
  dc.SelectObject(pFont);

  // First, we compute the maximum line width, and set the rectangle wide enough to
  // hold this.  Then we use DrawText/DT_CALCRECT to compute the height
  CSecString text;
  GetWindowText(text);
  CSize box = CSize(0, 0);

  // First replace all "\r\n" by"\n" then any remaining "\r" to "\n"
  text.Replace(L"\r\n", L"\n");
  text.Replace(L'\r', L'\n');

  TEXTMETRIC tm;
  dc.GetTextMetrics(&tm); 

  int inf; // inflation factor

  { /* compute box size */
    CSecString s = text;
    while(TRUE) { /* scan string */
      CSecString line;
      int p = s.Find(L"\n");
      if (p < 0)
        line = s;
      else { /* one line */
        line = s.Left(p);
        s = s.Mid(p + 1);
      } /* one line */
      CSize sz = dc.GetTextExtent(line);
      box.cx = max(box.cx, sz.cx);
      box.cy += tm.tmHeight + tm.tmInternalLeading;
      if (p < 0)
        break;
    } /* scan string */

    // Having computed the width, allow for the borders and extra space for margins
    inf = 4 * ::GetSystemMetrics(SM_CXBORDER);
    box.cx += 2 * inf;
    box.cy += 2 * inf;

    CRect rc(0, 0, 0, 0);
    rc.right = box.cx;
    rc.bottom = box.cy;

    bool bMoveWindow(false);
    int x = 0, y = 0;
    // Get area of potentially multiple monitors! - defined in  DboxMain.cpp as extern
    // if use_current_monitor was set in constructor, we'll check only screen where mouse is located
    HRGN hrgn;
    POINT mouse_pt;
    GetCursorPos(&mouse_pt);
    if (m_use_current_monitor){
       MONITORINFO mi;
       mi.cbSize = sizeof(mi);
       GetMonitorInfo(MonitorFromPoint(mouse_pt, MONITOR_DEFAULTTONEAREST), &mi);
       hrgn = CreateRectRgn(mi.rcWork.left, mi.rcWork.top, mi.rcWork.right, mi.rcWork.bottom);
    }
    else
      hrgn = GetWorkAreaRegion();

    if (hrgn != NULL) {
      // Test that all tip window is visible in the desktop rectangle.
      CRect rs(rc);
      // Convert to screen co-ordinates
      ClientToScreen(rs);
      if (!PtInRegion(hrgn, rs.right, rs.bottom) || !PtInRegion(hrgn, rs.left, rs.top)) {
        // Not in region - move Window
        RECT hr;
        if (GetRgnBox(hrgn, &hr)){
          if (rs.right > hr.right) {
             if (mouse_pt.x - rs.Width() - 1 >= hr.left) // can flip left?
               x = mouse_pt.x - rs.Width() - 1;
             else if (hr.right - rs.Width() >= hr.left) // can shift left and fit width?
               x = hr.right - rs.Width();
             else // press to left border
               x = hr.left;
          }
          else // no need to move
             x = rs.left; 

          if (rs.bottom > hr.bottom) {
             if (mouse_pt.y - rs.Height() - 1 >= hr.top)  // can flip up?
               y = mouse_pt.y - rs.Height() - 1;
             else if (hr.bottom - rs.Height() >= hr.top) // can shift up and fit height?
               y = hr.bottom - rs.Height();
             else // press to top border
               y = hr.top;
          }
          else // no need to move
             y = rs.top; 

          bMoveWindow = true;
          // Check that mouse pointer isn't on infowindow: when it is, window isn't displayed (treated somewhere as focus/mouse move?)
          if ((mouse_pt.x >= x) && (mouse_pt.x <= x + rs.Width()) && (mouse_pt.y >= y) && (mouse_pt.y <= y + rs.Height())) {
             if (mouse_pt.y == y)
                y++;
             else if (mouse_pt.y == y + rs.Height())
                y--;
             else if (mouse_pt.x == x)
                x++;
             else if (mouse_pt.x == x + rs.Width())
                x--;
             else if ((mouse_pt.y >= y) && (mouse_pt.y <= y + rs.Height())) // show top part of the message and trim/split bottom 
                y = mouse_pt.y + 1;
          }
        }
      }

      DeleteObject(hrgn);
    }

    // Set the window size
    SetWindowPos(NULL, x, y, rc.Width(), rc.Height(), 
                 (bMoveWindow ? 0: SWP_NOMOVE) |  SWP_NOZORDER | SWP_NOACTIVATE);
  } /* compute box size */     

  CRect r;
  GetClientRect(&r);
  r.InflateRect(-inf, -inf);

  dc.SetBkMode(TRANSPARENT);
   
  CSecString s = text;
  int y = r.top;
  while(TRUE) { /* scan string */
    CSecString line;
    int p = s.Find(L"\n");
    if (p < 0) {
      line = s;
    } else { /* one line */
      line = s.Left(p);
      s = s.Mid(p + 1);
    } /* one line */
    dc.TextOut(r.left, y, line);
    y += tm.tmHeight + tm.tmInternalLeading;
    if (p < 0)
      break;
  } /* scan string */
  // Do not call CWnd::OnPaint() for painting messages
}