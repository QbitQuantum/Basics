LRESULT CALLBACK ScanWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch ( msg )
    {
		case WM_CREATE:
		{
			RECT rc;
			GetClientRect( hWnd, &rc );

			g_hWnd_tab = CreateWindowEx( WS_EX_CONTROLPARENT, WC_TABCONTROL, NULL, WS_CHILD | WS_CLIPCHILDREN | WS_TABSTOP | WS_VISIBLE, 10, 10, rc.right - 20, rc.bottom - 50, hWnd, NULL, NULL, NULL );

			TCITEMA ti = { 0 };
			ti.mask = TCIF_PARAM | TCIF_TEXT;	// The tab will have text and an lParam value.
			ti.pszText = "Scan Directory";
			ti.lParam = ( LPARAM )0;
			SendMessageA( g_hWnd_tab, TCM_INSERTITEMA, 0, ( LPARAM )&ti );	// Insert a new tab at the end.

			ti.pszText = "Load ESE Database";
			ti.lParam = ( LPARAM )1;
			SendMessageA( g_hWnd_tab, TCM_INSERTITEMA, 1, ( LPARAM )&ti );	// Insert a new tab at the end.

			SendMessage( g_hWnd_tab, WM_SETFONT, ( WPARAM )hFont, 0 );

			// Set the tab's font before we get the item rect so that we have an accurate height.
			RECT rc_tab;
			GetClientRect( g_hWnd_tab, &rc );
			SendMessage( g_hWnd_tab, TCM_GETITEMRECT, 0, ( LPARAM )&rc_tab );

			g_hWnd_scan_tab = CreateWindowEx( WS_EX_CONTROLPARENT, L"scan_tab", NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE, 10, ( rc_tab.bottom + rc_tab.top ) + 8, rc.right - 20, rc.bottom - ( ( rc_tab.bottom + rc_tab.top ) + 16 ), g_hWnd_tab, NULL, NULL, NULL );

			g_hWnd_btn_details = CreateWindowA( WC_BUTTONA, "Show Details \xBB", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 0, 0, 0, 0, hWnd, ( HMENU )BTN_DETAILS, NULL, NULL );

			g_hWnd_btn_scan = CreateWindowA( WC_BUTTONA, "Scan", BS_DEFPUSHBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE, 0, 0, 0, 0, hWnd, ( HMENU )BTN_SCAN, NULL, NULL );
			g_hWnd_btn_cancel = CreateWindowA( WC_BUTTONA, "Cancel", WS_CHILD | WS_TABSTOP | WS_VISIBLE, 0, 0, 0, 0, hWnd, ( HMENU )BTN_CANCEL, NULL, NULL );

			// Make pretty font.
			SendMessage( g_hWnd_btn_details, WM_SETFONT, ( WPARAM )hFont, 0 );
			SendMessage( g_hWnd_btn_scan, WM_SETFONT, ( WPARAM )hFont, 0 );
			SendMessage( g_hWnd_btn_cancel, WM_SETFONT, ( WPARAM )hFont, 0 );

			return 0;
		}
		break;

		case WM_CHANGE_CURSOR:
		{
			// SetCursor must be called from the window thread.
			if ( wParam == TRUE )
			{
				wait_cursor = LoadCursor( NULL, IDC_APPSTARTING );	// Arrow + hourglass.
				SetCursor( wait_cursor );
			}
			else
			{
				SetCursor( LoadCursor( NULL, IDC_ARROW ) );	// Default arrow.
				wait_cursor = NULL;
			}
		}
		break;

		case WM_SETCURSOR:
		{
			if ( wait_cursor != NULL )
			{
				SetCursor( wait_cursor );	// Keep setting our cursor if it reverts back to the default.
				return TRUE;
			}

			DefWindowProc( hWnd, msg, wParam, lParam );
			return FALSE;
		}
		break;

		case WM_COMMAND:
		{
			switch( LOWORD( wParam ) )
			{
				case IDOK:
				case BTN_SCAN:
				{
					if ( g_kill_scan == false )
					{
						EnableWindow( g_hWnd_btn_scan, FALSE );
						g_kill_scan = true;
						break;
					}

					int length = SendMessage( g_hWnd_path[ tab_index ], WM_GETTEXT, MAX_PATH, ( LPARAM )g_filepath );
					if ( length >= 3 )
					{
						// We need to have at least the drive path. Example: "C:\"
						if ( g_filepath[ 1 ] == L':' && g_filepath[ 2 ] == L'\\' )
						{
							// Remove any trailing "\" from the path.
							if ( g_filepath[ length - 1 ] == L'\\' )
							{
								g_filepath[ length - 1 ] = '\0';
							}

							// Now get our extension filters.
							length = SendMessage( g_hWnd_extensions[ tab_index ], WM_GETTEXT, MAX_PATH, ( LPARAM )( g_extension_filter + 1 ) );
							if ( length > 0 )
							{
								g_extension_filter[ 0 ] = L'|';					// Append the delimiter to the beginning of the string.
								g_extension_filter[ length + 1 ] = L'|';		// Append the delimiter to the end of the string.
								g_extension_filter[ length + 2 ] = L'\0';
								_wcslwr_s( g_extension_filter, length + 3 );	// Set them to lowercase for later comparison.
							}
							else
							{
								g_extension_filter[ 0 ] = L'\0';
							}

							g_include_folders = SendMessage( g_hWnd_chk_folders[ tab_index ], BM_GETCHECK, 0, 0 ) ? true : false;

							g_retrieve_extended_information = SendMessage( g_hWnd_extended_information, BM_GETCHECK, 0, 0 ) ? true : false;

							scan_type = tab_index;	// scan_type will allow the correct windows to update regardless of the selected tab.

							// If use_scanner == false, then read the ese database.
							CloseHandle( ( HANDLE )_beginthreadex( NULL, 0, &map_entries, ( void * )scan_type, 0, NULL ) );
						}
						else
						{
							MessageBoxA( hWnd, "You must specify a valid path.", PROGRAM_CAPTION_A, MB_APPLMODAL | MB_ICONWARNING );
						}
					}
				}
				break;

				case BTN_CANCEL:
				{
					SendMessage( hWnd, WM_CLOSE, 0, 0 );
				}
				break;

				case BTN_DETAILS:
				{
					g_show_details = !g_show_details;

					// Hiding the details will allow for a faster scan since it doesn't have to update our controls.
					if ( g_show_details == true )
					{
						SendMessageA( g_hWnd_btn_details, WM_SETTEXT, 0, ( LPARAM )"Hide Details \xAB" );
						ShowWindow( g_hWnd_static3, SW_SHOW );
						ShowWindow( g_hWnd_static4, SW_SHOW );
						ShowWindow( g_hWnd_static5, SW_SHOW );
						ShowWindow( g_hWnd_hashing[ tab_index ], SW_SHOW );
						ShowWindow( g_hWnd_static_hash[ tab_index ], SW_SHOW );
						ShowWindow( g_hWnd_static_count[ tab_index ], SW_SHOW );
					}
					else
					{
						SendMessageA( g_hWnd_btn_details, WM_SETTEXT, 0, ( LPARAM )"Show Details \xBB" );
						ShowWindow( g_hWnd_static3, SW_HIDE );
						ShowWindow( g_hWnd_static4, SW_HIDE );
						ShowWindow( g_hWnd_static5, SW_HIDE );
						ShowWindow( g_hWnd_hashing[ 0 ], SW_HIDE );
						ShowWindow( g_hWnd_hashing[ 1 ], SW_HIDE );
						ShowWindow( g_hWnd_static_hash[ 0 ], SW_HIDE );
						ShowWindow( g_hWnd_static_hash[ 1 ], SW_HIDE );
						ShowWindow( g_hWnd_static_count[ 0 ], SW_HIDE );
						ShowWindow( g_hWnd_static_count[ 1 ], SW_HIDE );
					}

					// Adjust the window height.
					RECT rc;
					GetWindowRect( hWnd, &rc );
					SetWindowPos( hWnd, NULL, 0, 0, rc.right - rc.left, MIN_HEIGHT - ( g_show_details == true ? 25 : 115 ), SWP_NOMOVE );
				}
				break;
			}

			return 0;
		}
		break;

		case WM_NOTIFY:
		{
			// Get our listview codes.
			switch ( ( ( LPNMHDR )lParam )->code )
			{
				case TCN_SELCHANGING:		// The tab that's about to lose focus
				{
					NMHDR *nmhdr = ( NMHDR * )lParam;

					int index = SendMessage( nmhdr->hwndFrom, TCM_GETCURSEL, 0, 0 );		// Get the selected tab
					if ( index == 0 || index == 1 )
					{
						ShowWindow( g_hWnd_path[ index ], SW_HIDE );
						ShowWindow( g_hWnd_extensions[ index ], SW_HIDE );
						ShowWindow( g_hWnd_chk_folders[ index ], SW_HIDE );
						ShowWindow( g_hWnd_hashing[ index ], SW_HIDE );
						ShowWindow( g_hWnd_static_hash[ index ], SW_HIDE );
						ShowWindow( g_hWnd_static_count[ index ], SW_HIDE );

						if ( index == 1 )
						{
							ShowWindow( g_hWnd_extended_information, SW_HIDE );
						}
					}

					return FALSE;
				}
				break;

				case TCN_SELCHANGE:			// The tab that gains focus
                {
					NMHDR *nmhdr = ( NMHDR * )lParam;

					int index = SendMessage( nmhdr->hwndFrom, TCM_GETCURSEL, 0, 0 );		// Get the selected tab
					if ( index == 0 || index == 1 )
					{
						SendMessageA( g_hWnd_static1, WM_SETTEXT, 0, ( LPARAM )( index == 0 ? "Initial scan directory:" : "Extensible Storage Engine Database file:" ) );

						ShowWindow( g_hWnd_path[ index ], SW_SHOW );
						ShowWindow( g_hWnd_extensions[ index ], SW_SHOW );
						ShowWindow( g_hWnd_chk_folders[ index ], SW_SHOW );

						if ( g_show_details == true )
						{
							ShowWindow( g_hWnd_hashing[ index ], SW_SHOW );
							ShowWindow( g_hWnd_static_hash[ index ], SW_SHOW );
							ShowWindow( g_hWnd_static_count[ index ], SW_SHOW );
						}

						if ( index == 1 )
						{
							ShowWindow( g_hWnd_extended_information, SW_SHOW );
						}

						// If we're scanning, then enable the scan button. Otherwise, check for a valid path.
						EnableWindow( g_hWnd_btn_scan, ( g_kill_scan == false || SendMessage( g_hWnd_path[ index ], WM_GETTEXTLENGTH, 0, 0 ) >= 3 ) ? TRUE : FALSE );

						tab_index = index;
					}

					return FALSE;
                }
				break;
			}

			return FALSE;
		}
		break;

		case WM_SIZE:
		{
			RECT rc;
			GetClientRect( hWnd, &rc );

			// Allow our controls to move in relation to the parent window.
			HDWP hdwp = BeginDeferWindowPos( 4 );
			DeferWindowPos( hdwp, g_hWnd_tab, HWND_TOP, 10, 10, rc.right - 20, rc.bottom - 50, SWP_NOZORDER );
			DeferWindowPos( hdwp, g_hWnd_btn_details, HWND_TOP, 10, rc.bottom - 32, 100, 23, SWP_NOZORDER );
			DeferWindowPos( hdwp, g_hWnd_btn_scan, HWND_TOP, rc.right - 175, rc.bottom - 32, 80, 23, SWP_NOZORDER );
			DeferWindowPos( hdwp, g_hWnd_btn_cancel, HWND_TOP, rc.right - 90, rc.bottom - 32, 80, 23, SWP_NOZORDER );
			EndDeferWindowPos( hdwp );

			RECT rc_tab;
			GetClientRect( g_hWnd_tab, &rc );
			SendMessage( g_hWnd_tab, TCM_GETITEMRECT, 0, ( LPARAM )&rc_tab );

			SetWindowPos( g_hWnd_scan_tab, HWND_TOP, 10, ( rc_tab.bottom + rc_tab.top ) + 8, rc.right - 20, rc.bottom - ( ( rc_tab.bottom + rc_tab.top ) + 16 ), SWP_NOZORDER );

			return 0;
		}
		break;

		case WM_GETMINMAXINFO:
		{
			// Set the minimum dimensions that the window can be sized to.
			( ( MINMAXINFO * )lParam )->ptMinTrackSize.x = MIN_WIDTH;
			( ( MINMAXINFO * )lParam )->ptMinTrackSize.y = MIN_HEIGHT - ( g_show_details == true ? 25 : 115 );
			( ( MINMAXINFO * )lParam )->ptMaxTrackSize.y = MIN_HEIGHT - ( g_show_details == true ? 25 : 115 );

			return 0;
		}
		break;

		case WM_ACTIVATE:
		{
			// 0 = inactive, > 0 = active
			g_hWnd_active = ( wParam == 0 ? NULL : hWnd );

            return FALSE;
		}
		break;

		case WM_CLOSE:
		{
			g_kill_scan = true;

			// Reenable the main window.
			EnableWindow( g_hWnd_main, TRUE );
			SetForegroundWindow( g_hWnd_main );

			ShowWindow( hWnd, SW_HIDE );
		}
		break;

		case WM_ALERT:
		{
			MessageBoxA( hWnd, ( LPCSTR )lParam, PROGRAM_CAPTION_A, MB_APPLMODAL | ( wParam == 1 ? MB_ICONINFORMATION : MB_ICONWARNING ) | MB_SETFOREGROUND );
		}
		break;

		case WM_PROPAGATE:
		{
			if ( wParam == 1 )
			{
				g_kill_scan = false;

				EnableWindow( g_hWnd_path[ 0 ], FALSE );
				EnableWindow( g_hWnd_path[ 1 ], FALSE );
				EnableWindow( g_hWnd_load, FALSE );
				EnableWindow( g_hWnd_extensions[ 0 ], FALSE );
				EnableWindow( g_hWnd_extensions[ 1 ], FALSE );
				EnableWindow( g_hWnd_chk_folders[ 0 ], FALSE );
				EnableWindow( g_hWnd_chk_folders[ 1 ], FALSE );
				EnableWindow( g_hWnd_extended_information, FALSE );

				// We're scanning. Set the button's text to "Stop".
				SendMessageA( g_hWnd_btn_scan, WM_SETTEXT, 0, ( LPARAM )"Stop" );
			}
			else if ( wParam == 2 )
			{
				// Clear the current file info if we finished the scan without stopping.
				if ( g_kill_scan == false )
				{
					SendMessage( g_hWnd_hashing[ scan_type ], WM_SETTEXT, 0, 0 );
					SendMessageA( g_hWnd_static_hash[ scan_type ], WM_SETTEXT, 0, 0 );
				}

				g_kill_scan = true;

				EnableWindow( g_hWnd_path[ 0 ], TRUE );
				EnableWindow( g_hWnd_path[ 1 ], TRUE );
				EnableWindow( g_hWnd_load, TRUE );
				EnableWindow( g_hWnd_extensions[ 0 ], TRUE );
				EnableWindow( g_hWnd_extensions[ 1 ], TRUE );
				EnableWindow( g_hWnd_chk_folders[ 0 ], TRUE );
				EnableWindow( g_hWnd_chk_folders[ 1 ], TRUE );
				EnableWindow( g_hWnd_extended_information, TRUE );

				// We've stopped/finished scanning. Set the button's text to "Scan".
				SendMessageA( g_hWnd_btn_scan, WM_SETTEXT, 0, ( LPARAM )"Scan" );
				EnableWindow( g_hWnd_btn_scan, ( SendMessage( g_hWnd_path[ tab_index ], WM_GETTEXTLENGTH, 0, 0 ) >= 3 ) ? TRUE : FALSE );
			}
			else if ( wParam == 3 )
			{
				SendMessage( g_hWnd_hashing[ scan_type ], WM_SETTEXT, 0, lParam );
			}
			else if ( wParam == 4 )
			{
				SendMessageA( g_hWnd_static_hash[ scan_type ], WM_SETTEXT, 0, lParam );
			}
			else if ( wParam == 5 )
			{
				SendMessageA( g_hWnd_static_count[ scan_type ], WM_SETTEXT, 0, lParam );
			}
			else
			{
				g_kill_scan = true;

				// Reset text information.
				SendMessage( g_hWnd_hashing[ 0 ], WM_SETTEXT, 0, 0 );
				SendMessage( g_hWnd_hashing[ 1 ], WM_SETTEXT, 0, 0 );
				SendMessageA( g_hWnd_static_hash[ 0 ], WM_SETTEXT, 0, 0 );
				SendMessageA( g_hWnd_static_hash[ 1 ], WM_SETTEXT, 0, 0 );
				SendMessageA( g_hWnd_static_count[ 0 ], WM_SETTEXT, 0, 0 );
				SendMessageA( g_hWnd_static_count[ 1 ], WM_SETTEXT, 0, 0 );
				SendMessageA( g_hWnd_btn_scan, WM_SETTEXT, 0, ( LPARAM )"Scan" );
				EnableWindow( g_hWnd_btn_scan, ( SendMessage( g_hWnd_path[ tab_index ], WM_GETTEXTLENGTH, 0, 0 ) >= 3 ) ? TRUE : FALSE );

				SendMessage( g_hWnd_tab, TCM_SETCURFOCUS, 0, 0 );

				// Disable the main window.
				EnableWindow( g_hWnd_main, FALSE );

				// Set the window above all other windows.
				SetForegroundWindow( hWnd );
				SetWindowPos( hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
				ShowWindow( hWnd, SW_SHOW );
			}
		}
		break;

		default:
		{
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
		break;
	}
	return TRUE;
}