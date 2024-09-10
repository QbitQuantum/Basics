/*
 * StartUpDriver - the main message handling loop
 */
long __export FAR PASCAL StartUpDriver( HWND hwnd, UINT message,
                                WPARAM wparam, LPARAM lparam )
{
    FARPROC     farproc;
    HWND        tmpw;
    int         len;
    char        data[_MAX_PATH];
    char        tmp[80 + _MAX_PATH];
    HINSTANCE   inst;

    switch( message ) {
    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;

    case WM_COMMAND:
        switch( wparam ) {
        case MSG_ABOUT:
            inst = (HINSTANCE)GetWindowWord( hwnd, GWW_HINSTANCE );
            farproc = MakeProcInstance( (FARPROC)About2, inst );
            DialogBox( inst, ResName( "AboutBox" ), hwnd, (DLGPROC)farproc );
            FreeProcInstance( farproc );
            SetFocus( editChild );
            break;

        case PUSH_GETFILES_ID:
        case MSG_GETFILES:
            data[0] = 0;
            if( getFile( data ) ) {
                GetWindowText( editChild, tmp, sizeof( tmp ) );
                strcat( tmp, data );
                SetWindowText( editChild, tmp );
            }
            SetFocus( editChild );
            break;

        case PUSH_OK_ID:
        case SELECT_ID:
            len = GetWindowTextLength( editChild ) + 1;
            if( len > _MAX_PATH )
                len = _MAX_PATH;
            GetWindowText( editChild, dataPtr, len );
            canContinue = TRUE;
            tmpw = GetParent( editChild );
            SetWindowLong( editChild, GWL_WNDPROC, (LONG) oldClassProc );
            /* fall through, like exit was picked */

        case MSG_EXIT:
            DestroyWindow( mainWindow );
            PostQuitMessage( 0 );
            break;

        } /* switch */
        break;

    default:
        return( DefWindowProc(hwnd,message,wparam,lparam) );

    } /* switch */
    return( 0L );

} /* StartUpDriver */