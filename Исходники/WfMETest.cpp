BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {

   chSETDLGICONS(hwnd, IDI_WFMETEXT);

   // Initialize the controls in the dialog box
   SetDlgItemInt(hwnd,  IDC_NUMOBJS, 4, FALSE);
   SetDlgItemInt(hwnd,  IDC_TIMEOUT, 30000, FALSE);
   SetDlgItemText(hwnd, IDC_EXPRESSION, 
      _T("1 2 | 2 3 4 | 1 4"));

   // Set the multi-column listbox's column size
   ListBox_SetColumnWidth(GetDlgItem(hwnd, IDC_OBJLIST), 
      LOWORD(GetDialogBaseUnits()) * 4);

   return(TRUE);  // Accept default focus window.
}