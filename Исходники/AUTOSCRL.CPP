void CAutoScrollView::AutoScroll(UINT nRefMessage)
   {
   MSG   msg;             // dummmy message structure to process incoming
   // messages while autoscrolling.
   CPoint ptScrollPos,    // Current scroll position - logical units
   ptDevScrollPos, // Current scroll position - device units
   ptCursorPos;    // Current mouse cursor position
   CRect  rc; 			  // Client area
   long   dx, dy;         // Scrolling increment
   SIZE   sizeTotal,      // CScrollView scroll data
   sizePage,
   sizeLine;
   int    nMapMode,       // Mapping mode
   nMapFactor,     // Accounts for mapping mode
   xMin, xMax,
   yMin, yMax;   // Scroll range
   
   if (!m_bAutoScroll)
   return;
   
   msg.message = 0;   // forces at least one loop.
   SetCapture();
   GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);
   
   // We keep track of the scroll range because CScrollView::ScrollToPosition always
   // try to scroll even if the scroll limit has been reached. This results in screen
   // flickering when ScrollWindow is called.
   GetScrollRange(SB_HORZ, &xMin, &xMax);
   GetScrollRange(SB_VERT, &yMin, &yMax);
   
   // Process all messages until the relevant mouse button
   // has been released. nRefMessage depends on which button
   // has been used to trigger autoscrolling.
   //   while (msg.message != nRefMessage)
   BOOL bSawRefMessage = FALSE;
   
   while (!bSawRefMessage)
      {
      // Process incoming messages until autoscroll button is released
      
      // You cannot peek here because it may process an invalidate
      // due to the scrolling.
      
      /*
      if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
         {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
         }
      */
      
      ptScrollPos = GetScrollPosition();
      ptDevScrollPos = GetDeviceScrollPosition();
      GetCursorPos(&ptCursorPos);
      ScreenToClient(&ptCursorPos);
      GetClientRect(&rc);
      dx = 0L;
      dy = 0L;
      
      if ((ptCursorPos.y < 0) && (ptDevScrollPos.y != yMin))
      // Cursor is above client area
      dy = min(-sizeLine.cy, max(-sizePage.cy, (ptCursorPos.y/10) * sizeLine.cy));
      else if ((ptCursorPos.y > rc.bottom) &&  (ptDevScrollPos.y != yMax))
      // Cursor is below client area
      dy = max(sizeLine.cy, min(sizePage.cy, ((ptCursorPos.y - rc.bottom)/10) * sizeLine.cy));
      // otherwise we can't scroll anyway
      
      if ((ptCursorPos.x < 0) && (ptDevScrollPos.x != xMin))
      // Cursor is on the left of the client area
      dx = min(-sizeLine.cx, max(-sizePage.cx, (ptCursorPos.x/10) * sizeLine.cx));
      else if ((ptCursorPos.x > rc.right) && (ptDevScrollPos.x != xMax))
      // Cursor is on the right of the client area
      dx = max(sizeLine.cx, min(sizePage.cx, ((ptCursorPos.x - rc.right)/10) * sizeLine.cx));
      // otherwise we can't scroll anyway
      
      // if mouse cursor is dragging outside the client area, scrolling occurs
      if ((dx != 0) || (dy != 0))
         {
         // Flip the Y coordinate if we're not in MM_TEXT
         nMapFactor = (nMapMode == MM_TEXT) ? 1 : -1;
         ptScrollPos.y += (int) dy * nMapFactor;
         ptScrollPos.x += (int) dx;
         m_bIsScrolling = TRUE;
         OnAutoScroll(ptCursorPos, TRUE);
         ScrollToPosition(ptScrollPos);
         
         while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            
            //            if (msg.message == nRefMessage) break;
            if (msg.message == nRefMessage) bSawRefMessage = TRUE;
            }
         
         //         if (!bSawRefMessage)
         OnAutoScroll(ptCursorPos, FALSE);
         }
      else
         {
         
         while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            
            //            if (msg.message == nRefMessage) break;
            if (msg.message == nRefMessage) bSawRefMessage = TRUE;
            }
         
         m_bIsScrolling = FALSE;
         }
      }
   ReleaseCapture();
   m_bIsScrolling = FALSE;
   }