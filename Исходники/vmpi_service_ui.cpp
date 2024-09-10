	virtual int		WindowProc( void *pWnd, int uMsg, long wParam, long lParam )
	{
		HWND hWnd = (HWND)pWnd;

		switch( uMsg )
		{
			// Right button brings up the popup menu.
			case MYWM_NOTIFYICON:
			{
				if ( lParam == WM_RBUTTONDOWN )
				{
					POINT cursorPos;
					GetCursorPos( &cursorPos );

					UpdatePopupMenuState();

					// Make a popup menu.
					SetForegroundWindow( hWnd );
					TrackPopupMenu( g_hPopupMenu, TPM_RIGHTALIGN | TPM_BOTTOMALIGN, cursorPos.x, cursorPos.y, 0, hWnd, NULL );
					return 0;
				}
				else if ( lParam == WM_LBUTTONDOWN )
				{
					// Left button brings up the console.
					g_pConsoleWnd->SetVisible( true );
					UpdatePopupMenuState();
					return 0;
				}
			}
			break;
			
			case WM_COMMAND:
			{
				switch( wParam )
				{
					case ID_ENABLE_WORKER:
					{
						char cPacket = VMPI_SERVICE_ENABLE;
						g_ConnMgr.SendPacket( -1, &cPacket, 1 );
					}
					break;

					case ID_DISABLE_WORKER:
					{
						char cPacket = VMPI_SERVICE_DISABLE;
						g_ConnMgr.SendPacket( -1, &cPacket, 1 );
					}
					break;
					
					case ID_KILLCURRENTJOB:
					{
						char cPacket = VMPI_KILL_PROCESS;
						g_ConnMgr.SendPacket( -1, &cPacket, 1 );
					}
					break;

					case ID_HIGHLIGHT_ICON_WHEN_BUSY:
					{
						g_bHighlightIconWhenBusy = !g_bHighlightIconWhenBusy;
						SaveStateToRegistry();
						UpdateAppIcon();
						UpdatePopupMenuState();
					}
					break;

					case ID_SCREENSAVER_MODE:
					{
						g_bScreensaverMode = !g_bScreensaverMode;
						char cPacket[2] = { VMPI_SERVICE_SCREENSAVER_MODE, g_bScreensaverMode };
						g_ConnMgr.SendPacket( -1, cPacket, sizeof( cPacket ) );
					}
					break;


					case ID_SHOW_CONSOLE_WINDOW:
					{
						g_pConsoleWnd->SetVisible( true );
						UpdatePopupMenuState();
					}
					break;

					case ID_HIDE_CONSOLE_WINDOW:
					{
						g_pConsoleWnd->SetVisible( false );
						UpdatePopupMenuState();
					}
					break;
				
					case ID_SET_PASSWORD:
					{
						DialogBox( g_hInstance, MAKEINTRESOURCE( IDD_SET_PASSWORD ), NULL, SetPasswordDlgProc );
					}
					break;

					case ID_EXIT_SERVICE:
					{
						// Quit the service app..
						char cPacket = VMPI_SERVICE_EXIT;
						g_ConnMgr.SendPacket( -1, &cPacket, 1 );

						// Stop showing the icon.
						g_ShellIconMgr.Term();

						// Wait for a bit for the connection to go away.
						DWORD startTime = GetTickCount();
						while ( GetTickCount()-startTime < 2000 )
						{
							g_ConnMgr.Update();
							if ( !g_ConnMgr.IsConnected() )
								break;
							else
								Sleep( 10 );
						}							
						
						// Quit the UI app.
						PostQuitMessage( 0 );
						return 1;
					}
					break;
				}
			}
			break;
		}	

		return DefWindowProc( (HWND)hWnd, uMsg, wParam, lParam );
	}