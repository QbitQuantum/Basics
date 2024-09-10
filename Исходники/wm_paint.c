LRESULT CALLBACK MainWndProc(HWND HWnd, UINT Msg, WPARAM WParam,
   LPARAM LParam)
{
  const char* text = "Persistent Text";

   switch (Msg)
   {
      case WM_PAINT:
      {
         // determine the invalidated area of the window
         RECT RUpdate;
         HDC Hdc;
         GetUpdateRect(HWnd, &RUpdate, FALSE);

         // grab a handle to our window's
         // common display device context
         Hdc = GetDC(HWnd);
#if 0
         try
#endif
         {
            RECT RClient;
            GetClientRect(HWnd, &RClient);

            // set the clipping region
            IntersectClipRect(Hdc, RUpdate.left, RUpdate.top,
                              RUpdate.right, RUpdate.bottom);

            // fill the client area with the background brush
            /*HBRUSH HBrush =
               reinterpret_cast<HBRUSH>
                  (HBRUSH)(GetClassLong(HWnd, GCL_HBRBACKGROUND)
                  );*/
            FillRect(Hdc, &RClient, NULL);

            // render the persistent text
            SetTextColor(Hdc, PALETTERGB(0, 0, 255));
            DrawText(Hdc, text, strlen(text), &RClient,
                     DT_CENTER | DT_VCENTER | DT_SINGLELINE);
         }
#if 0
         catch (...)
#endif
         {
            // release the device context
            ReleaseDC(HWnd, Hdc);

            // validate the update area
            ValidateRect(HWnd, &RUpdate);
         }
         // release the device context
         ReleaseDC(HWnd, Hdc);

         // validate the update area
         ValidateRect(HWnd, &RUpdate);

         break;
      }
      case WM_DESTROY:
      {
         PostQuitMessage(0);
         return 0;
      }
   }
   return DefWindowProc(HWnd, Msg, WParam, LParam);
}