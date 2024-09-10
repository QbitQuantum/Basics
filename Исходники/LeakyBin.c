//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  MESSAGES:
//
// WM_COMMAND - process the application menu
// WM_PAINT - Paint the main window
// WM_DESTROY - post a quit message and return
//    WM_DISPLAYCHANGE - message sent to Plug & Play systems when the display changes
//    WM_RBUTTONDOWN - Right mouse click -- put up context menu here if appropriate
//    WM_NCRBUTTONUP - User has clicked the right button on the application's system menu
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   int wmId, wmEvent;
   PAINTSTRUCT ps;
   HDC hdc;
   POINT pnt;
   HMENU hMenu;
   BOOL bGotHelp;

   switch (message)
   {
   case WM_CREATE:
      // clear timer flags
      TimerID = 0;
      TimerRunning = FALSE;

      // enable "Start" menu selection
      hAppMenu = GetMenu (hWnd);
      hTestMenu  = GetSubMenu (hAppMenu, 1);
      EnableMenuItem (hTestMenu, IDM_STOP, MF_BYCOMMAND | MF_GRAYED);
      EnableMenuItem (hTestMenu, IDM_START, MF_BYCOMMAND | MF_ENABLED);
      break;

   case WM_COMMAND:
      wmId    = LOWORD(wParam); // Remember, these are...
      wmEvent = HIWORD(wParam); // ...different for Win32!

      //Parse the menu selections:
      switch (wmId)
      {

      case IDM_EXIT:
         DestroyWindow (hWnd);
         break;

      case IDM_START:
         if (!TimerRunning)
         {
            TimerID = SetTimer (hWnd, LEAK_TIMER, TIME_INTERVAL, NULL);
            if (TimerID != 0)
            {
               TimerRunning = TRUE;
               EnableMenuItem (hTestMenu, IDM_START,
                               MF_BYCOMMAND | MF_GRAYED);
               EnableMenuItem (hTestMenu, IDM_STOP,
                               MF_BYCOMMAND | MF_ENABLED);
            }
            else
            {
               //unable to start timer
               MessageBeep (MB_ICONEXCLAMATION);
            }
         }
         InvalidateRect (hWnd, NULL, TRUE);
         break;

      case IDM_STOP:
         if (TimerRunning)
         {
            KillTimer (hWnd, LEAK_TIMER);
            TimerID = 0;
            TimerRunning = FALSE;
            EnableMenuItem (hTestMenu, IDM_STOP,
                            MF_BYCOMMAND | MF_GRAYED);
            EnableMenuItem (hTestMenu, IDM_START,
                            MF_BYCOMMAND | MF_ENABLED);
         }
         InvalidateRect (hWnd, NULL, TRUE);
         break;

      case IDM_RESET:
         FreeAllocatedMemory();
         InvalidateRect (hWnd, NULL, TRUE);
         break;

      case IDM_ABOUT:
         DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About);
         break;

      case IDM_HELPTOPICS: // Only called in Windows 95
         bGotHelp = WinHelp (hWnd, APPNAME".HLP", HELP_FINDER,(DWORD)0);
         if (!bGotHelp)
         {
            MessageBox (GetFocus(), GetStringRes(IDS_NO_HELP),
                        szAppName, MB_OK|MB_ICONHAND);
         }
         break;

      default:
         return (DefWindowProc(hWnd, message, wParam, lParam));
      }
      break;

   case WM_TIMER:
      {
         PMEMORY_ALLOC_BLOCK     pMab, pNewMab;

         pNewMab = (PMEMORY_ALLOC_BLOCK)G_ALLOC (GPTR, ALLOCATION_SIZE);

         if (pNewMab != NULL)
         {
            // save this pointer
            pNewMab->pNext = NULL;
            if (mabListHead.pNext == NULL)
            {
               // this is the first entry
               mabListHead.pNext = pNewMab;
            }
            else
            {
               // go to end of list
               pMab = mabListHead.pNext;
               while (pMab->pNext != NULL) pMab = pMab->pNext;
               pMab->pNext = pNewMab;
            }
            InvalidateRect (hWnd, NULL, TRUE);
         }
      }
      break;

   case WM_RBUTTONDOWN: // RightClick in windows client area...
      pnt.x = LOWORD(lParam);
      pnt.y = HIWORD(lParam);
      ClientToScreen(hWnd, (LPPOINT) &pnt);
      // This is where you would determine the appropriate 'context'
      // menu to bring up. Since this app has no real functionality,
      // we will just bring up the 'Help' menu:
      hMenu = GetSubMenu (GetMenu (hWnd), 2);
      if (hMenu)
      {
         TrackPopupMenu (hMenu, 0, pnt.x, pnt.y, 0, hWnd, NULL);
      }
      else
      {
         // Couldn't find the menu...
         MessageBeep(0);
      }
      break;


   case WM_DISPLAYCHANGE: // Only comes through on plug'n'play systems
      {
         SIZE  szScreen;
         DWORD dwBitsPerPixel = (DWORD)wParam;

         szScreen.cx = LOWORD(lParam);
         szScreen.cy = HIWORD(lParam);

         MessageBox (GetFocus(), GetStringRes(IDS_DISPLAYCHANGED),
                     szAppName, 0);
      }
      break;

   case WM_PAINT:
      {
         MEMORYSTATUS    MemoryStatusData;
         LONGLONG            llInUse;
         DWORD                   dwPercentUsed;

         int     nX, nY;
         LONG    lTextOutReturn;
         int     nStringLength;
         CHAR            szOutputString[100];

         hdc = BeginPaint (hWnd, &ps);
         // Add any drawing code here...
         GlobalMemoryStatus (& MemoryStatusData);

         llInUse = (LONGLONG)(MemoryStatusData.dwTotalPageFile -
                              MemoryStatusData.dwAvailPageFile + 5 );
         llInUse *= 1000;
         llInUse /= MemoryStatusData.dwTotalPageFile;
         llInUse /= 10;

         dwPercentUsed = (DWORD)llInUse;

         nX = 0;
         nY = 0;
         _snprintf_s(szOutputString, 100, _TRUNCATE, "Reported Memory Load: \t%3.1d%%",
                  MemoryStatusData.dwMemoryLoad);
         nStringLength = lstrlen (szOutputString) * sizeof (CHAR);
         lTextOutReturn = TabbedTextOut (hdc, nX, nY,
                                         szOutputString, nStringLength, 0, NULL, 0);
         nY += HIWORD (lTextOutReturn);

         _snprintf_s(szOutputString, 100, _TRUNCATE, "Page file in use:  \t%3.1d%%",
                  dwPercentUsed);
         nStringLength = lstrlen (szOutputString) * sizeof (CHAR);
         lTextOutReturn = TabbedTextOut(hdc, nX, nY,
                                         szOutputString, nStringLength, 0, NULL, 0);
         nY += HIWORD(lTextOutReturn);

         EndPaint (hWnd, &ps);
      }
      break;

   case WM_DESTROY:
      FreeAllocatedMemory();
      // Tell WinHelp we don't need it any more...
      WinHelp(hWnd, APPNAME".HLP", HELP_QUIT,(DWORD)0);
      PostQuitMessage(0);
      break;

   default:
      return (DefWindowProc(hWnd, message, wParam, lParam));
   }
   return (0);
}