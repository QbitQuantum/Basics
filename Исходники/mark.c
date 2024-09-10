/*
 * MarkDlgProc - handle messages from the mark dialog
 */
INT_PTR CALLBACK MarkDlgProc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
    char        buf[MARK_LEN];
    char        boxbuf[MARK_LEN];
    int         ret;
    HWND        hdl;

    lparam = lparam;
    switch( msg ) {
    case WM_INITDIALOG:
        SendDlgItemMessage( hwnd, MARK_BOXED, BM_SETCHECK, 1, 0L );
        hdl = GetDlgItem( hwnd, MARK_EDIT );
        SetFocus( hdl );
        return( FALSE );
//      strcpy( buf, "---------" );
//      SendDlgItemMessage( hwnd, MARK_EDIT, WM_SETTEXT, 0, (LPARAM)buf );
        break;
#ifndef NOUSE3D
    case WM_SYSCOLORCHANGE:
        CvrCtl3dColorChange();
        break;
#endif
    case WM_COMMAND:
        switch( wparam ) {
            case MARK_OK:
                ret = GetDlgItemText( hwnd, MARK_EDIT, buf, MARK_LEN );
                if( ret == 0 ) {
                    buf[0] = '\0';
                }
                if( IsDlgButtonChecked( hwnd, MARK_BOXED ) ) {
                    if( *buf == '\0' ) {
                        WriteFn( "*" );
                    } else {
                        strcpy( boxbuf, buf );
                        if( ret < MARK_LEN - 5 ) {
                            strcpy( boxbuf, "* " );
                            strcpy( boxbuf + 2, buf );
                            strcpy( boxbuf + ret + 2, " *" );
                        }
                        strcpy( buf, boxbuf );
                        strset( boxbuf, '*' );
                        WriteFn( boxbuf );
                        WriteFn( buf );
                        WriteFn( boxbuf );
                    }
                } else {
                    WriteFn( buf );
                }
                EndDialog( hwnd, -1 );
                break;
            case MARK_CANCEL:
                EndDialog( hwnd, -1 );
                break;
            default:
                return( FALSE );
        }
        break;
    default:
        return( FALSE );
    }
    return( TRUE );

} /* MarkDlgProc */