LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static BOOL  bNeedSave ;
     static DRUM  drum ;
     static HMENU hMenu ;
     static int   iTempo = 50, iIndexLast ;
     static TCHAR szFileName  [MAX_PATH], szTitleName [MAX_PATH] ;
     HDC          hdc ;
     int          i, x, y ;
     PAINTSTRUCT  ps ;
     POINT        point ;
     RECT         rect ;
     TCHAR      * szError ;
     
     switch (message)
     {
     case WM_CREATE:
               // Initialize DRUM structure
          
          drum.iMsecPerBeat = 100 ;
          drum.iVelocity    =  64 ;
          drum.iNumBeats    =  32 ;
          
          DrumSetParams (&drum) ;
          
               // Other initialization
          
          cxChar = LOWORD (GetDialogBaseUnits ()) ;
          cyChar = HIWORD (GetDialogBaseUnits ()) ;

          GetWindowRect (hwnd, &rect) ;
          MoveWindow (hwnd, rect.left, rect.top, 
                            77 * cxChar, 29 * cyChar, FALSE) ;
          
          hMenu = GetMenu (hwnd) ;
          
               // Initialize "Volume" scroll bar
          
          SetScrollRange (hwnd, SB_HORZ, 1, 127, FALSE) ;
          SetScrollPos   (hwnd, SB_HORZ, drum.iVelocity, TRUE) ;
          
               // Initialize "Tempo" scroll bar
          
          SetScrollRange (hwnd, SB_VERT, 0, 100, FALSE) ;
          SetScrollPos   (hwnd, SB_VERT, iTempo, TRUE) ;
          
          DoCaption (hwnd, szTitleName) ;
          return 0 ;
          
     case WM_COMMAND:
          switch (LOWORD (wParam))
          {
          case IDM_FILE_NEW:
               if (bNeedSave && IDCANCEL == AskAboutSave (hwnd, szTitleName))
                    return 0 ;
               
                    // Clear drum pattern
               
               for (i = 0 ; i < NUM_PERC ; i++)
               {
                    drum.dwSeqPerc [i] = 0 ;
                    drum.dwSeqPian [i] = 0 ;
               }
               
               InvalidateRect (hwnd, NULL, FALSE) ;
               DrumSetParams (&drum) ;
               bNeedSave = FALSE ;
               return 0 ;
               
          case IDM_FILE_OPEN:
                    // Save previous file
               
               if (bNeedSave && IDCANCEL ==
                    AskAboutSave (hwnd, szTitleName))
                    return 0 ;
               
                    // Open the selected file
               
               if (DrumFileOpenDlg (hwnd, szFileName, szTitleName))
               {
                    szError = DrumFileRead (&drum, szFileName) ;
                    
                    if (szError != NULL)
                    {
                         ErrorMessage (hwnd, szError, szTitleName) ;
                         szTitleName [0] = '\0' ;
                    }
                    else
                    {
                              // Set new parameters
                         
                         iTempo = (int) (50 *
                              (log10 (drum.iMsecPerBeat) - 1)) ;
                         
                         SetScrollPos (hwnd, SB_VERT, iTempo, TRUE) ;
                         SetScrollPos (hwnd, SB_HORZ, drum.iVelocity, TRUE) ;
                         
                         DrumSetParams (&drum) ;
                         InvalidateRect (hwnd, NULL, FALSE) ;
                         bNeedSave = FALSE ;
                    }
                    
                    DoCaption (hwnd, szTitleName) ;
               }
               return 0 ;
               
          case IDM_FILE_SAVE:
          case IDM_FILE_SAVE_AS:
                    // Save the selected file
               
               if ((LOWORD (wParam) == IDM_FILE_SAVE && szTitleName [0]) ||
                         DrumFileSaveDlg (hwnd, szFileName, szTitleName))
               {
                    szError = DrumFileWrite (&drum, szFileName) ;
                    
                    if (szError != NULL)
                    {
                         ErrorMessage (hwnd, szError, szTitleName) ;
                         szTitleName [0] = '\0' ;
                    }
                    else
                         bNeedSave = FALSE ;
                    
                    DoCaption (hwnd, szTitleName) ;
               }
               return 0 ;
               
          case IDM_APP_EXIT:
               SendMessage (hwnd, WM_SYSCOMMAND, SC_CLOSE, 0L) ;
               return 0 ;
               
          case IDM_SEQUENCE_RUNNING:
                    // Begin sequence
               
               if (!DrumBeginSequence (hwnd))
               {
                    ErrorMessage (hwnd,
                         TEXT ("Could not start MIDI sequence -- ")
                         TEXT ("MIDI Mapper device is unavailable!"),
                         szTitleName) ;
               }
               else
               {
                    CheckMenuItem (hMenu, IDM_SEQUENCE_RUNNING,   MF_CHECKED) ;
                    CheckMenuItem (hMenu, IDM_SEQUENCE_STOPPED, MF_UNCHECKED) ;
               }
               return 0 ;
               
          case IDM_SEQUENCE_STOPPED:
                    // Finish at end of sequence
               
               DrumEndSequence (FALSE) ;
               return 0 ;
               
          case IDM_APP_ABOUT:
               DialogBox (hInst, TEXT ("AboutBox"), hwnd, AboutProc) ;
               return 0 ;
          }
          return 0 ;
                    
     case WM_LBUTTONDOWN:
     case WM_RBUTTONDOWN:
          hdc = GetDC (hwnd) ;
          
               // Convert mouse coordinates to grid coordinates
          
          x =     LOWORD (lParam) / cxChar - 40 ;
          y = 2 * HIWORD (lParam) / cyChar -  2 ;
          
               // Set a new number of beats of sequence
          
          if (x > 0 && x <= 32 && y < 0)
          {
               SetTextColor (hdc, RGB (255, 255, 255)) ;
               TextOut (hdc, (40 + drum.iNumBeats) * cxChar, 0, TEXT (":|"), 2);
               SetTextColor (hdc, RGB (0, 0, 0)) ;
               
               if (drum.iNumBeats % 4 == 0)
                    TextOut (hdc, (40 + drum.iNumBeats) * cxChar, 0,
                             TEXT ("."), 1) ;
               
               drum.iNumBeats = x ;
               
               TextOut (hdc, (40 + drum.iNumBeats) * cxChar, 0, TEXT (":|"), 2);
               
               bNeedSave = TRUE ;
          }
          
               // Set or reset a percussion instrument beat
          
          if (x >= 0 && x < 32 && y >= 0 && y < NUM_PERC)
          {
               if (message == WM_LBUTTONDOWN)
                    drum.dwSeqPerc[y] ^= (1 << x) ;
               else
                    drum.dwSeqPian[y] ^= (1 << x) ;
               
               DrawRectangle (hdc, x, y, drum.dwSeqPerc, drum.dwSeqPian) ;
               
               bNeedSave = TRUE ;
          }
          
          ReleaseDC (hwnd, hdc) ;
          DrumSetParams (&drum) ;
          return 0 ;
          
     case WM_HSCROLL:
               // Change the note velocity
          
          switch (LOWORD (wParam))
          {
          case SB_LINEUP:         drum.iVelocity -= 1 ;  break ;
          case SB_LINEDOWN:       drum.iVelocity += 1 ;  break ;
          case SB_PAGEUP:         drum.iVelocity -= 8 ;  break ;
          case SB_PAGEDOWN:       drum.iVelocity += 8 ;  break ;
          case SB_THUMBPOSITION:
               drum.iVelocity = HIWORD (wParam) ;
               break ;
               
          default:
               return 0 ;
          }
          
          drum.iVelocity = max (1, min (drum.iVelocity, 127)) ;
          SetScrollPos (hwnd, SB_HORZ, drum.iVelocity, TRUE) ;
          DrumSetParams (&drum) ;
          bNeedSave = TRUE ;
          return 0 ;
     
     case WM_VSCROLL:
               // Change the tempo
          
          switch (LOWORD (wParam))
          {
          case SB_LINEUP:         iTempo -=  1 ;  break ;
          case SB_LINEDOWN:       iTempo +=  1 ;  break ;
          case SB_PAGEUP:         iTempo -= 10 ;  break ;
          case SB_PAGEDOWN:       iTempo += 10 ;  break ;
          case SB_THUMBPOSITION:
               iTempo = HIWORD (wParam) ;
               break ;
               
          default:
               return 0 ;
          }
          
          iTempo = max (0, min (iTempo, 100)) ;
          SetScrollPos (hwnd, SB_VERT, iTempo, TRUE) ;
          
          drum.iMsecPerBeat = (WORD) (10 * pow (100, iTempo / 100.0)) ;
          
          DrumSetParams (&drum) ;
          bNeedSave = TRUE ;
          return 0 ;
     
     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;
          
          SetTextAlign (hdc, TA_UPDATECP) ;
          SetBkMode (hdc, TRANSPARENT) ;
          
               // Draw the text strings and horizontal lines
          
          for (i = 0 ; i < NUM_PERC ; i++)
          {
               MoveToEx (hdc, i & 1 ? 20 * cxChar : cxChar,
                             (2 * i + 3) * cyChar / 4, NULL) ;
               
               TextOut (hdc, 0, 0, szPerc [i], lstrlen (szPerc [i])) ;
               
               GetCurrentPositionEx (hdc, &point) ;
               
               MoveToEx (hdc,  point.x + cxChar, point.y + cyChar / 2, NULL) ;
               LineTo   (hdc,       39 * cxChar, point.y + cyChar / 2) ;
          }
          
          SetTextAlign (hdc, 0) ;
          
               // Draw rectangular grid, repeat mark, and beat marks
          
          for (x = 0 ; x < 32 ; x++)
          {
               for (y = 0 ; y < NUM_PERC ; y++)
                    DrawRectangle (hdc, x, y, drum.dwSeqPerc, drum.dwSeqPian) ;
               
               SetTextColor (hdc, x == drum.iNumBeats - 1 ?
                                   RGB (0, 0, 0) : RGB (255, 255, 255)) ;
               
               TextOut (hdc, (41 + x) * cxChar, 0, TEXT (":|"), 2) ;
               
               SetTextColor (hdc, RGB (0, 0, 0)) ;
               
               if (x % 4 == 0)
                    TextOut (hdc, (40 + x) * cxChar, 0, TEXT ("."), 1) ;
          }
          
          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_USER_NOTIFY:
               // Draw the "bouncing ball"
          
          hdc = GetDC (hwnd) ;
          
          SelectObject (hdc, GetStockObject (NULL_PEN)) ;
          SelectObject (hdc, GetStockObject (WHITE_BRUSH)) ;
          
          for (i = 0 ; i < 2 ; i++)
          {
               x = iIndexLast ;
               y = NUM_PERC + 1 ;
               
               Ellipse (hdc, (x + 40) * cxChar, (2 * y + 3) * cyChar / 4,
                    (x + 41) * cxChar, (2 * y + 5) * cyChar / 4);
               
               iIndexLast = wParam ;
               SelectObject (hdc, GetStockObject (BLACK_BRUSH)) ;
          }
          
          ReleaseDC (hwnd, hdc) ;
          return 0 ;
          
     case WM_USER_ERROR:
          ErrorMessage (hwnd, TEXT ("Can't set timer event for tempo"),
                        szTitleName) ;
          
                                             // fall through
     case WM_USER_FINISHED:
          DrumEndSequence (TRUE) ;
          CheckMenuItem (hMenu, IDM_SEQUENCE_RUNNING,   MF_UNCHECKED) ;
          CheckMenuItem (hMenu, IDM_SEQUENCE_STOPPED, MF_CHECKED) ;
          return 0 ;
          
     case WM_CLOSE:
          if (!bNeedSave || IDCANCEL != AskAboutSave (hwnd, szTitleName))
               DestroyWindow (hwnd) ;
          
          return 0 ;
          
     case WM_QUERYENDSESSION:
          if (!bNeedSave || IDCANCEL != AskAboutSave (hwnd, szTitleName))
               return 1L ;
          
          return 0 ;
          
     case WM_DESTROY:
          DrumEndSequence (TRUE) ;
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}