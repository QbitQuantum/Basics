//-------------------------------------------------------------------
LRESULT 
Statusbar_MenuSelect (HWND /*hwnd*/, WPARAM wParam, LPARAM lParam)
     {
     UINT fuFlags = (UINT) HIWORD (wParam) ;
     HMENU hMainMenu = NULL ;
     int iMenu = 0 ;

     // Handle non-system popup menu descriptions.
     if ((fuFlags & MF_POPUP) &&
         (!(fuFlags & MF_SYSMENU)))
          {
          for (iMenu = 1 ; iMenu < MAX_MENUS ; iMenu++)
               {
               if ((HMENU) lParam == popstr[iMenu].hMenu)
                    {
                    hMainMenu = (HMENU) lParam ;
                    break ;
                    }
               }
          }

     // Display helpful text in status bar
     MenuHelp (WM_MENUSELECT, wParam, lParam, hMainMenu, hInst, 
               hwndStatusBar, (UINT *) &popstr[iMenu]) ;

     return 0 ;
     }