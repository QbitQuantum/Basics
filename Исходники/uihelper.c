LRESULT CALLBACK EasyBusyDlg (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   static easythread_struct *et;
   static easybusydlg_struct *ebd;
//   HWND hctl;

   switch(message) {
      case WM_INITDIALOG:
      {
         et=(easythread_struct *)lParam;
         ebd=(easybusydlg_struct *)et->extra;
         ebd->hwnd = hwnd;
         return TRUE;
      }
      case WM_COMMAND:
         switch (LOWORD(wParam))
         {
            case IDCANCEL:
               EndDialog(hwnd, FALSE);
#if 0
               hctl = FindWindowExA(hwnd, NULL, "STATIC", NULL);
               SetWindowText(hctl, "Cancelling... Please wait.");
               EnableWindow(GetDlgItem(hwnd, IDCANCEL), FALSE);
#endif
               et->killflag = TRUE;
               return TRUE;
            default: 
                return FALSE;
         }
      default:
         return FALSE;
   }
}