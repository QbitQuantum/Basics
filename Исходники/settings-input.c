LRESULT CALLBACK MouseConfigDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam,
                                    LPARAM lParam)
{
   static u8 cursel;
   static BOOL enablebuttons;
   static int controlmap[13];
   static int padnum;
   static HWND hParent;
   static int emulatetype;
   int i;

   switch (uMsg)
   {
      case WM_INITDIALOG:
      {
         padnum = (int)lParam;

         hParent = PropSheet_GetCurrentPageHwnd(GetParent(hDlg));
         emulatetype = ConvertEmulateTypeSelStringToID(hParent, IDC_PORT1ATYPECB+padnum);
         PERDXListDevices(GetDlgItem(hDlg, IDC_DXDEVICECB), emulatetype);

         // Load settings from ini here, if necessary
         PERDXInitControlConfig(hDlg, padnum, controlmap, inifilename);

         cursel = (u8)SendDlgItemMessage(hDlg, IDC_DXDEVICECB, CB_GETCURSEL, 0, 0);
         enablebuttons = cursel ? TRUE : FALSE;

         EnableWindow(GetDlgItem(hDlg, IDC_STARTPB), enablebuttons);
         EnableWindow(GetDlgItem(hDlg, IDC_APB), enablebuttons);
         EnableWindow(GetDlgItem(hDlg, IDC_BPB), enablebuttons);
         EnableWindow(GetDlgItem(hDlg, IDC_CPB), enablebuttons);
         return TRUE;
      }
      case WM_COMMAND:
      {
         switch (LOWORD(wParam))
         {
            case IDC_STARTPB:
            case IDC_APB:
            case IDC_BPB:
            case IDC_CPB:
            {
               DoControlConfig(hDlg, cursel-1, IDC_UPTEXT+(LOWORD(wParam)-IDC_UPPB), IDC_UPTEXT, controlmap);

               return TRUE;
            }
            case IDOK:
            {
               char string1[20];
               char string2[20];

               EndDialog(hDlg, TRUE);

               sprintf(string1, "Peripheral%d%C", ((padnum/6)+1), 'A'+(padnum%6));

               // Write GUID
               PERDXWriteGUID(cursel-1, padnum, inifilename);

               for (i = 0; i < 13; i++)
               {
                  sprintf(string2, "%d", controlmap[i]);
                  WritePrivateProfileStringA(string1, PerPadNames[i], string2, inifilename);
               }
               return TRUE;
            }
            case IDCANCEL:
            {
               EndDialog(hDlg, FALSE);
               return TRUE;
            }
            case IDC_DXDEVICECB:
            {
               switch(HIWORD(wParam))
               {
                  case CBN_SELCHANGE:
                  {
                     cursel = (u8)SendDlgItemMessage(hDlg, IDC_DXDEVICECB, CB_GETCURSEL, 0, 0);
                     enablebuttons = cursel ? TRUE : FALSE;

                     EnableWindow(GetDlgItem(hDlg, IDC_STARTPB), enablebuttons);
                     EnableWindow(GetDlgItem(hDlg, IDC_APB), enablebuttons);
                     EnableWindow(GetDlgItem(hDlg, IDC_BPB), enablebuttons);
                     EnableWindow(GetDlgItem(hDlg, IDC_CPB), enablebuttons);
                     break;
                  }
                  default: break;
               }
               break;
            }
            default: break;
         }

         break;
      }
      case WM_DESTROY:
      {
         break;
      }
   }

   return FALSE;
}