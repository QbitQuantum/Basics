LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static PTSTR pText ;
     BOOL         bEnable ;
     HGLOBAL      hGlobal ;
     HDC          hdc ;
     PTSTR        pGlobal ;
     PAINTSTRUCT  ps ;
     RECT         rect ;
     
     switch (message)
     {
     case WM_CREATE:
          SendMessage (hwnd, WM_COMMAND, IDM_EDIT_RESET, 0) ;
          return 0 ;

    case WM_INITMENUPOPUP:
          EnableMenuItem ((HMENU) wParam, IDM_EDIT_PASTE,
               IsClipboardFormatAvailable (CF_TCHAR) ? MF_ENABLED : MF_GRAYED) ;

          bEnable = pText ? MF_ENABLED : MF_GRAYED ;

          EnableMenuItem ((HMENU) wParam, IDM_EDIT_CUT,   bEnable) ;
          EnableMenuItem ((HMENU) wParam, IDM_EDIT_COPY,  bEnable) ;
          EnableMenuItem ((HMENU) wParam, IDM_EDIT_CLEAR, bEnable) ;
          break ;
          
     case WM_COMMAND:
          switch (LOWORD (wParam))
          {
          case IDM_EDIT_PASTE:
               OpenClipboard (hwnd) ;

               if (hGlobal = GetClipboardData (CF_TCHAR))
               {
                    pGlobal = GlobalLock (hGlobal) ;

                    if (pText)
                    {
                         free (pText) ;
                         pText = NULL ;
                    }
                    pText = malloc (GlobalSize (hGlobal)) ;
                    lstrcpy (pText, pGlobal) ;
                    InvalidateRect (hwnd, NULL, TRUE) ;
               }
               CloseClipboard () ;
               return 0 ;

          case IDM_EDIT_CUT:
          case IDM_EDIT_COPY:
               if (!pText)
                    return 0 ;

               hGlobal = GlobalAlloc (GHND | GMEM_SHARE, 
                                      (lstrlen (pText) + 1) * sizeof (TCHAR)) ;
               pGlobal = GlobalLock (hGlobal) ;
               lstrcpy (pGlobal, pText) ;
               GlobalUnlock (hGlobal) ;

               OpenClipboard (hwnd) ;
               EmptyClipboard () ;
               SetClipboardData (CF_TCHAR, hGlobal) ;
               CloseClipboard () ;

               if (LOWORD (wParam) == IDM_EDIT_COPY)
                    return 0 ;        
                                             // fall through for IDM_EDIT_CUT
          case IDM_EDIT_CLEAR:
               if (pText)
               {
                    free (pText) ;
                    pText = NULL ;
               }
               InvalidateRect (hwnd, NULL, TRUE) ;
               return 0 ;

          case IDM_EDIT_RESET:
               if (pText)
               {
                    free (pText) ;
                    pText = NULL ;
               }

               pText = malloc ((lstrlen (szDefaultText) + 1) * sizeof (TCHAR)) ;
               lstrcpy (pText, szDefaultText) ;
               InvalidateRect (hwnd, NULL, TRUE) ;
               return 0 ;
          }
          break ;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;

          GetClientRect (hwnd, &rect) ;
          
          if (pText != NULL)
               DrawText (hdc, pText, -1, &rect, DT_EXPANDTABS | DT_WORDBREAK) ;

          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY:
          if (pText)
               free (pText) ;

          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}