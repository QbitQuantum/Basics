HRESULT CALLBACK DlgProc_Browse (HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
   BROWSEDIALOGPARAMS *pbdp;

   if (AfsAppLib_HandleHelp (IDD_APPLIB_BROWSE, hDlg, msg, wp, lp))
   {
      return FALSE;
   }

   if (msg == WM_INITDIALOG)
   {
      SetWindowLongPtr (hDlg, DWLP_USER, lp);
   }

   if ((pbdp = (BROWSEDIALOGPARAMS *)GetWindowLongPtr (hDlg, DWLP_USER)) != NULL)
   {
      switch (msg)
      {
         case WM_INITDIALOG:
            DlgProc_Browse_OnInitDialog (hDlg, pbdp);
            break;

         case WM_NOTIFY:
            switch (((LPNMHDR)lp)->code)
            {
               case LVN_ITEMCHANGED:
                  if ( ((LPNM_LISTVIEW)lp)->uNewState & LVIS_SELECTED )
                  {
                     DlgProc_Browse_SelectedEntry (hDlg, pbdp);
                  }
                  break;

               case NM_DBLCLK:
                  PostMessage (hDlg, WM_COMMAND, MAKELONG(IDC_BROWSE_SELECT,BN_CLICKED), (LPARAM)GetDlgItem(hDlg,IDC_BROWSE_SELECT));
                  break;
            }
            break;

         case WM_DESTROY:
            DlgProc_Browse_StopSearch (pbdp);

            if (pbdp->hImages != NULL)
            {
               ListView_SetImageList (GetDlgItem (hDlg, IDC_BROWSE_LIST), 0, 0);
               ImageList_Destroy (pbdp->hImages);
            }
            break;

         case WM_FOUNDNAME:
         {
            LPTSTR pszName = (LPTSTR)lp;
            if (pszName != NULL)
            {
               HWND hList = GetDlgItem (hDlg, IDC_BROWSE_LIST);
               LV_AddItem (hList, 1, INDEX_SORT, 0, 0, pszName);
               FreeString (pszName);
            }
            break;
         }

         case WM_THREADSTART:
         {
            TCHAR szText[ cchRESOURCE ];
            GetString (szText, IDS_BROWSE_WAITING);
            SetDlgItemText (pbdp->hDlg, IDC_BROWSE_STATUS, szText);
            break;
         }

         case WM_THREADDONE:
         {
            SetDlgItemText (pbdp->hDlg, IDC_BROWSE_STATUS, TEXT(""));
            break;
         }

         case WM_COMMAND:
            switch (LOWORD(wp))
            {
               case IDCANCEL:
                  EndDialog (hDlg, LOWORD(wp));
                  break;

               case IDC_BROWSE_SELECT:
                  if ( (GetDlgItem (pbdp->hDlg, IDC_BROWSE_NONE) != NULL) &&
                       (IsDlgButtonChecked (pbdp->hDlg, IDC_BROWSE_NONE)) )
                  {
                     pbdp->szCell[0] = TEXT('\0');
                     pbdp->szNamed[0] = TEXT('\0');
                  }
                  else
                  {
                     GetDlgItemText (hDlg, IDC_BROWSE_CELL,  pbdp->szCell,  cchNAME);
                     GetDlgItemText (hDlg, IDC_BROWSE_NAMED, pbdp->szNamed, cchRESOURCE);
                  }
                  EndDialog (hDlg, IDOK);
                  break;

               case IDC_BROWSE_CELL:
                  if (HIWORD(wp) == CBN_SELCHANGE)
                  {
                     GetDlgItemText (hDlg, IDC_BROWSE_CELL, pbdp->szCell, cchNAME);
                     DlgProc_Browse_StartSearch (pbdp, FALSE);
                  }
                  break;

               case IDC_BROWSE_RESTART:
                  GetDlgItemText (hDlg, IDC_BROWSE_CELL, pbdp->szCell, cchNAME);
                  DlgProc_Browse_StartSearch (pbdp, FALSE);
                  PostMessage (hDlg, WM_NEXTDLGCTL, (WPARAM)GetDlgItem (hDlg, IDC_BROWSE_NAMED), (LPARAM)TRUE);
                  break;

               case IDC_BROWSE_NAMED:
                  if (HIWORD(wp) == EN_UPDATE)  // has the user hit Enter here?
                  {
                     TCHAR szTest[ cchRESOURCE ];

                     GetDlgItemText (hDlg, IDC_BROWSE_NAMED, szTest, cchRESOURCE);

                     if ( (lstrlen (szTest) > 0) &&
                          (szTest[ lstrlen(szTest)-1 ] == TEXT('\n')) )
                     {
                        szTest[ lstrlen(szTest)-1 ] = TEXT('\0');

                        if ( (lstrlen (szTest) > 0) &&
                             (szTest[ lstrlen(szTest)-1 ] == TEXT('\r')) )
                        {
                           szTest[ lstrlen(szTest)-1 ] = TEXT('\0');
                        }

                        SetDlgItemText (hDlg, IDC_BROWSE_NAMED, szTest);
                        PostMessage (hDlg, WM_COMMAND, MAKELONG(IDC_BROWSE_SELECT,BN_CLICKED), (LPARAM)GetDlgItem(hDlg,IDC_BROWSE_SELECT));
                     }
                  }
                  break;

               case IDC_BROWSE_NONE:
                  DlgProc_Browse_OnNone (hDlg, pbdp);
                  break;
            }
            break;
      }
   }

   return FALSE;
}