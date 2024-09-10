/*
 * WindowProc - handle messages for the main application window
 */
LONG _EXPORT FAR PASCAL WindowProc( HWND window_handle, unsigned msg,
                                     WORD wparam, LONG lparam )
/*************************************************************/
{
    FARPROC             proc;
    HANDLE              inst_handle;
    extra_data          *edata_ptr;
    HDC                 hdc;
    PAINTSTRUCT         ps;
    RECT                rect;
    HBRUSH              brush;

    /*
     * if the message window is ON, send all messages we want to display to the
     * message window, so that we can see what is happening
     * ( before we actually process the message )
     */
    if( MessagesOn ) {
        switch( msg ) {
        case WM_COMMAND:
        case WM_MOUSEMOVE:
        case WM_LBUTTONUP:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        case WM_RBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_CHAR:
        case WM_TIMER:
        case WM_HSCROLL:
        case WM_VSCROLL:
            SendMessage( MessageWnd, msg, wparam, lparam );
            break;
        }
    }

    /*
     * now process the message
     */
    switch( msg ) {
    case WM_CREATE:
        inst_handle = GetWindowWord( window_handle, GWW_HINSTANCE );
        /*
         * make sure message window is turned OFF to start
         */
        MessagesOn = FALSE;
        CheckMenuItem ( GetMenu( window_handle ), MENU_MESSAGE_WINDOW_ON,
                        MF_BYCOMMAND | MF_UNCHECKED );
        break;
    case WM_LBUTTONDOWN:
        /*
         * zap the target with a lightning bolt!
         */
        edata_ptr = (extra_data *) GetWindowLong( window_handle,
                                            EXTRA_DATA_OFFSET );
        /*
         * set the aim point to where the mouse was just clicked
         * set the bolt start point to the top left corner of the window
         */
        edata_ptr->aim = MAKEPOINT( lparam );
        edata_ptr->bolt.x = edata_ptr->client_rect.right - BOLTWIDTH;
        edata_ptr->bolt.y = edata_ptr->client_rect.top;
        /*
         * shoot the bolt from the current bolt position to the aim point
         */
        ShootBolt( window_handle );
        break;
    case WM_SIZE:
        edata_ptr = (extra_data *) GetWindowLong( window_handle,
                                            EXTRA_DATA_OFFSET );
        /*
         * store the new size of the window
         */
        GetClientRect( window_handle, &edata_ptr->client_rect );
        SetScrollRange( window_handle, SB_HORZ, edata_ptr->client_rect.left,
                        edata_ptr->client_rect.right, TRUE );
        SetScrollRange( window_handle, SB_VERT, edata_ptr->client_rect.top,
                        edata_ptr->client_rect.bottom, TRUE );
        break;
    case WM_COMMAND:
        switch( wparam ) {
        case MENU_ABOUT:
            inst_handle = GetWindowWord( window_handle, GWW_HINSTANCE );
            proc = MakeProcInstance( (FARPROC)About, inst_handle );
            DialogBox( inst_handle,"AboutBox", window_handle, (DLGPROC)proc );
            FreeProcInstance( proc );
            break;
        case MENU_EXIT:
            SendMessage( window_handle, WM_CLOSE, 0, 0L );
            break;
        case MENU_SET_TARGET_SPEED:
            inst_handle = GetWindowWord( window_handle, GWW_HINSTANCE );
            proc = MakeProcInstance( (FARPROC)SpeedDlgProc, inst_handle );
            DialogBoxParam( inst_handle,"SpeedDlg", window_handle, (DLGPROC)proc,
                            (DWORD)SET_TARGET_SPEED );
            FreeProcInstance( proc );
            break;
        case MENU_SET_BOLT_SPEED:
            inst_handle = GetWindowWord( window_handle, GWW_HINSTANCE );
            proc = MakeProcInstance( (FARPROC)SpeedDlgProc, inst_handle );
            DialogBoxParam( inst_handle,"SpeedDlg", window_handle, (DLGPROC)proc,
                            (DWORD)SET_BOLT_SPEED );
            FreeProcInstance( proc );
            break;
        case MENU_SCORE_WINDOW_ON:
            /*
             * toggle the score window on or off
             */
            edata_ptr = (extra_data *) GetWindowLong( window_handle,
                                                EXTRA_DATA_OFFSET );
            if( !edata_ptr->score_on ) {
                TurnScoreWindowOn( window_handle );
                CheckMenuItem ( GetMenu( window_handle ),
                                wparam, MF_BYCOMMAND | MF_CHECKED );
                edata_ptr->score_on = TRUE;
            } else {
                SendMessage( ScoreWnd, WM_CLOSE, 0, 0L );
                CheckMenuItem ( GetMenu( window_handle ), wparam,
                    MF_BYCOMMAND | MF_UNCHECKED );
                edata_ptr->score_on = FALSE;
            }
            break;
        case MENU_SOUND_ON:
            /*
             * toggle the sound on or off
             */
            edata_ptr = (extra_data *) GetWindowLong( window_handle,
                                                EXTRA_DATA_OFFSET );
            if( !edata_ptr->sound_on ) {
                CheckMenuItem ( GetMenu( window_handle ),
                                wparam, MF_BYCOMMAND | MF_CHECKED );
                edata_ptr->sound_on = TRUE;
            } else {
                CheckMenuItem ( GetMenu( window_handle ), wparam,
                    MF_BYCOMMAND | MF_UNCHECKED );
                edata_ptr->sound_on = FALSE;
            }
            break;
        case MENU_MESSAGE_WINDOW_ON:
            /*
             * toggle the message window on or off
             */
            if( !MessagesOn ) {
                TurnMessageWindowOn( window_handle );
                CheckMenuItem ( GetMenu( window_handle ),
                                wparam, MF_BYCOMMAND | MF_CHECKED );
                MessagesOn = TRUE;
            } else {
                SendMessage( MessageWnd, WM_CLOSE, 0, 0L );
                CheckMenuItem ( GetMenu( window_handle ), wparam,
                    MF_BYCOMMAND | MF_UNCHECKED );
                MessagesOn = FALSE;
            }
            break;
        }
        break;
    case WM_PAINT:
        edata_ptr = (extra_data *) GetWindowLong( window_handle,
                                            EXTRA_DATA_OFFSET );
        hdc = BeginPaint (window_handle, &ps);
        /*
         * paint the invalid area with the background colour
         */
        brush = CreateSolidBrush( BACKGROUND );
        FillRect( hdc, &ps.rcPaint, brush );
        DeleteObject( brush );

        rect.left   = edata_ptr->target.x;
        rect.top    = edata_ptr->target.y;
        rect.right  = rect.left + edata_ptr->size.x;
        rect.bottom = rect.top + edata_ptr->size.y;

        /*
         * if part of the target bitmap is invalid, redraw it
         */
        if( IntersectRect( &rect, &rect, &ps.rcPaint ) ) {
            DrawBitmap( hdc, edata_ptr->target_bmp,
                        edata_ptr->target.x, edata_ptr->target.y );
        }
        EndPaint(window_handle, &ps);
        break;
    case WM_HSCROLL:
    case WM_VSCROLL:
        /*
         * use the scrollbars to move the target around
         */
        {
            short position; /* the x or y position of the scrollbar */
            short max;
            short min;

            edata_ptr = (extra_data *) GetWindowLong( window_handle,
                                                EXTRA_DATA_OFFSET );
            position = ( msg == WM_HSCROLL ) ?
                       edata_ptr->target.x : edata_ptr->target.y;

            switch( wparam ) {
            case SB_PAGEDOWN:
                position += 15;
                break;
            case SB_LINEDOWN:
                position++;
                break;
            case SB_PAGEUP:
                position -= 15;
                break;
            case SB_LINEUP:
                position--;
                break;
            case SB_THUMBPOSITION:
            case SB_THUMBTRACK:
                position = LOWORD( lparam );
                break;
            default:
                return( 0L );
            }
            if( msg == WM_HSCROLL ) {
                GetScrollRange( window_handle, SB_HORZ, (LPINT)&min, (LPINT)&max );
                edata_ptr->target.x = max( min( position, max ), min );
                SetScrollPos( window_handle, SB_HORZ, edata_ptr->target.x , TRUE );
            } else {
                GetScrollRange( window_handle, SB_VERT, (LPINT)&min, (LPINT)&max );
                edata_ptr->target.y = max( min( position, max ), min );
                SetScrollPos( window_handle, SB_VERT, edata_ptr->target.y, TRUE );
            }
            InvalidateRect( window_handle, &edata_ptr->client_rect, FALSE );
        }
        break;
    case WM_MOVE_TARGET:

        /*
         * move the target to a random location on the screen
         */

        edata_ptr = (extra_data *) GetWindowLong( window_handle,
                                            EXTRA_DATA_OFFSET );
        rect.left   = edata_ptr->target.x;
        rect.top    = edata_ptr->target.y;
        rect.right  = rect.left + edata_ptr->size.x;
        rect.bottom = rect.top + edata_ptr->size.y;
        InvalidateRect( window_handle, &rect, TRUE );

        edata_ptr->target = RandPoint( edata_ptr->client_rect, edata_ptr->size );

        rect.left   = edata_ptr->target.x;
        rect.top    = edata_ptr->target.y;
        rect.right  = rect.left + edata_ptr->size.x;
        rect.bottom = rect.top + edata_ptr->size.y;
        InvalidateRect( window_handle, &rect, TRUE );

        /* set the scrollbars to indicate the new position */
        SetScrollPos( window_handle, SB_HORZ, edata_ptr->target.x , TRUE );
        SetScrollPos( window_handle, SB_VERT, edata_ptr->target.y, TRUE );

        break;
    case WM_TIMER:
        SendMessage( window_handle, WM_MOVE_TARGET, 0, 0L );
        break;
        break;
    case WM_DESTROY:
        edata_ptr = (extra_data *) GetWindowLong( window_handle,
                                                  EXTRA_DATA_OFFSET );
        KillTimer( window_handle, TARGET_TIMER );       /* Stops the timer */
        FreeProcInstance( edata_ptr->message_window_proc );
        FreeProcInstance( edata_ptr->score_window_proc );
        PostQuitMessage( 0 );
        break;

    default:
        return( DefWindowProc( window_handle, msg, wparam, lparam ) );
    }
    return( 0L );

} /* WindowProc */