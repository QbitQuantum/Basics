INT_PTR CALLBACK
_about_dlg_proc(
		HWND	hwnd,
		UINT	message,
		WPARAM	wparam,
		LPARAM	lparam
	)
{
	_ctl_init ctl_links[ ] = 
	{
		{ DC_HOMEPAGE,  IDC_ABOUT_URL1, 0 },
		{ DC_FORUMPAGE, IDC_ABOUT_URL2, 0 }
	};
	static HICON h_icon;

	switch ( message )
	{
		case WM_DESTROY :
		{
			DestroyIcon(h_icon);
			return 0L;
		}
		break;			

		case WM_CLOSE : 
		{
			EndDialog(hwnd, 0);
			return 0L;
		}
		break;

		case WM_COMMAND : 
		{
			int id   = LOWORD(wparam);
			int code = HIWORD(wparam);
			int k;

			if ( code == EN_SETFOCUS )
			{
				SendMessage( (HWND)lparam, EM_SETSEL, -1, 0 );
			}

			if ( id == IDCANCEL || id == IDOK )
			{
				EndDialog(hwnd, 0);
			}
			for ( k = 0; k < array_num(ctl_links); k++ )
			{
				if ( id == ctl_links[k].id )
				{
					__execute(ctl_links[k].display);
				}
			}
		}
		break;

		case WM_SHOWWINDOW :
		{
			SetFocus( GetDlgItem(hwnd, IDC_EDIT_NOTICE) );
			SendMessage( GetDlgItem(hwnd, IDC_EDIT_NOTICE), EM_SETSEL, -1, 0 );
		}
		break;

		case WM_INITDIALOG : 
		{
			HWND    h_notice = GetDlgItem(hwnd, IDC_EDIT_NOTICE);
			wchar_t s_display[MAX_PATH];
			BYTE   *res;
			int     size, id_icon;
			int     k = 0;

			res = _extract_rsrc( IDI_ICON_TRAY, RT_GROUP_ICON, &size );

			id_icon = LookupIconIdFromDirectoryEx( res, TRUE, 48, 48, 0 );
			res = _extract_rsrc( id_icon, RT_ICON, &size );
 
			h_icon = CreateIconFromResourceEx( res, size, TRUE, 0x00030000, 48, 48, 0 );
			SendMessage( GetDlgItem(hwnd, IDC_ICON_MAIN), STM_SETICON, (WPARAM)h_icon, 0 );
			{
				HWND h_title = GetDlgItem( hwnd, IDC_ABOUT1 );

				_snwprintf(
					s_display, sizeof_w(s_display), L"%s %S", DC_NAME, DC_FILE_VER
					);

				SetWindowText( h_title, s_display );
				SetWindowText( h_notice,
					L"This program is free software: you can redistribute "
					L"it under the terms of the GNU General Public License "
					L"version 3 as published by the Free Software Foundation.\r\n\r\n"
					L"Contacts:\r\n"
					L"[email protected] (PGP key ID 0xC48251EB4F8E4E6E)\r\n\r\n"
					L"Special thanks to:\r\n"
					L"Aleksey Bragin and ReactOS Foundation\r\n\r\n"
					L"Portions of this software:\r\n"
					L"Copyright \xa9 1998, 2001, 2002 Brian Palmer\r\n"
					L"Copyright \xa9 2003, Dr Brian Gladman, Worcester, UK\r\n"
					L"Copyright \xa9 2006, Rik Snel <*****@*****.**>\r\n"
					L"Copyright \xa9 Vincent Rijmen <*****@*****.**>\r\n"
					L"Copyright \xa9 Antoon Bosselaers <*****@*****.**>\r\n"
					L"Copyright \xa9 Paulo Barreto <*****@*****.**>\r\n"
					L"Copyright \xa9 Tom St Denis <*****@*****.**>\r\n"
					L"Copyright \xa9 Juergen Schmied and Jon Griffiths\r\n"
					L"Copyright \xa9 Lynn McGuire\r\n"
					L"Copyright \xa9 Matthew Skala <*****@*****.**>\r\n"
					L"Copyright \xa9 Werner Koch\r\n"
					L"Copyright \xa9 Dag Arne Osvik <*****@*****.**>\r\n"
					L"Copyright \xa9 Herbert Valerio Riedel <*****@*****.**>\r\n"
					L"Copyright \xa9 Wei Dai\r\n"
					L"Copyright \xa9 Ruben Jesus Garcia Hernandez <*****@*****.**>\r\n"
					L"Copyright \xa9 Serge Trusov <*****@*****.**>"
				);

				SendMessage( h_title, WM_SETFONT, (WPARAM)__font_bold, 0 );
				for ( k = 0; k < array_num(ctl_links); k++ )
				{
					HWND h_ctl = GetDlgItem(hwnd, ctl_links[k].id);

					SetWindowLongPtr( h_ctl, GWL_USERDATA, (LONG_PTR)GetWindowLongPtr( h_ctl, GWL_WNDPROC ) );
					SetWindowLongPtr( h_ctl, GWL_WNDPROC, (LONG_PTR)_link_proc );

					SetWindowText( h_ctl, ctl_links[k].display );
					SendMessage( h_ctl, WM_SETFONT, (WPARAM)__font_link, 0 );
					{
						WINDOWINFO pwi;
						SIZE       size;
						HDC        h_dc = GetDC( h_ctl );

						SelectObject( h_dc, __font_link );
						GetTextExtentPoint32( h_dc, ctl_links[k].display, d32(wcslen(ctl_links[k].display)), &size );

						GetWindowInfo( h_ctl, &pwi );
						ScreenToClient( hwnd, pv(&pwi.rcClient) );

						MoveWindow( h_ctl, pwi.rcClient.left, pwi.rcClient.top, size.cx, size.cy, TRUE );
						ReleaseDC( h_ctl, h_dc );
					}
				}
				{
					dc_conf conf;
					if ( dc_get_conf_flags(&conf) == ST_OK )
					{
						wchar_t *s_using = L"Not supported";
						wchar_t *s_inset = L"Not supported";

						if ( conf.load_flags & DST_HW_CRYPTO )
						{
							s_using = (
								conf.conf_flags & CONF_HW_CRYPTO ? L"Enabled" : L"Disabled"
							);
							if ( conf.load_flags & DST_INTEL_NI ) s_inset = L"Intel® AES Instructions Set (AES-NI)";
							if ( conf.load_flags & DST_VIA_PADLOCK ) s_inset = L"The VIA PadLock Advanced Cryptography Engine (ACE)";
						}
						_snwprintf( s_display, sizeof_w(s_display), 
							L"Hardware Cryptography: %s\r\n"
							L"Instruction Set: %s",
							s_using, s_inset
						);
						SetWindowText( GetDlgItem(hwnd, IDC_EDIT_CIPHER_INFO), s_display );
						EnableWindow( GetDlgItem(hwnd, IDC_EDIT_CIPHER_INFO), conf.load_flags & DST_HW_CRYPTO );
					}
				}
			}
			SendMessage( h_notice, EM_SCROLLCARET, 0, 0 );
			SetForegroundWindow( hwnd );

			return 1L;
		}
		break;

		default:
		{
			int rlt = _draw_proc( message, lparam );
			if ( rlt != -1 )
			{
				return rlt;
			}
		}
	}
	return 0L;

}