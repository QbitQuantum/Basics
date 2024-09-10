void Server_OnKey_Tab (HWND hDlg, BOOL fForward)
{
   // The tab-cycle should go:
   //    TabControl <-> TabChildControls
   //
   HWND hFocus = GetFocus();
   HWND hTabChild = GetTabChild (GetDlgItem (hDlg, IDC_TABS));

   if (fForward)
      {
      if (hFocus == GetDlgItem (hDlg, IDC_TABS))
         {
         PostMessage (hDlg, WM_NEXTDLGCTL, (WPARAM)GetNextDlgTabItem (hTabChild, NULL, FALSE), TRUE);
         }
      else
         {
         if (GetNextDlgTabItem (hTabChild, hFocus, FALSE) == GetNextDlgTabItem (hTabChild, NULL, FALSE))
            PostMessage (hDlg, WM_NEXTDLGCTL, (WPARAM)GetDlgItem (hDlg, IDC_TABS), TRUE);
         else
            PostMessage (hDlg, WM_NEXTDLGCTL, (WPARAM)GetNextDlgTabItem (hTabChild, hFocus, FALSE), TRUE);
         }
      }
   else // (!fForward)
      {
      if (hFocus == GetDlgItem (hDlg, IDC_TABS))
         {
         PostMessage (hDlg, WM_NEXTDLGCTL, (WPARAM)GetLastDlgTabItem (hTabChild), TRUE);
         }
      else
         {
         if (hFocus == GetNextDlgTabItem (hTabChild, NULL, FALSE))
            PostMessage (hDlg, WM_NEXTDLGCTL, (WPARAM)GetDlgItem (hDlg, IDC_TABS), TRUE);
         else
            PostMessage (hDlg, WM_NEXTDLGCTL, (WPARAM)GetNextDlgTabItem (hTabChild, hFocus, TRUE), TRUE);
         }
      }
}