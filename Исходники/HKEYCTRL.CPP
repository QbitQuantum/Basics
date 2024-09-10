LRESULT PASCAL HotKeyWndProc(HWND hWnd, register UINT uMsg, register WPARAM wParam, register LPARAM lParam)
{
	CM_HOTKEY *pHotKey = ( CM_HOTKEY * ) GetProp( hWnd, _T("HOTKEY") ); 

	switch ( uMsg )
	{
		case WM_CREATE:
			{
				CM_HOTKEY *pHotKey = new CM_HOTKEY;
				ZeroMemory( pHotKey, sizeof( CM_HOTKEY ) );
				SetProp( hWnd, _T("HOTKEY"), pHotKey ); 
				SetWindowLong( hWnd, GWL_EXSTYLE, GetWindowLong( hWnd, GWL_EXSTYLE ) | WS_EX_CLIENTEDGE );
				SetWindowPos( hWnd, NULL, -1, -1, -1, -1, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_DRAWFRAME );
				SendMessage( hWnd, UM_UPDATEHOTKEYTEXT, 0, 0 );
				g_bEatCommand = FALSE;
				break;
			}

		case WM_DESTROY:
			{
				RemoveProp( hWnd, _T("HOTKEY") );
				delete pHotKey;
				break;
			}

		case UM_TAKEBACKFOCUS:
		{
			if ( GetFocus() != hWnd )
			{
				SetFocus( hWnd );
			}
			g_bEatCommand = FALSE;
			return 0;
		}

		case HOTM_QUERYEATCOMMAND:
		{
			return g_bEatCommand;
		}

		case UM_UPDATEHOTKEYTEXT:
		{
			TCHAR szHotKey[ 100 ];
			*szHotKey = '\0';
			GetHotKeyString( *pHotKey, szHotKey );
			g_bCanUpdateText = TRUE;
			SetWindowText( hWnd, szHotKey );
			g_bCanUpdateText = FALSE;
			SendMessage( hWnd, EM_SETSEL, 1000, 1000 );

			return 0;
		}

		case UM_INTERNALSETHOTKEY:
		{
			UINT nVirtKey = wParam;
			switch ( nVirtKey )
			{
				case VK_CONTROL:
				case VK_SHIFT:
				case VK_MENU:
				{
					nVirtKey = 0;
				}
			}

			if ( nVirtKey )
			{
				CM_HOTKEY cmHotKey = *pHotKey;
				BYTE byModifiers = 0;
				byModifiers |= ( ( GetKeyState( VK_CONTROL ) < 0 ) ? HOTKEYF_CONTROL : 0 );
				byModifiers |= ( ( GetKeyState( VK_SHIFT ) < 0 ) ? HOTKEYF_SHIFT : 0 );
				byModifiers |= ( ( GetKeyState( VK_MENU ) < 0 ) ? HOTKEYF_ALT : 0 );

				if ( cmHotKey.byModifiers1 || cmHotKey.nVirtKey1 )
				{
					if ( !cmHotKey.byModifiers2 && !cmHotKey.nVirtKey2 )
					{
						cmHotKey.byModifiers2 = byModifiers;
						cmHotKey.nVirtKey2 = nVirtKey;
					}
					else
					{
						cmHotKey.byModifiers2 = 0;
						cmHotKey.nVirtKey2 = 0;
						goto set_loword;
					}
				}
				else
				{
					set_loword:
					ASSERT( !cmHotKey.byModifiers2 && !cmHotKey.nVirtKey2 );
					cmHotKey.byModifiers1 = byModifiers;
					cmHotKey.nVirtKey1 = nVirtKey;
				}

				SendMessage( hWnd, HOTM_SETHOTKEY, 0, ( LPARAM ) &cmHotKey );
			}
			return 0;
		}

		case HOTM_SETHOTKEY:
		{
			if ( lParam )
			{
				*pHotKey = *( CM_HOTKEY * ) lParam;
			}
			else
			{
				CM_HOTKEY cmHotKey = { 0, 0, 0, 0 };
				*pHotKey = cmHotKey;
			}
			SendMessage( hWnd, UM_UPDATEHOTKEYTEXT, 0, 0 );
			return 0;
		}

		case HOTM_GETHOTKEY:
		{
			*( ( CM_HOTKEY * ) lParam ) = *pHotKey;
			break;
		}

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			g_bEatCommand = TRUE;
			SendMessage( hWnd, UM_INTERNALSETHOTKEY, wParam, lParam );
			PostMessage( hWnd, UM_TAKEBACKFOCUS, 0, 0 );
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
		}
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
		}
		case WM_CHAR:
		case WM_SYSCHAR:
		{
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
		}

	case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:
		case WM_CONTEXTMENU:
		{
			SetFocus( hWnd );
			return 0;
		}

		case WM_SYSCOMMAND:
		{
			return 0;
		}
		case WM_SETTEXT:
		{
			if ( g_bCanUpdateText )
		{
				break;
			}
			else
			{
				return 0;
			}
		}
		case WM_GETDLGCODE:
		{
			DWORD dwDlgCode = DLGC_WANTARROWS | DLGC_WANTCHARS | DLGC_WANTTAB;
			if ( HAS_FLAG( GetWindowLong( hWnd, GWL_STYLE ), ES_WANTRETURN ) )
			{
				dwDlgCode |= DLGC_WANTALLKEYS;
			}
			return dwDlgCode;
		}
	}

	// Other than the above messages, the hotkey control behaves identical to an edit control
	WNDCLASS wcEdit;
	VERIFY( GetClassInfo( ( HINSTANCE ) GetWindowLong( hWnd, GWL_HINSTANCE ), _T("EDIT"), &wcEdit ) );
#ifdef _ACTIVEX
	return CallWindowProc( wcEdit.lpfnWndProc, hWnd, uMsg, wParam, lParam );
#else
	#if _MSC_VER  > 1100 
		return CallWindowProc( ( WNDPROC ) wcEdit.lpfnWndProc, hWnd, uMsg, wParam, lParam );
	#else
		return CallWindowProc( ( FARPROC ) wcEdit.lpfnWndProc, hWnd, uMsg, wParam, lParam );
	#endif

#endif
}