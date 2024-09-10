LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam,
   LPARAM lParam)
{
   switch (msg)
   {
      case WM_CREATE:
      {
         INITCOMMONCONTROLSEX icx;
         icx.dwSize = sizeof(INITCOMMONCONTROLSEX);
         icx.dwICC = ICC_BAR_CLASSES;

         InitCommonControlsEx(&icx);

         hTrackBar =
            CreateWindow(
               TRACKBAR_CLASS, "",
               TBS_HORZ | TBS_BOTH | TBS_AUTOTICKS |
               TBS_FIXEDLENGTH | TBS_ENABLESELRANGE |
               WS_CHILD | WS_VISIBLE,
               10, 260, 375, 40,
               hWnd, NULL, hInst, NULL
               );

         assert(hTrackBar != NULL);
         SNDMSG(hTrackBar, TBM_SETTHUMBLENGTH, 20, 0);
         SNDMSG(hTrackBar, TBM_SETRANGEMAX, TRUE, 100);

         // create the TrueType (scalable) font
         HDC hDC = GetDC(hWnd);
         try
         {
            // see Chapter 4 for the definition of MakeFont
            hTTFont = font::MakeFont(hDC, "Impact", 72);
            if (!hTTFont) throw;
         }
         catch (...)
         {
            ReleaseDC(hWnd, hDC);
         }
         ReleaseDC(hWnd, hDC);
         break;
      }
      case WM_HSCROLL:
      {
         if (reinterpret_cast<HWND>(lParam) == hTrackBar)
         {
            //
            // adjust the scaling factor according to
            // the position of the trackbar's slider
            //
            scale = static_cast<double>(
               (SNDMSG(hTrackBar, TBM_GETPOS, 0, 0) + 1) / 50.0
               );
            InvalidateRect(hWnd, NULL, true);
         }
         break;
      }
      case WM_ERASEBKGND:
      {
         LRESULT res = DefWindowProc(hWnd, msg, wParam, lParam);

         HDC hDC = reinterpret_cast<HDC>(wParam);
         HFONT hOldFont = static_cast<HFONT>(
            SelectObject(hDC, hTTFont)
            );
         try
         {
            SetBkMode(hDC, TRANSPARENT);

            // open a path bracket
            if (!BeginPath(hDC)) throw;

            // record the text to the path
            TextOut(hDC, 10, 10, pText, lstrlen(pText));

            // close the path bracket and
            // select the path into hDC
            EndPath(hDC);

            // determine the number of endpoints in the path
            const int num_points = GetPath(hDC, NULL, NULL, 0);
            if (num_points > 0)
            {
               // make room for the POINTs and vertex types
               POINT* pPEnds = new POINT[num_points];
               unsigned char* pTypes = new unsigned char[num_points];
               try
               {
                  // get the path's description
                  int num_got = GetPath(hDC, pPEnds, pTypes, num_points);
                  if (num_got > 0)
                  {
                     // start a new path bracket
                     if (!BeginPath(hDC)) throw;

                     // scale each point in the description
                     int iPoint;
                     for (iPoint = 0; iPoint < num_got; ++iPoint)
                     {
                        pPEnds[iPoint].x = static_cast<LONG>(
                           scale * pPEnds[iPoint].x + 0.5
                           );
                        pPEnds[iPoint].y = static_cast<LONG>(
                           scale * pPEnds[iPoint].y + 0.5
                           );
                     }

                     for (iPoint = 0; iPoint < num_points; ++iPoint)
                     {
                        // handle the MoveToEx case
                        if (pTypes[iPoint] == PT_MOVETO)
                        {
                           MoveToEx(
                             hDC, pPEnds[iPoint].x, pPEnds[iPoint].y, NULL
                             );
                        }
                        // handle the LineTo case
                        else if (
                           pTypes[iPoint] == PT_LINETO ||
                           pTypes[iPoint] == (PT_LINETO | PT_CLOSEFIGURE)
                           )
                        {
                           LineTo(hDC, pPEnds[iPoint].x, pPEnds[iPoint].y);
                        }
                        // handle the PolyBezierTo case
                        else if (
                           pTypes[iPoint] == PT_BEZIERTO ||
                           pTypes[iPoint] == (PT_BEZIERTO | PT_CLOSEFIGURE)
                           )
                        {
                           PolyBezierTo(hDC, pPEnds + iPoint, 3);
                           iPoint += 2;
                        }
                     }

                     // close the new path bracket
                     EndPath(hDC);

                     // stroke and fill the new path
                     StrokeAndFillPath(hDC);
                  }
               }
               catch (...)
               {
                  // clean up
                  delete [] pTypes;
                  delete [] pPEnds;
                  throw;
               }
               // clean up
               delete [] pTypes;
               delete [] pPEnds;
            }
            // ...
         }
         catch (...)
         {
            SelectObject(hDC, hOldFont);
         }
         SelectObject(hDC, hOldFont);
         return res;
      }
      case WM_SIZE:
      {
         MoveWindow(
            hTrackBar,
            0, HIWORD(lParam) - 40, LOWORD(lParam), 40,
            false
            );
         break;
      }
      case WM_DESTROY:
      {
         // clean up
         DeleteObject(hTTFont);
         PostQuitMessage(0);
         break;
      }
   }
   return DefWindowProc(hWnd, msg, wParam, lParam);
}