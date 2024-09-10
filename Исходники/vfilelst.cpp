UINT_PTR CALLBACK AddSrcDlgProc95( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
    WORD            cmd;
    int             item;
    LRESULT         rc;
    HWND            ctl;
    HWND            dlg;
    GetFilesInfo    *info;

    lparam = lparam;
    switch( msg ) {
    case WM_INITDIALOG:
        {
            OPENFILENAME        *of;

            of = (OPENFILENAME *)lparam;
            ctl = GetDlgItem( hwnd, FOD_REMOVE );
            EnableWindow( ctl, FALSE );
            dlg = GetParent( hwnd );
            SendMessage( dlg, CDM_SETCONTROLTEXT, IDOK, (LPARAM)"&Add" );
            SET_DLGDATA( hwnd, of->lCustData );
            info = (GetFilesInfo *)of->lCustData;
            info->filter_index = of->nFilterIndex;
            info->filter = of->lpstrFilter;
            initFileList( hwnd );
        }
        break;
    case WM_COMMAND:
        cmd = LOWORD( wparam );
        switch( cmd ) {
        case FOD_ADD:
            addCurrentFile95( hwnd );
            return( TRUE );
        case FOD_ADDALL:
            addAllFiles95( hwnd );
            break;
        case FOD_REMOVE:
            ctl = GetDlgItem( hwnd, FOD_FILELIST );
            item = (int)SendMessage( ctl, LB_GETCURSEL, 0, 0 );
            if( item != LB_ERR ) {
                rc = SendMessage( ctl, LB_DELETESTRING, item, 0 );
                if( item != 0 ) {
                    SendMessage( ctl, LB_SETCURSEL, item - 1, 0 );
                } else {
                    SendMessage( ctl, LB_SETCURSEL, item, 0 );
                }
            }
            checkRemoveButton( hwnd );
            break;
        case FOD_FILELIST:
            if( GET_WM_COMMAND_CMD( wparam, lparam ) == LBN_SELCHANGE ||
                GET_WM_COMMAND_CMD( wparam, lparam ) == LBN_SELCANCEL ) {
                checkRemoveButton( hwnd );
            }
            break;
        case FOD_CLOSE:
            GetResults( hwnd );
            info = (GetFilesInfo *)GET_DLGDATA( hwnd );
            info->ret_code = IDOK;
            PostMessage( GetParent( hwnd ), WM_COMMAND, IDCANCEL, 0L );
            return( TRUE );
        case IDCANCEL:
            info = (GetFilesInfo *)GET_DLGDATA( hwnd );
            info->ret_code = IDCANCEL;
            PostMessage( GetParent( hwnd ), WM_COMMAND, IDCANCEL, 0L );
            return( TRUE );
        default:
            return( FALSE );
        }
        break;
    case WM_NOTIFY:
        switch( ((NMHDR *)lparam)->code ) {
        case CDN_FILEOK:
            PostMessage( hwnd, WM_COMMAND, FOD_ADD, 0L );
            SET_DLGRESULT( hwnd, 1L );
            return( TRUE );
        case CDN_TYPECHANGE:
            info = (GetFilesInfo *)GET_DLGDATA( hwnd );
            info->filter_index = ((OFNOTIFY *)lparam)->lpOFN->nFilterIndex;
            break;
        }
        break;
    default:
        return( FALSE );
    }
    return( TRUE );
}