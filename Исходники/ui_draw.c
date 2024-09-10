void _draw_listview(
		LPDRAWITEMSTRUCT itst
	)
{
	DRAWTEXTPARAMS dtp         = { sizeof(dtp) };
	LVCOLUMN       lvc         = { sizeof(lvc) };
	wchar_t        s_text[200] = { 0 };
	int            cx, cy, k   = 0;
	int            offset      = 0;
	int            icon;
	BOOL           is_root;
	int            col_cnt     = Header_GetItemCount( ListView_GetHeader( itst->hwndItem ) );
	LVITEM         lvitem      = { LVIF_TEXT | LVIF_PARAM, itst->itemID, 0, 0, 0, s_text, countof(s_text) };
	COLORREF       bgcolor     = ListView_GetBkColor( itst->hwndItem );

	ListView_GetItem( itst->hwndItem, &lvitem );
	is_root = _is_root_item( lvitem.lParam );

	{
		void *user_data = wnd_get_long( __lists[HMAIN_DRIVES], GWL_USERDATA );
		if (user_data != NULL)
		{
			MessageBox( __dlg, s_text, NULL, 0 );
		}
	}

	if ( ( itst->itemState & ODS_SELECTED ) && IsWindowEnabled( itst->hwndItem ) /*&& ( lvitem.lParam != NULL )*/ ) 
	{
		if ( GetFocus( ) == itst->hwndItem )
		{
			bgcolor = CL_WHITE;
		} else {
			bgcolor = _cl( COLOR_BTNFACE, 80 );
		}
	}
	if ( is_root ) 
	{
		bgcolor = _cl( COLOR_BTNSHADOW, 60 );
	}
	if ( _is_marked_item(lvitem.lParam) ) 
	{
		bgcolor = _cl( COLOR_BTNSHADOW, 35 );
	}
	
	_fill( itst->hDC, &itst->rcItem, bgcolor );

	for ( ; k < col_cnt; k++ )
	{
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_IMAGE;
		ListView_GetColumn( itst->hwndItem, k, &lvc );

		itst->rcItem.left  = k ? itst->rcItem.right : 0;
		itst->rcItem.right = itst->rcItem.left + lvc.cx;

		lvitem.iItem       = itst->itemID; 
		lvitem.iSubItem    = k;

		ListView_GetItem( itst->hwndItem, &lvitem );
		dtp.iLeftMargin = dtp.iRightMargin = 5;		

		if ( (!itst->rcItem.left) && _is_icon_show( itst->hwndItem, k ) )
		{
			ImageList_GetIconSize( __dsk_img, &cx, &cy );
			offset = lvitem.lParam && !is_root ? 25 : 3;

			itst->rcItem.left += offset + cy + ( lvitem.lParam && !is_root ? 8 : 4 );
			icon = 0;

			if (! is_root ) 
			{
				if ( _is_splited_item(lvitem.lParam) ) icon = 1;
				if ( _is_cdrom_item(lvitem.lParam) )   icon = 2;
			}

			ImageList_Draw(
				__dsk_img, icon, itst->hDC, offset, itst->rcItem.top + 3, ILD_TRANSPARENT
				);
		} else 
		{
			offset = 0;
		}
		if ( offset && is_root )
		{
			DrawState(
				itst->hDC, 0, NULL, (LPARAM)s_text, 0, 
				itst->rcItem.left+5, itst->rcItem.top, 0, 0, DST_PREFIXTEXT | DSS_MONO
				);
		} else 
		{
			if ( wcslen(s_text) != 0 ) 
			{
				COLORREF text_color = GetSysColor( COLOR_WINDOWTEXT );

				if ( !_is_active_item(lvitem.lParam) )
				{
					text_color = GetSysColor( COLOR_GRAYTEXT );
				}
				SetTextColor( itst->hDC, text_color );

				if ( k >= 4 )
				{
					SelectObject( itst->hDC, __font_bold );
				}
				if ( !IsWindowEnabled( itst->hwndItem ) )
				{
					SetTextColor( itst->hDC, GetSysColor(COLOR_GRAYTEXT) );

					DrawTextEx(
						itst->hDC, s_text, -1, &itst->rcItem,
						DT_END_ELLIPSIS | ((lvc.fmt & LVCFMT_RIGHT) ? DT_RIGHT : FALSE), &dtp
						);
				} else 
				{
					DrawTextEx(
						itst->hDC, s_text, -1, &itst->rcItem,
						DT_END_ELLIPSIS | ((lvc.fmt & LVCFMT_RIGHT) ? DT_RIGHT : FALSE), &dtp
						);
					/*
					if ( GetFocus( ) == itst->hwndItem )
					{
						DrawFocusRect( itst->hDC, &itst->rcItem );
					}
					*/
				}
			}
		}
	}							
}