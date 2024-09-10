/* error console dialog process */
BOOL CALLBACK callback_err_console( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    switch( uMsg )
    {
    case WM_INITDIALOG :
        break;
    case WM_DESTROY : 
        break;
    case WM_COMMAND :
        if( HIWORD( wParam ) == BN_CLICKED ) {
            switch( LOWORD( wParam ) ) {
            case IDOK :
                DestroyWindow( hWnd );
                break;
            case IDC_COPYCLIP :
                if( OpenClipboard( hWnd ) )
                    {
                        int i;
                        int num_lines = SendDlgItemMessage( hWnd, IDC_CONSOLE, 
                                        LB_GETCOUNT, 0, 0 );
                        int text_size;
                        char *buffer;
                        HGLOBAL clipbuffer;

                        if( num_lines <= 0 )
                            break;

                        /* calculate text size */
                        for( i = 0, text_size = 0; i < num_lines; i++ )
                            text_size += SendDlgItemMessage( hWnd, IDC_CONSOLE, 
                                   LB_GETTEXTLEN, ( WPARAM )i, 0 );

                        /* CR-LF for each line + terminating NULL */
                        text_size += 2 * num_lines + 1;
                        
                        EmptyClipboard( );
                        clipbuffer = GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE,
                                     text_size );
                        buffer = (char *)GlobalLock( clipbuffer );

                        /* concatenate lines of text in the global buffer */
                        for( i = 0; i < num_lines; i++ )
                        {                            
                            char msg_buf[1024];
                            
                            SendDlgItemMessage( hWnd, IDC_CONSOLE, LB_GETTEXT,
                                              ( WPARAM )i, ( LPARAM )msg_buf );
                            strcat( msg_buf, "\r\n" );
                            memcpy( buffer, msg_buf, strlen( msg_buf ) );
                            buffer += strlen( msg_buf );
                        }
                        *buffer = 0; /* null-terminate the buffer */

                        GlobalUnlock( clipbuffer );
                        SetClipboardData( CF_TEXT, clipbuffer );
                        CloseClipboard( );
                    }
                break;
            default :
                return 0;
            }
            break;
        }
        break;

    default :
        return DefWindowProc( hWnd, uMsg, wParam, lParam );
    }

    return 0;
}