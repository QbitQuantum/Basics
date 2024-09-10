LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static BOOL      bNeedSave = FALSE ;
     static HINSTANCE hInst ;
     static HWND      hwndEdit ;
     static int       iOffset ;
     static TCHAR     szFileName[MAX_PATH], szTitleName[MAX_PATH] ;
     static UINT      messageFindReplace ;
     int              iSelBeg, iSelEnd, iEnable ;
     LPFINDREPLACE    pfr ;
     
     switch (message)
     {
     case WM_CREATE:
          hInst = ((LPCREATESTRUCT) lParam) -> hInstance ;
          
               // Create the edit control child window
          
          hwndEdit = CreateWindow (TEXT ("edit"), NULL,
                              WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
                              WS_BORDER | ES_LEFT | ES_MULTILINE |
                              ES_NOHIDESEL | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
                              0, 0, 0, 0,
                              hwnd, (HMENU) EDITID, hInst, NULL) ;
          
          SendMessage (hwndEdit, EM_LIMITTEXT, 32000, 0L) ;
          
               // Initialize common dialog box stuff
          
          PopFileInitialize (hwnd) ;
          PopFontInitialize (hwndEdit) ;
          
          messageFindReplace = RegisterWindowMessage (FINDMSGSTRING) ;
          
          DoCaption (hwnd, szTitleName) ;
          return 0 ;
          
     case WM_SETFOCUS:
          SetFocus (hwndEdit) ;
          return 0 ;
          
     case WM_SIZE: 
          MoveWindow (hwndEdit, 0, 0, LOWORD (lParam), HIWORD (lParam), TRUE) ;
          return 0 ;
          
     case WM_INITMENUPOPUP:
          switch (lParam)
          {
          case 1:             // Edit menu
               
                    // Enable Undo if edit control can do it
               
               EnableMenuItem ((HMENU) wParam, IDM_EDIT_UNDO,
                    SendMessage (hwndEdit, EM_CANUNDO, 0, 0L) ?
                                             MF_ENABLED : MF_GRAYED) ;
               
                    // Enable Paste if text is in the clipboard
               
               EnableMenuItem ((HMENU) wParam, IDM_EDIT_PASTE,
                    IsClipboardFormatAvailable (CF_TEXT) ?
                                             MF_ENABLED : MF_GRAYED) ;
               
                    // Enable Cut, Copy, and Del if text is selected
               
               SendMessage (hwndEdit, EM_GETSEL, (WPARAM) &iSelBeg,
                                                 (LPARAM) &iSelEnd) ;
               
               iEnable = iSelBeg != iSelEnd ? MF_ENABLED : MF_GRAYED ;
               
               EnableMenuItem ((HMENU) wParam, IDM_EDIT_CUT,   iEnable) ;
               EnableMenuItem ((HMENU) wParam, IDM_EDIT_COPY,  iEnable) ;
               EnableMenuItem ((HMENU) wParam, IDM_EDIT_CLEAR, iEnable) ;
               break ;
               
          case 2:             // Search menu
               
               // Enable Find, Next, and Replace if modeless
               //   dialogs are not already active
               
               iEnable = hDlgModeless == NULL ?
                              MF_ENABLED : MF_GRAYED ;
               
               EnableMenuItem ((HMENU) wParam, IDM_SEARCH_FIND,    iEnable) ;
               EnableMenuItem ((HMENU) wParam, IDM_SEARCH_NEXT,    iEnable) ;
               EnableMenuItem ((HMENU) wParam, IDM_SEARCH_REPLACE, iEnable) ;
               break ;
          }
          return 0 ;
     
     case WM_COMMAND:
               // Messages from edit control
          
          if (lParam && LOWORD (wParam) == EDITID)
          {
               switch (HIWORD (wParam))
               {
               case EN_UPDATE :
                    bNeedSave = TRUE ;
                    return 0 ;
                    
               case EN_ERRSPACE :
               case EN_MAXTEXT :
                    MessageBox (hwnd, TEXT ("Edit control out of space."),
                                szAppName, MB_OK | MB_ICONSTOP) ;
                    return 0 ;
               }
               break ;
          }
          
          switch (LOWORD (wParam))
          {
               // Messages from File menu
               
          case IDM_FILE_NEW:
               if (bNeedSave && IDCANCEL == AskAboutSave (hwnd, szTitleName))
                    return 0 ;
               
               SetWindowText (hwndEdit, TEXT ("\0")) ;
               szFileName[0]  = '\0' ;
               szTitleName[0] = '\0' ;
               DoCaption (hwnd, szTitleName) ;
               bNeedSave = FALSE ;
               return 0 ;
               
          case IDM_FILE_OPEN:
               if (bNeedSave && IDCANCEL == AskAboutSave (hwnd, szTitleName))
                    return 0 ;
               
               if (PopFileOpenDlg (hwnd, szFileName, szTitleName))
               {
                    if (!PopFileRead (hwndEdit, szFileName))
                    {
                         OkMessage (hwnd, TEXT ("Could not read file %s!"),
                                    szTitleName) ;
                         szFileName[0]  = '\0' ;
                         szTitleName[0] = '\0' ;
                    }
               }
               
               DoCaption (hwnd, szTitleName) ;
               bNeedSave = FALSE ;
               return 0 ;
               
          case IDM_FILE_SAVE:
               if (szFileName[0])
               {
                    if (PopFileWrite (hwndEdit, szFileName))
                    {
                         bNeedSave = FALSE ;
                         return 1 ;
                    }
                    else
                    {
                         OkMessage (hwnd, TEXT ("Could not write file %s"),
                                    szTitleName) ;
                         return 0 ;
                    }
               }
                                   // fall through
          case IDM_FILE_SAVE_AS:
               if (PopFileSaveDlg (hwnd, szFileName, szTitleName))
               {
                    DoCaption (hwnd, szTitleName) ;
                    
                    if (PopFileWrite (hwndEdit, szFileName))
                    {
                         bNeedSave = FALSE ;
                         return 1 ;
                    }
                    else
                    {
                         OkMessage (hwnd, TEXT ("Could not write file %s"),
                                    szTitleName) ;
                         return 0 ;
                    }
               }
               return 0 ;
               
          case IDM_FILE_PRINT:
               if (!PopPrntPrintFile (hInst, hwnd, hwndEdit, szTitleName))
                    OkMessage (hwnd, TEXT ("Could not print file %s"),
                                     szTitleName) ;
               return 0 ;
               
          case IDM_APP_EXIT:
               SendMessage (hwnd, WM_CLOSE, 0, 0) ;
               return 0 ;
               
                    // Messages from Edit menu
               
          case IDM_EDIT_UNDO:
               SendMessage (hwndEdit, WM_UNDO, 0, 0) ;
               return 0 ;
               
          case IDM_EDIT_CUT:
               SendMessage (hwndEdit, WM_CUT, 0, 0) ;
               return 0 ;
               
          case IDM_EDIT_COPY:
               SendMessage (hwndEdit, WM_COPY, 0, 0) ;
               return 0 ;
               
          case IDM_EDIT_PASTE:
               SendMessage (hwndEdit, WM_PASTE, 0, 0) ;
               return 0 ;
               
          case IDM_EDIT_CLEAR:
               SendMessage (hwndEdit, WM_CLEAR, 0, 0) ;
               return 0 ;
               
          case IDM_EDIT_SELECT_ALL:
               SendMessage (hwndEdit, EM_SETSEL, 0, -1) ;
               return 0 ;
               
                    // Messages from Search menu
               
          case IDM_SEARCH_FIND:
               SendMessage (hwndEdit, EM_GETSEL, 0, (LPARAM) &iOffset) ;
               hDlgModeless = PopFindFindDlg (hwnd) ;
               return 0 ;
               
          case IDM_SEARCH_NEXT:
               SendMessage (hwndEdit, EM_GETSEL, 0, (LPARAM) &iOffset) ;
               
               if (PopFindValidFind ())
                    PopFindNextText (hwndEdit, &iOffset) ;
               else
                    hDlgModeless = PopFindFindDlg (hwnd) ;
               
               return 0 ;
               
          case IDM_SEARCH_REPLACE:
               SendMessage (hwndEdit, EM_GETSEL, 0, (LPARAM) &iOffset) ;
               hDlgModeless = PopFindReplaceDlg (hwnd) ;
               return 0 ;
               
          case IDM_FORMAT_FONT:
               if (PopFontChooseFont (hwnd))
                    PopFontSetFont (hwndEdit) ;
               
               return 0 ;
               
                    // Messages from Help menu
               
          case IDM_HELP:
               OkMessage (hwnd, TEXT ("Help not yet implemented!"), 
                                TEXT ("\0")) ;
               return 0 ;
               
          case IDM_APP_ABOUT:
               DialogBox (hInst, TEXT ("AboutBox"), hwnd, AboutDlgProc) ;
               return 0 ;
          }
          break ;
               
     case WM_CLOSE:
          if (!bNeedSave || IDCANCEL != AskAboutSave (hwnd, szTitleName))
               DestroyWindow (hwnd) ;
          
          return 0 ;
          
     case WM_QUERYENDSESSION :
          if (!bNeedSave || IDCANCEL != AskAboutSave (hwnd, szTitleName))
               return 1 ;
          
          return 0 ;
          
     case WM_DESTROY:
          PopFontDeinitialize () ;
          PostQuitMessage (0) ;
          return 0 ;
          
     default:
               // Process "Find-Replace" messages
          
          if (message == messageFindReplace)
          {
               pfr = (LPFINDREPLACE) lParam ;
               
               if (pfr->Flags & FR_DIALOGTERM)
                    hDlgModeless = NULL ;
               
               if (pfr->Flags & FR_FINDNEXT)
                    if (!PopFindFindText (hwndEdit, &iOffset, pfr))
                         OkMessage (hwnd, TEXT ("Text not found!"), 
                                          TEXT ("\0")) ;
                    
               if (pfr->Flags & FR_REPLACE || pfr->Flags & FR_REPLACEALL)
                    if (!PopFindReplaceText (hwndEdit, &iOffset, pfr))
                         OkMessage (hwnd, TEXT ("Text not found!"), 
                                          TEXT ("\0")) ;
                         
               if (pfr->Flags & FR_REPLACEALL)
                    while (PopFindReplaceText (hwndEdit, &iOffset, pfr)) ;
                              
               return 0 ;
          }
          break ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}