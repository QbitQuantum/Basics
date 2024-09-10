DLGBOOL CALLBACK defDemoDlg ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch ( message )
		{
		case WM_INITDIALOG:
			{
#ifdef DEBUGBASEUNIT
			char s[256];
			RECT rc, rcb;
			TEXTMETRIC tm;
			HFONT hfnt = (HFONT) SendMessage ( hWnd, WM_GETFONT, 0, 0 );
			HDC hdc = GetDC ( hWnd );
			rcb.left = rcb.top = 0;
			rcb.right = 4, rcb.bottom = 8;
			SelectObject ( hdc, hfnt );
			GetTextMetrics ( hdc, &tm );
			GetClientRect(hWnd, &rc);
			MapDialogRect ( hWnd, &rcb );
			sprintf ( s, "AW=%d (%d), Ht=%d (%d), %d x %d", 
					  tm.tmAveCharWidth, rcb.right, tm.tmHeight, rcb.bottom,
					  rc.right, rc.bottom );
			SetWindowText ( hWnd, s );
			ReleaseDC ( hWnd, hdc );
#endif
			}
			break;

		case WM_CTLCOLORSTATIC:
			{
			if( GetDlgCtrlID((HWND)lParam) == IDC_CTLCOLOR )
				{
				HBRUSH hbr = (HBRUSH)(LRESULT)DefWindowProc ( hWnd, message, wParam, lParam );
				SetTextColor ( (HDC)wParam, RGB(255,0,0) );
				SetBkColor ( (HDC)wParam, GetSysColor(COLOR_3DFACE) );
				return (DLGBOOL)hbr;
				}
			}
			return DefWindowProc ( hWnd, message, wParam, lParam );

		case WM_COMMAND:
			switch ( LOWORD(wParam) )
				{
				case IDOK:
					EndDialog ( hWnd, TRUE );
					break;

				case IDCANCEL:
					EndDialog ( hWnd, FALSE );
					break;
				}
			break;

		default:
			return FALSE;
		}

	return TRUE;
}