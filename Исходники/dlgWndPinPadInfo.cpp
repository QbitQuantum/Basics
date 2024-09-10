LRESULT dlgWndPinpadInfo::ProcecEvent(	UINT		uMsg,			// Message For This Window
									WPARAM		wParam,			// Additional Message Information
									LPARAM		lParam )		// Additional Message Information
{
	PAINTSTRUCT ps;
	RECT rect;

	switch( uMsg )
	{

	case WM_PAINT:
		{
			m_hDC = BeginPaint( m_hWnd, &ps );

			HDC hdcMem;

			hdcMem = CreateCompatibleDC( m_hDC );

			HGDIOBJ oldObj = SelectObject( hdcMem , ImagePIN );

			GetClientRect( m_hWnd, &rect );
			//Size of the background Image
			MaskBlt( m_hDC, 4, 8,
				410, 261,	hdcMem, 0, 0,
				ImagePIN_Mask, 0, 0, MAKEROP4( SRCCOPY, 0x00AA0029 ) );
		
			
			SelectObject( hdcMem, oldObj );
			DeleteDC(hdcMem);

			GetClientRect( m_hWnd, &rect );
			rect.left += IMG_SIZE + 100;
			rect.top = 32;
			rect.right -= 8;
			rect.bottom = 136 - 8;
			SetBkColor( m_hDC, GetSysColor( COLOR_3DFACE ) );
			SelectObject( m_hDC, TextFont );
			DrawText( m_hDC, m_szHeader, -1, &rect, DT_WORDBREAK );

			//Change top header dimensions
			GetClientRect( m_hWnd, &rect );
			rect.left += IMG_SIZE + 100;
			rect.top = 60;
			rect.right -= 20;
			rect.bottom = rect.bottom - 60;
			SetBkColor( m_hDC, GetSysColor( COLOR_3DFACE ) );
			SelectObject( m_hDC, TextFont );
			DrawText( m_hDC, m_szMessage, -1, &rect, DT_WORDBREAK );

			EndPaint( m_hWnd, &ps );

			SetForegroundWindow( m_hWnd );

			return 0;

/*
			m_hDC = BeginPaint( m_hWnd, &ps );

			HDC hdcMem;

			GetClientRect( m_hWnd, &rect );
			rect.bottom = rect.top + IMG_SIZE + 8;//rect.bottom / 2;
			FillRect( m_hDC, &rect, CreateSolidBrush( RGB(255, 255, 255) ) );

			hdcMem = CreateCompatibleDC( m_hDC );
			SelectObject( hdcMem , ImagePIN );
			BitBlt( m_hDC, 4, 4, IMG_SIZE, IMG_SIZE, hdcMem,
				0, 0, SRCCOPY );

			DeleteDC(hdcMem);

			rect.left += 136;
			rect.top += 32;
			rect.right -= 8;
			rect.bottom = 136 - 8;
			//SetBkColor( m_hDC, GetSysColor( COLOR_3DFACE ) );
			DrawText( m_hDC, m_szHeader, -1, &rect, DT_WORDBREAK );

			GetClientRect( m_hWnd, &rect );
			rect.top=rect.top + IMG_SIZE + 8;

			rect.top = rect.top + 8;
			rect.bottom = rect.bottom - 8;
			rect.left = rect.left + 8;
			rect.right = rect.right - 8;
			FillRect( m_hDC, &rect, CreateSolidBrush( RGB(255, 255, 255) ) );

			rect.top = rect.top + 8;
			rect.bottom = rect.bottom - 8;
			rect.left = rect.left + 8;
			rect.right = rect.right - 8;
			DrawText( m_hDC, m_szMessage, -1, &rect, DT_WORDBREAK );

			EndPaint( m_hWnd, &ps );

			SetForegroundWindow( m_hWnd );

			return 0;
			*/
		}

		case WM_CREATE:
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndPinpadInfo::ProcecEvent WM_CLOSE (wParam=%X, lParam=%X)",wParam,lParam);

			HMENU hSysMenu;

			hSysMenu = GetSystemMenu( m_hWnd, FALSE);
			EnableMenuItem( hSysMenu, 2, MF_BYPOSITION | MF_GRAYED );

			return 1;
		}

		case WM_CLOSE:
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndPinpadInfo::ProcecEvent WM_CLOSE (wParam=%X, lParam=%X)",wParam,lParam);

			if( m_ulHandle )
			{
				unsigned long tmp = m_ulHandle;
				m_ulHandle = 0;
				DlgClosePinpadInfo( tmp );
			}
			return  0;
		}

		case WM_DESTROY: 
		{
			MWLOG(LEV_DEBUG, MOD_DLG, L"  --> dlgWndModal::ProcecEvent WM_DESTROY (wParam=%X, lParam=%X)",wParam,lParam);
			break;
		}

		default:
		{
			return DefWindowProc( m_hWnd, uMsg, wParam, lParam );
		}
	}
	return DefWindowProc( m_hWnd, uMsg, wParam, lParam );
}