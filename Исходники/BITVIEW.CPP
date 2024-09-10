BOOL CALLBACK PaletteDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
   BOOL  msgProcessed;
   RECT  r;
   HWND  hCtrl;

   msgProcessed = FALSE;
   switch (message) 
   {
      case WM_INITDIALOG:
         GetWindowRect(hDlg, &r);
         r.left = (GetSystemMetrics(SM_CXSCREEN) - (r.right - r.left)) / 2;
         r.top  = (GetSystemMetrics(SM_CYSCREEN) - (r.bottom - r.top)) / 2;
         SetWindowPos(hDlg, NULL, r.left,r.top,0,0, SWP_NOSIZE | SWP_NOZORDER);
      
         hCtrl = GetDlgItem(hDlg, IDC_SC_TRANSLUCENCY);
         SetScrollRange(hCtrl, SB_CTL, 0, pal->getMaxTranslucent(), TRUE);
         SetScrollPos(hCtrl, SB_CTL, pal->getTransLevel(), TRUE);

         hCtrl = GetDlgItem(hDlg, IDC_SC_HAZE);
         SetScrollRange(hCtrl, SB_CTL, 0, pal->getMaxHaze(), TRUE);
         SetScrollPos(hCtrl, SB_CTL, pal->getHazeIndex(), TRUE);
         
         hCtrl = GetDlgItem(hDlg, IDC_SC_SHADE);
         SetScrollRange(hCtrl, SB_CTL, 0, pal->getMaxShade(), TRUE);
         SetScrollPos(hCtrl, SB_CTL, curShadeIndex, TRUE);
         
         msgProcessed = TRUE;
         break;

      case WM_COMMAND:            
         switch(LOWORD(wParam))
         {
                      /*
            case IDCANCEL:
            case IDM_PUSHOK:
               EndDialog(hDlg, wParam);         
               msgProcessed = TRUE;
               
               break;  
                        */
            default:
               break;
         }
      
         break;
      case WM_HSCROLL:
         int shift;
         int newPos;
         
         switch(LOWORD(wParam))
         {
            case SB_PAGELEFT:
            case SB_LINELEFT:
               shift = -1;
               break;
            case SB_PAGERIGHT:
            case SB_LINERIGHT:
               shift = 1;
               break;
            case SB_THUMBTRACK:
            case SB_THUMBPOSITION:
               shift = 0;
               newPos = HIWORD(wParam);
               break;
            default:
               return 1;
         }
         hCtrl = (HWND) LOWORD(lParam);
         long ctrlIdx;
         ctrlIdx = GetWindowLong(hCtrl, GWL_ID);
         
         if(shift)
         {
            int min, max;
            newPos = GetScrollPos(hCtrl, SB_CTL);
            newPos += shift;
            GetScrollRange(hCtrl, SB_CTL, &min, &max);
            if(newPos < min)
               newPos = min;
            else if(newPos > max)
               newPos = max;
         }
         SetScrollPos(hCtrl, SB_CTL, newPos, TRUE);
         
         switch(ctrlIdx)
         {
            case IDC_SC_TRANSLUCENCY:
               hCtrl = GetDlgItem(hDlg, IDC_SC_TRANSLUCENCY);
               pal->setTransLevel(GetScrollPos(hCtrl, SB_CTL));
               break;
            case IDC_SC_HAZE:
               
               break;
            case IDC_SC_SHADE:
               break;
         }
         Redraw();
         return 0;
      case WM_CLOSE:
         DestroyWindow(hDlg);
         paletteWindow = 0;
         break;
   }
   return (msgProcessed);               
}