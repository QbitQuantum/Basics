LRESULT CALLBACK FrameProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
   switch(Message)
   {
      case WM_HSCROLL:{
        int xDelta;
        int xNewPos;
        int yDelta = 0;

        switch (LOWORD(wParam)) {
            /* User clicked the shaft left of the scroll box. */
            case SB_PAGEUP:
                xNewPos = xCurrentScroll - xPageScroll;
                break;
            /* User clicked the shaft right of the scroll box. */
            case SB_PAGEDOWN:
                xNewPos = xCurrentScroll + xPageScroll;
                break;
            /* User clicked the left arrow. */
            case SB_LINEUP:
                xNewPos = xCurrentScroll - xIncrementScroll;
                break;
            /* User clicked the right arrow. */
            case SB_LINEDOWN:
                xNewPos = xCurrentScroll + xIncrementScroll;
                break;
            /* User dragged or is dragging the scroll box. */
            case SB_THUMBPOSITION:
            case SB_THUMBTRACK:
                xNewPos = HIWORD(wParam);
                break;
            default:
                xNewPos = xCurrentScroll;
        }
        /* New position must be between 0 and the screen width. */
        xNewPos = max(0, xNewPos);
        xNewPos = min(xMaxScroll, xNewPos);

        /* If the current position does not change, do not scroll.*/
        if (xNewPos == xCurrentScroll)
            break;

        /* Determine the amount scrolled (in pixels). */
        xDelta = (xNewPos - xCurrentScroll)*xPixelsPerIncrement;
                           //(-) is hit left, scroll right
        /* Reset the current scroll position. */
        xCurrentScroll = xNewPos;

        ScrollDC(hdcMemoryTheMap,-xDelta,-yDelta,NULL,NULL,NULL,NULL);
        MapPositionX=xCurrentScroll;
        if (xDelta>0)    //hit right, scroll left
          RenderScreen(hwnd,max(0,(TheMapWidth-xDelta)),0,TheMapWidth,TheMapHeight);
        else   //hit left, scroll right
          RenderScreen(hwnd,0,0,min(TheMapWidth,-xDelta),TheMapHeight);
        ScrollWindowEx(hwnd, -xDelta, -yDelta, &TheWindowRect,
            &TheWindowRect, (HRGN) NULL, (LPRECT) NULL,
            SW_INVALIDATE);
//             InvalidateRect(hwnd,&TheWindowRect,false);
        UpdateWindow(hwnd);
        ResetScrollBarX(hwnd);
      }
      break;

      case WM_VSCROLL:{
        int xDelta=0;
        int yNewPos;
        int yDelta;

        switch (LOWORD(wParam)) {
            /* User clicked the shaft above scroll box. */
            case SB_PAGEUP:
                yNewPos = yCurrentScroll - yPageScroll;
                break;
            /* User clicked the shaft below the scroll box. */
            case SB_PAGEDOWN:
                yNewPos = yCurrentScroll + yPageScroll;
                break;
            /* User clicked the up arrow. */
            case SB_LINEUP:
                yNewPos = yCurrentScroll - yIncrementScroll;
                break;
            /* User clicked the down arrow. */
            case SB_LINEDOWN:
                yNewPos = yCurrentScroll + yIncrementScroll;
                break;
            /* User dragged or is dragging the scroll box. */
            case SB_THUMBPOSITION:
            case SB_THUMBTRACK:
                yNewPos = HIWORD(wParam);
                break;
            default:
                yNewPos = yCurrentScroll;
        }
        /* New position must be between 0 and the screen height. */
        yNewPos = max(0, yNewPos);
        yNewPos = min(yMaxScroll, yNewPos);

        /* If the current position does not change, do not scroll.*/
        if (yNewPos == yCurrentScroll)
            break;

        /* Determine the amount scrolled (in pixels). */
        yDelta = (yNewPos - yCurrentScroll)*yPixelsPerIncrement;
                           //(-) is hit up, scroll down
        /* Reset the current scroll position. */
        yCurrentScroll = yNewPos;

        ScrollDC(hdcMemoryTheMap,-xDelta,-yDelta,NULL,NULL,NULL,NULL);
        MapPositionY=yCurrentScroll;
        if (yDelta>0)    //hit down, scroll up
          RenderScreen(hwnd,0,max(0,(TheMapHeight-yDelta)),TheMapWidth,TheMapHeight);
        else   //hit up, scroll down
          RenderScreen(hwnd,0,0,TheMapWidth,min(TheMapHeight,-yDelta));

        ScrollWindowEx(hwnd, -xDelta, -yDelta, &TheWindowRect,
            &TheWindowRect, (HRGN) NULL, (LPRECT) NULL,
            SW_INVALIDATE);
        UpdateWindow(hwnd);
        ResetScrollBarY(hwnd);
      }
      break;
      case WM_COMMAND:
          MainWindowCommand(hwnd,LOWORD(wParam));
          break;
      case WM_ERASEBKGND:
          if (MapLoaded)
               return 1;   //don't erase background if we have the map loaded
          return DefWindowProc(hwnd, Message, wParam, lParam);
      case WM_PAINT:
         PAINTSTRUCT ps;
         HDC hdcWindow;
         hdcWindow = BeginPaint(hwnd, &ps);

         if (!TheMapBitmap)
         {
            CreateMainBitmapX(hwnd);
            RenderFullScreen(hwnd);
         }
         DisplayFullScreen2(hdcWindow);

         EndPaint(hwnd, &ps);
         break;

      case WM_SIZE:
         //Adjust our bitmap to fit window
         if ((wParam==SIZE_MAXIMIZED)||(wParam==SIZE_RESTORED))
            AdjustScreenSize(hwnd,LOWORD(lParam),HIWORD(lParam));
         break;
      case WM_CREATE:
         CreateMainMenu(hwnd);
         break;
      case WM_CLOSE:
         DestroyWindow(hwnd);
         break;
      case WM_DESTROY:
         FreeAllData();
         if (hdcMemoryTheMap)
            DeleteDC(hdcMemoryTheMap);
         if (TheMapBitmap)
            DeleteObject(TheMapBitmap);
         PostQuitMessage(0);
         break;
      default: return DefWindowProc(hwnd, Message, wParam, lParam);
   }
   return 0;
}