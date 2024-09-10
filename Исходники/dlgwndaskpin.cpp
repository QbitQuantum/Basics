LRESULT dlgWndAskPIN::ProcecEvent
			(	UINT		uMsg,			// Message For This Window
				WPARAM		wParam,			// Additional Message Information
				LPARAM		lParam )		// Additional Message Information
{
	PAINTSTRUCT ps;
	RECT rect;

	switch( uMsg )
	{ 
		case WM_COMMAND:
		{
			switch( LOWORD(wParam) )
			{
				case IDC_EDIT:
				{
					if( EN_CHANGE == HIWORD(wParam) )
					{
						long len = (long)SendMessage( GetDlgItem( m_hWnd, IDC_EDIT ), WM_GETTEXTLENGTH, 0, 0 );
						EnableWindow( GetDlgItem( m_hWnd, IDOK ), ( (unsigned int)len >= m_ulPinMinLen ) );
					}
					return TRUE;
				}

				case IDB_OK:
					GetPinResult();
					dlgResult = eIDMW::DLG_OK;
					close();
					return TRUE;

				case IDB_CANCEL:
					dlgResult = eIDMW::DLG_CANCEL;
					close();
					return TRUE;

				default:
					unsigned short tmp = LOWORD(wParam);
					if( tmp >= IDB_KeypadStart && tmp < IDB_KeypadEnd ) // Keypad Buttons
					{
						wchar_t nameBuf[128];
						SendMessage( GetDlgItem( m_hWnd, IDC_EDIT ), WM_GETTEXT, (WPARAM)(sizeof(nameBuf)), (LPARAM)nameBuf );
						size_t iPos = wcslen( nameBuf );
						if( iPos >= m_ulPinMaxLen )
							return TRUE;
						if( tmp == IDB_KeypadEnd - 1 ) // Keypad Button 0
						{
							nameBuf[ iPos++ ] = L'0';
						}
						else // Keypad Button 1 to 9
						{
							nameBuf[ iPos++ ] = 49 + tmp - IDB_KeypadStart;
						}
						nameBuf[ iPos++ ] = NULL;
						SendMessage( GetDlgItem( m_hWnd, IDC_EDIT ), WM_SETTEXT, 0, (LPARAM)nameBuf );
						return TRUE;
					}
					if( tmp == IDB_KeypadEnd ) // Keypad Button CE
					{
						SendMessage( GetDlgItem( m_hWnd, IDC_EDIT ), WM_SETTEXT, 0, (LPARAM)"" );
						//clear
					}
					return DefWindowProc( m_hWnd, uMsg, wParam, lParam );
			}
		}

		case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
			if( lpDrawItem->CtlType & ODT_BUTTON )
			{
				//MWLOG(LEV_DEBUG, MOD_DLG, L" dlgWndAskPIN : Virtual pinpad - WM_DRAWITEM lParam=%x, wParam=%ld",lParam,wParam);
				//MWLOG(LEV_DEBUG, MOD_DLG, L" dlgWndAskPIN : Virtual pinpad - Entering WM_DRAWITEM lpDrawItem->hDC=%ld",lpDrawItem->hDC);

				FillRect( lpDrawItem->hDC, &lpDrawItem->rcItem, CreateSolidBrush( GetSysColor( COLOR_3DFACE ) ) );
				//MWLOG(LEV_DEBUG, MOD_DLG, L" dlgWndAskPIN : Virtual pinpad - WM_DRAWITEM top=%ld, bottom=%ld, left=%ld, right=%ld",
					//lpDrawItem->rcItem.top,lpDrawItem->rcItem.bottom,lpDrawItem->rcItem.left,lpDrawItem->rcItem.right);

				HDC hdcMem = CreateCompatibleDC( lpDrawItem->hDC );
				SelectObject( hdcMem , ImageKP_BTN[11] );
				MaskBlt( lpDrawItem->hDC, (lpDrawItem->rcItem.right - KP_BTN_SIZE) / 2, (lpDrawItem->rcItem.bottom - KP_BTN_SIZE) / 2,
					KP_BTN_SIZE, KP_BTN_SIZE, hdcMem, 0, 0,
					ImageKP_BTN_Mask, 0, 0, MAKEROP4( SRCCOPY, 0x00AA0029 ) );

				unsigned int iNum = 0;
				if( lpDrawItem->CtlID == IDB_KeypadEnd )
				{
					iNum = 10;
				}
				else if( lpDrawItem->CtlID >= IDB_KeypadStart && lpDrawItem->CtlID < IDB_KeypadEnd -2 )
				{
					iNum = lpDrawItem->CtlID - IDB_KeypadStart +1;
				}
				//MWLOG(LEV_DEBUG, MOD_DLG, L" dlgWndAskPIN : Virtual pinpad - WM_DRAWITEM iNum=%ld",iNum);

				SelectObject( hdcMem , ImageKP_BTN[iNum] );
				BitBlt( lpDrawItem->hDC, (lpDrawItem->rcItem.right - KP_LBL_SIZE) / 2, (lpDrawItem->rcItem.bottom - KP_LBL_SIZE) / 2, 
						KP_LBL_SIZE, KP_LBL_SIZE, hdcMem, 0, 0, SRCCOPY );
				DeleteDC(hdcMem);

				if( lpDrawItem->itemState & ODS_SELECTED )
					DrawEdge( lpDrawItem->hDC, &lpDrawItem->rcItem, EDGE_RAISED, BF_RECT );
				
				if( lpDrawItem->itemState & ODS_HOTLIGHT )
					DrawEdge( lpDrawItem->hDC, &lpDrawItem->rcItem, EDGE_SUNKEN, BF_RECT );
				
				if( lpDrawItem->itemState & ODS_FOCUS )
				{
					GetClientRect( lpDrawItem->hwndItem, &rect );
					rect.left += 2;
					rect.right -= 2;
					rect.top += 2;
					rect.bottom -= 2;
					DrawFocusRect( lpDrawItem->hDC, &rect );
				}
				//MWLOG(LEV_DEBUG, MOD_DLG, L" dlgWndAskPIN : Virtual pinpad - Leaving WM_DRAWITEM lpDrawItem->hDC=%ld",lpDrawItem->hDC);
				return TRUE;
			}
			break;
		}

		case WM_SIZE:
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndAskPIN::ProcecEvent WM_SIZE (wParam=%X, lParam=%X)",wParam,lParam);

			if( IsIconic( m_hWnd ) )
				return 0;
			break;
		}

		case WM_PAINT:
		{
			//MWLOG(LEV_DEBUG, MOD_DLG, L" dlgWndAskPIN : WM_PAINT");
			m_hDC = BeginPaint( m_hWnd, &ps );

			HDC hdcMem;

			hdcMem = CreateCompatibleDC( m_hDC );

			HGDIOBJ oldObj = SelectObject( hdcMem , ImagePIN );

			GetClientRect( m_hWnd, &rect );
			MaskBlt( m_hDC, 4, m_KeypadHeight + 8,
				IMG_SIZE, IMG_SIZE,	hdcMem, 0, 0,
				ImagePIN_Mask, 0, 0, MAKEROP4( SRCCOPY, 0x00AA0029 ) );
		
			
			SelectObject( hdcMem, oldObj );
			DeleteDC(hdcMem);

			if( m_UseKeypad )
			{
				GetClientRect( m_hWnd, &rect );
				rect.left += 8;
				rect.right -= 8;
				rect.top += 8;
				rect.bottom = m_KeypadHeight;

				DrawEdge( m_hDC, &rect, EDGE_RAISED, BF_RECT );
			}

			GetClientRect( m_hWnd, &rect );
			rect.left += IMG_SIZE + 16;
			rect.top = m_KeypadHeight + 8;
			rect.right -= 8;
			rect.bottom = rect.bottom - 40;
			SetBkColor( m_hDC, GetSysColor( COLOR_3DFACE ) );
			SelectObject( m_hDC, TextFont );
			DrawText( m_hDC, szHeader, -1, &rect, DT_WORDBREAK );

			EndPaint( m_hWnd, &ps );

			SetForegroundWindow( m_hWnd );

			return 0;
		}

		case WM_ACTIVATE:
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndAskPIN::ProcecEvent WM_ACTIVATE (wParam=%X, lParam=%X)",wParam,lParam);
			break;
		}

		case WM_NCACTIVATE:
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndAskPIN::ProcecEvent WM_NCACTIVATE (wParam=%X, lParam=%X)",wParam,lParam);

			//if( !IsIconic( m_hWnd ) && m_ModalHold && Active_hWnd == m_hWnd )
			//{
			//	ShowWindow( m_hWnd, SW_SHOW );
			//	SetFocus( m_hWnd );
			//	return 0;
			//}
			if(!wParam)
			{
				SetFocus( m_hWnd );
				return 0;
			}
			break;
		}

		case WM_SETFOCUS:
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndAskPIN::ProcecEvent WM_SETFOCUS (wParam=%X, lParam=%X)",wParam,lParam);
			break;
		}

		case WM_KILLFOCUS:
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndAskPIN::ProcecEvent WM_KILLFOCUS (wParam=%X, lParam=%X)",wParam,lParam);

			//if( !IsIconic( m_hWnd ) && m_ModalHold && Active_hWnd == m_hWnd )
			//{
			//	if( GetParent((HWND)wParam ) != m_hWnd )
			//	{
			//		SetFocus( m_hWnd );
			//		return 0;
			//	}
			//}
			break;
		}

		case WM_CREATE:
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndAskPIN::ProcecEvent WM_CREATE (wParam=%X, lParam=%X)",wParam,lParam);

			HMENU hSysMenu;

			hSysMenu = GetSystemMenu( m_hWnd, FALSE );
			EnableMenuItem( hSysMenu, 3, MF_BYPOSITION | MF_GRAYED );
			SendMessage( m_hWnd, DM_SETDEFID, (WPARAM) IDC_EDIT, (LPARAM) 0); 

			return DefWindowProc( (HWND)((CREATESTRUCT *)lParam)->lpCreateParams, uMsg, wParam, lParam );
		}

		case WM_CLOSE:
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndAskPIN::ProcecEvent WM_CLOSE (wParam=%X, lParam=%X)",wParam,lParam);

			if( IsIconic( m_hWnd ) )
				return DefWindowProc( m_hWnd, uMsg, wParam, lParam );

			ShowWindow( m_hWnd, SW_MINIMIZE );
			return 0;
		}

		case WM_DESTROY: 
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndAskPIN::ProcecEvent WM_DESTROY (wParam=%X, lParam=%X)",wParam,lParam);
			break;
		}

		default:
		{
			return DefWindowProc( m_hWnd, uMsg, wParam, lParam );
		}
	}
	return DefWindowProc( m_hWnd, uMsg, wParam, lParam );
}