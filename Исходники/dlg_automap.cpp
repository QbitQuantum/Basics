BOOL CALLBACK AutoMap_DlgProc (HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
   switch (msg)
      {
      case WM_INITDIALOG:
         AutoMap_OnInitDialog (hDlg);
         break;

      case WM_CTLCOLORSTATIC:
         if ((HWND)lp == GetDlgItem (hDlg, IDC_CHUNK_SIZE))
            {
            if (IsWindowEnabled ((HWND)lp))
               {
               static HBRUSH hbrStatic = CreateSolidBrush (GetSysColor (COLOR_WINDOW));
               SetTextColor ((HDC)wp, GetSysColor (COLOR_WINDOWTEXT));
               SetBkColor ((HDC)wp, GetSysColor (COLOR_WINDOW));
               return (BOOL)hbrStatic;
               }
            }
         break;

      case WM_COMMAND:
         switch (LOWORD(wp))
            {
            case IDHELP:
               AutoMap_DlgProc (hDlg, WM_HELP, 0, 0);
               break;

            case IDOK:
               EndDialog(hDlg, IDOK);
               break;

            case IDCANCEL:
               EndDialog(hDlg, IDCANCEL);
               break;

				case IDC_ADD:
					AutoMap_OnAdd(hDlg);
					break;

				case IDC_CHANGE:
					AutoMap_OnEdit(hDlg);
					break;

				case IDC_REMOVE:
					AutoMap_OnRemove(hDlg);
					break;
            }
         break;

      case WM_NOTIFY:
         switch (((LPNMHDR)lp)->code)
         	{
            case FLN_ITEMSELECT:
               AutoMap_OnSelect (hDlg);
               break;

            case FLN_LDBLCLICK:
               if (IsWindowEnabled (GetDlgItem (hDlg, IDC_EDIT)))
                  AutoMap_OnEdit (hDlg);
               break;
            }
         break;

      case WM_HELP:
         WinHelp (hDlg, g.szHelpFile, HELP_CONTEXT, IDH_AFSCONFIG_ADVANCED_AUTOMAP);
         break;
      }

   return FALSE;
}