LRESULT CALLBACK
waoWC_buttonChkProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{   static TRACKMOUSEEVENT tME;
    switch( msg )
    {
        case WM_CREATE:
        {
            tME.cbSize = sizeof( TRACKMOUSEEVENT );
            tME.dwHoverTime = 0;
            SendMessage( GetParent( hwnd ),
                         WAOM_TBBTNCREATED,
                         MAKEWPARAM( WAOM_TBBTNCREATED_LW, GetWindowLong( hwnd, GWL_ID ) ),
                         ( LPARAM ) hwnd );
        }
        case WM_MOUSELEAVE:
        if( !( GetWindowLong( hwnd, GWL_USERDATA ) & WAO_TBBS_CHECKED ) )
        {
            SetWindowLong( hwnd, GWL_USERDATA, WAO_TBBS_NORMAL );
            RedrawWindow( hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE );
        }
        else
            SetWindowLong( hwnd, GWL_USERDATA, WAO_TBBS_CHECKED | WAO_TBBS_NORMAL );
        break;
        case WM_LBUTTONUP:
        {
            // should be clicked first:
            if( !( GetWindowLong( hwnd, GWL_USERDATA ) & WAO_TBBS_CLICKED ) )
                return FALSE;
            if( GetWindowLong( hwnd, GWL_USERDATA ) & WAO_TBBS_CHECKED )
            {
                if( !( GetWindowLong( hwnd, GWL_STYLE ) & BS_AUTORADIOBUTTON ) )
                {
                    SetWindowLong( hwnd, GWL_USERDATA, WAO_TBBS_HOVERED );
                    tME.dwFlags = TME_LEAVE;
                    tME.hwndTrack = hwnd;
                    TrackMouseEvent( &tME );
                }
            }
            else
            {
                SetWindowLong( hwnd, GWL_USERDATA, WAO_TBBS_CHECKED );
                if( GetWindowLong( hwnd, GWL_STYLE ) & BS_RADIOBUTTON )
                {
                    long wStyle;
                    HWND t_hndWnd = hwnd;
                    while( t_hndWnd = GetWindow( t_hndWnd, GW_HWNDPREV ) )
                    {
                        wchar_t buffer[ 16 ];
                        GetClassName( t_hndWnd, buffer, 15 );
                        if( lstrcmp( buffer, L"wao_BUTTON_Chk" ) )
                            break;
                        wStyle = GetWindowLong( t_hndWnd, GWL_STYLE );
                        if( !( wStyle & BS_RADIOBUTTON ) )
                            break;
                        SetWindowLong( t_hndWnd, GWL_USERDATA, WAO_TBBS_NORMAL );
                        RedrawWindow( t_hndWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE );
                        if( wStyle & WS_GROUP )
                            break;
                    }
                    t_hndWnd = hwnd;
                    while( t_hndWnd = GetWindow( t_hndWnd, GW_HWNDNEXT ) )
                    {
                        wchar_t buffer[ 16 ];
                        GetClassName( t_hndWnd, buffer, 15 );
                        if( lstrcmp( buffer, L"wao_BUTTON_Chk" ) )
                            break;
                        wStyle = GetWindowLong( t_hndWnd, GWL_STYLE );
                        if( !( wStyle & BS_RADIOBUTTON ) )
                            break;
                        SetWindowLong( t_hndWnd, GWL_USERDATA, WAO_TBBS_NORMAL );
                        RedrawWindow( t_hndWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE );
                        if( wStyle & WS_GROUP )
                            break;
                    }
                }
            }
            RedrawWindow( hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE );
// RADIO BUTTON
            DLGPROC parProc = ( DLGPROC ) GetWindowLong( GetParent( hwnd ), DWL_DLGPROC );
            parProc( GetParent( hwnd ),
                     WM_COMMAND,
                     MAKEWPARAM( GetWindowLong( hwnd, GWL_ID ), WAO_TBBN_LCLCKED ),
                     ( LPARAM ) hwnd );

        }
        break;
        default:
        return( waoWC_button0Proc( hwnd, msg, wParam, lParam ) );
    }
}