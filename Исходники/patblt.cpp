LRESULT CALLBACK MainWndProc(HWND HWnd, UINT Msg, WPARAM WParam,
   LPARAM LParam)
{
   switch (Msg)
   {
      case WM_CREATE:
      {
         // create a memory DC
         HMemDC = CreateCompatibleDC(NULL);
         if (HMemDC)
         {
            // load the penguin bitmap
            HBITMAP HBmp = static_cast<HBITMAP>(
               LoadImage(HInst, filename, IMAGE_BITMAP, 0, 0,
                         LR_LOADFROMFILE | LR_DEFAULTSIZE)
               );
            if (HBmp)
            {
               // get the bitmap's dimensions
               BITMAP bmp;
               if (GetObject(HBmp, sizeof(BITMAP), &bmp))
               {
                  RImage.right += bmp.bmWidth;
                  RImage.bottom += bmp.bmHeight;

                  // realize the bitmap
                  HOldBmp = static_cast<HBITMAP>(
                     SelectObject(HMemDC, HBmp)
                     );
               }
               else DeleteObject(HBmp);
            }
         }
         break;
      }
      case WM_LBUTTONDOWN:
      {
         PMouse.x = LOWORD(LParam);
         PMouse.y = HIWORD(LParam);

         RECT RClient;
         if (PtInRect(&RImage, PMouse) &&
             GetClientRect(HWnd, &RClient))
         {
            MapRect(HWnd, HWND_DESKTOP, RClient);
            ClipCursor(&RClient);

            // grab a handle to the screen DC and clip
            // all output to the client area of our window
            HScreenDC = GetDC(NULL);
            HRGN HClipRgn = CreateRectRgnIndirect(&RClient);
            SelectClipRgn(HScreenDC, HClipRgn);
            DeleteObject(HClipRgn);

            CopyRect(&RTrack, &RImage);
            MapRect(HWnd, HWND_DESKTOP, RTrack);

            // render the first tracking rect
            RenderTrackingRect(HScreenDC, RTrack);
            is_tracking = true;
         }
         break;
      }
      case WM_MOUSEMOVE:
      {
         if (HScreenDC && is_tracking)
         {
            POINT PCurrent = {LOWORD(LParam), HIWORD(LParam)};
            const int dX = PCurrent.x - PMouse.x;
            const int dY = PCurrent.y - PMouse.y;

            // erase the previous rectangle
            RenderTrackingRect(HScreenDC, RTrack);
            // update the postion
            OffsetRect(&RTrack, dX, dY);
            // render the new tracking rectangle
            RenderTrackingRect(HScreenDC, RTrack);

            // update the mouse position
            memcpy(&PMouse, &PCurrent, sizeof(POINT));
         }
         break;
      }
      case WM_LBUTTONUP:
      {
         // clean up
         if (is_tracking)
         {
            is_tracking = false;
            SelectClipRgn(HScreenDC, NULL);
            ReleaseDC(NULL, HScreenDC);

            InvalidateRect(HWnd, &RImage, true);
            CopyRect(&RImage, &RTrack);
            MapRect(HWND_DESKTOP, HWnd, RImage);
            InvalidateRect(HWnd, &RImage, true);

            ClipCursor(NULL);
         }
         break;
      }
      case WM_PAINT:
      {
         PAINTSTRUCT ps;
         HDC Hdc = BeginPaint(HWnd, &ps);
         try
         {
            //
            // TODO: Add palette support...
            //

            // render the penguin
            BitBlt(Hdc, RImage.left, RImage.top,
                   RImage.right - RImage.left,
                   RImage.bottom - RImage.top,
                   HMemDC, 0, 0,
                   SRCCOPY);
         }
         catch (...)
         {
            EndPaint(HWnd, &ps);
         }
         EndPaint(HWnd, &ps);
         break;
      }
      case WM_DESTROY:
      {
         // clean up
         if (HOldBmp)
         {
            DeleteObject(SelectObject(HMemDC, HOldBmp));
         }
         if (HMemDC)
         {
            DeleteDC(HMemDC);
         }
         PostQuitMessage(0);
         return 0;
      }
   }
   return DefWindowProc(HWnd, Msg, WParam, LParam);
}