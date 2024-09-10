LRESULT CALLBACK FileViewProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hDlg = hWnd;
	long	i=0;
	short	win=0;

	while( i < NUMFILES ){
		if ( hViewWindows[i] == hWnd ){
			win = (short)i;
			break;
		}
		i++;
	}
	i = 0;
	//filename = fileview_name[win];
//	OutDebugs( "Window %d, filename %s", win, filename );

	switch (message) {
		case WM_PAINT:{
				HDC hdc;
                PAINTSTRUCT ps;
                RECT rc;

                GetClientRect(hDlg, &rc);
				hdc = BeginPaint(hDlg, &ps);
				FillRect( hdc, &rc, GetSysColorBrush(COLOR_3DFACE) );
                EndPaint(hDlg, &ps);

				UpdateWindow( GetDlgItem(hWnd, IDC_VIEWSCROLL) );
            }
			SetText( IDC_FILEVIEWNAME, fileview_name[win] );
			break; 

		
		case WM_INITDIALOG:
			lineTooLongMsgLen = mystrlen( lineTooLongMsg );
			if ( initWindowIndex >= 0 ){
				hViewWindows[ initWindowIndex ] = hWnd;
				initWindowIndex = -1;
			}
			hMenu[win] = LoadMenu( hInst, "FILEVIEW_MENU" );
			SetTimer (hWnd, FILEVIEW_TIMER, 300, NULL);
//			OutDebugs( "Init Dialog: Window %d, filename %s", win, fileview_name[win] );
			SetText( IDC_FILEVIEWNAME, fileview_name[win] );

			EnableScrollBar( GetDlgItem(hWnd, IDC_VIEWSCROLL), SB_CTL,ESB_ENABLE_BOTH );
			OutDebug( fileview_name[win] );
			InitWindowStats( &winStats[win] );
			SetScale( fileview_name[win], 0, win, hDlg );
			SetScrollRange(  GetDlgItem(hWnd, IDC_VIEWSCROLL), SB_CTL, 0, winStats[win].scrollScale, 1 );
			ShowScrollBar( GetDlgItem(hWnd, IDC_VIEWSCROLL), SB_CTL, 1 );

			ListView_SetExtendedListViewStyleEx( GetDlgItem(hWnd, IDC_FILEVIEW), LVS_EX_FULLROWSELECT , LVS_EX_FULLROWSELECT );

			{
				long numlines, pos = winStats[win].scrollScale+1;
				numlines = GetLinestoFit( hWnd, win );
				winStats[win].linesInWin = numlines;
				i = 0;
				while( i < numlines-1 ){
					i += UpdateFileView( hDlg, win, pos-- );
					if ( pos < 0 )
						break;
				}
				SetScrollPos( GetDlgItem(hDlg, IDC_VIEWSCROLL), SB_CTL, pos, 1 );
			}
			SetFocus( GetDlgItem(hDlg, IDC_FILEVIEW) );
			break;

	    case WM_TIMER:
			if (wParam == FILEVIEW_TIMER ){
				char	title[350];
/*				long x = GetScrollPos( GetDlgItem(hWnd, IDC_VIEWSCROLL), SB_CTL );
				long startPos, endPos;
				startPos = (long)((winStats[win].fileLen/(double)winStats[win].averageLineLen) * (x/(double)winStats[win].scrollScale));
				endPos = startPos + winStats[win].linesInWin;
				sprintf( title, "Viewing - %s  (at approx. lines %d - %d)", fileview_name[win], startPos, endPos );*/
				sprintf( title, "View - %s", fileview_name[win] );
				SetWindowText( hWnd, title );
				CheckFileViewStatus( hWnd, win );
			}
			break;

        case WM_RBUTTONDOWN: // RightClick in windows client area...
			{
			    POINT	pnt;	

				pnt.x = LOWORD(lParam);
				pnt.y = HIWORD(lParam);
				ClientToScreen(hWnd, (LPPOINT) &pnt);
				// This is where you would determine the appropriate 'context'
				// menu to bring up. Since this app has no real functionality,
				// we will just bring up the 'Help' menu:
				//hMenu = GetSubMenu (GetMenu (hWnd), 0);
				if (hMenu[win]) {
					TrackPopupMenu (GetSubMenu (hMenu[win], 0), 0, pnt.x, pnt.y, 0, hWnd, NULL);
				} 
			}
            break;

		case WM_CLOSE:
			if ( hMenu[win] ) DestroyMenu( hMenu[win] );
			hViewWindows[win] = 0;
			EndDialog(hWnd, TRUE);
			return (TRUE);
			break;
 
		case WM_DESTROY:
			KillTimer (hWnd, FILEVIEW_TIMER);
			break;

		case WM_NOTIFY:
			switch( wParam )
			{
				case IDC_FILEVIEW:
					return FileViewNotifyHandler(hWnd, message, wParam, lParam, win );
			}
			break;

		case WM_VSCROLL:
			{
				long x;
				long nScrollCode = (int) LOWORD(wParam); // scroll bar value 
				long nPos = (short int) HIWORD(wParam);  // scroll box position 
				HWND hwndScrollBar = (HWND) lParam;      // handle to scroll bar 

				x = GetScrollPos( GetDlgItem(hWnd, IDC_VIEWSCROLL), SB_CTL );

				//OutDebugs( "nPos: %d, x: %d, linesInWin: %d, scale: %d", nPos, x, winStats[win].linesInWin, winStats[win].scrollScale );

				switch( nScrollCode ){
					case SB_LINEDOWN:		nPos = x+1;		break;
					case SB_PAGEDOWN:		nPos = x+winStats[win].linesInWin/2;		break;
					case SB_LINEUP:			nPos = x-1;		break;
					case SB_PAGEUP:			nPos = x-winStats[win].linesInWin/2;		break;
					case SB_ENDSCROLL:
						return 1;
				}

				//SetScale( filename, 0, win, hDlg );
				if( nPos > winStats[win].scrollScale )
					nPos = winStats[win].scrollScale;
				if( nPos < 0 )
					nPos = 0;

				//OutDebugs( "pos=%d", nPos );
				UpdateFileView( hWnd, win,nPos );

				//if ( nScrollCode == SB_THUMBTRACK )
					SetScrollPos( GetDlgItem(hWnd, IDC_VIEWSCROLL), SB_CTL, nPos, 1 );
				return 0;
			}
			break;


		case WM_SIZE:
			SetWinSize( hWnd, LOWORD(lParam)-40, HIWORD(lParam)-37 );
			{
				long nPos = GetScrollPos( GetDlgItem(hWnd, IDC_VIEWSCROLL), SB_CTL );
				UpdateFileView( hWnd, win, nPos );
			}
			break;

		case WM_SIZING:
			{
				RECT *lprc = (LPRECT) lParam;
				long w,h, x,y;

				w = lprc->right - lprc->left;
				h = lprc->bottom - lprc->top;
				x = lprc->left;
				y = lprc->top;

				w = w -48;
				h = h -64;

				SetWinSize( hWnd, w, h );

			}
			break;

		case WM_COPY: 
			EditCopy(hWnd); 
			break; 

		case WM_COMMAND:
			switch (LOWORD(wParam) ) {
				case IDM_FM_COPY: 
					EditCopy(hWnd); 
					break; 
			}
			break;
		//default:
		//	return (DefWindowProc(hWnd, message, wParam, lParam));
	}

    return FALSE;
}