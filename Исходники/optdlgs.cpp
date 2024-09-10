BOOL CALLBACK
KnownDllsDialogProc(
    HWND    hdlg,
    UINT    uMessage,
    WPARAM  wParam,
    LPARAM  lParam
    )
{
    static HWND hwndDlls;

    switch (uMessage) {
        case WM_INITDIALOG:
            {
                hwndDlls = GetDlgItem( hdlg, IDC_KNOWN_DLLS );
                SetWindowContextHelpId( hwndDlls, IDH_DLLS_OPTIONS );
                CenterWindow( GetParent( hdlg ), hwndFrame );
                //
                // set/initialize the image list(s)
                //
                HIMAGELIST himlState = ImageList_Create( 16, 16, TRUE, 2, 0 );
                ImageList_AddMasked(
                    himlState,
                    LoadBitmap (GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_CHECKSTATES)),
                    RGB (255,0,0)
                    );
                ListView_SetImageList( hwndDlls, himlState, LVSIL_STATE );
                //
                // set/initialize the columns
                //
                LV_COLUMN lvc = {0};
                lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
                lvc.pszText = "DLL Name";
                lvc.iSubItem = 0;
                lvc.cx = 260;
                lvc.fmt = LVCFMT_LEFT;
                ListView_InsertColumn( hwndDlls, 0, &lvc );
            }
            break;

        case WM_REFRESH_LIST:
            ListView_DeleteAllItems( hwndDlls );
            goto refresh_list;

        case WM_NOTIFY:
            switch (((LPNMHDR)lParam)->code) {
                case PSN_KILLACTIVE:
                    SetWindowLong( hdlg, DWL_MSGRESULT, 0 );
                    break;

                case PSN_APPLY:
                    SaveOptions();
                    SendMessage( GetParent(hdlg), PSM_UNCHANGED, (LPARAM)hdlg, 0 );
                    SetWindowLong( hdlg, DWL_MSGRESULT, 0 );
                    break;

                case NM_CLICK:
                    {
                        DWORD dwpos = GetMessagePos();
                        LV_HITTESTINFO lvhti = {0};
                        lvhti.pt.x = LOWORD(dwpos);
                        lvhti.pt.y = HIWORD(dwpos);
                        MapWindowPoints( HWND_DESKTOP, hwndDlls, &lvhti.pt, 1 );
                        int iItemClicked = ListView_HitTest( hwndDlls, &lvhti );
                        if (iItemClicked == -1) {
                            //
                            // add a new item
                            //
                            LV_ITEM lvi = {0};
                            lvi.pszText = "";
                            lvi.iItem = ListView_GetItemCount( hwndDlls );
                            lvi.iSubItem = 0;
                            lvi.iImage = 0;
                            lvi.mask = LVIF_TEXT;
                            lvi.state = 0;
                            lvi.stateMask = 0;
                            iItemClicked = ListView_InsertItem( hwndDlls, &lvi );
                        }
                        ListView_EditLabel( hwndDlls, iItemClicked );
                    }
                    break;

                case LVN_ENDLABELEDIT:
                    {
                        LV_DISPINFO *DispInfo = (LV_DISPINFO*)lParam;
                        LPSTR p = ApiMonOptions.KnownDlls;
                        ULONG i = 0;
                        LPSTR nk = (LPSTR) MemAlloc( 2048 );
                        LPSTR p1 = nk;
                        while( i != (ULONG)DispInfo->item.iItem ) {
                            strcpy( p1, p );
                            p1 += (strlen(p) + 1);
                            p  += (strlen(p) + 1);
                            i += 1;
                        }
                        p  += (strlen(p) + 1);
                        if (DispInfo->item.pszText && DispInfo->item.pszText[0]) {
                            strcpy( p1, DispInfo->item.pszText );
                            p1 += (strlen(DispInfo->item.pszText) + 1);
                        }
                        while( p && *p ) {
                            strcpy( p1, p );
                            p1 += (strlen(p) + 1);
                            p  += (strlen(p) + 1);
                        }
                        *p1 = 0;
                        memcpy( ApiMonOptions.KnownDlls, nk, 2048 );
                        MemFree( nk );
                        PostMessage( hdlg, WM_REFRESH_LIST, 0, 0 );
                    }

                case PSN_SETACTIVE:
refresh_list:
                    {
                        LPSTR p = ApiMonOptions.KnownDlls;
                        LV_ITEM lvi = {0};
                        int iItem = 0;
                        while( p && *p ) {
                            lvi.pszText = p;
                            lvi.iItem = iItem;
                            iItem += 1;
                            lvi.iSubItem = 0;
                            lvi.iImage = 0;
                            lvi.mask = LVIF_TEXT;
                            lvi.state = 0;
                            lvi.stateMask = 0;
                            ListView_InsertItem( hwndDlls, &lvi );
                            p += (strlen(p) + 1);
                        }
                    }
                    break;
            }
            break;

        case WM_HELP:
            {
                LPHELPINFO hi = (LPHELPINFO)lParam;
                ProcessHelpRequest( hdlg, hi->iCtrlId );
            }
            break;
    }
    return FALSE;
}