/*
================
rvGENavigator::WndProc

Window Procedure
================
*/
LRESULT CALLBACK rvGENavigator::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	rvGENavigator *nav = ( rvGENavigator * ) GetWindowLong( hWnd, GWL_USERDATA );
	switch( msg ) {
	case WM_INITMENUPOPUP:
		return SendMessage( gApp.GetMDIFrame( ), msg, wParam, lParam );
	case WM_ACTIVATE:
		common->ActivateTool( LOWORD( wParam ) != WA_INACTIVE );
		break;
	case WM_ERASEBKGND:
		return TRUE;
	case WM_DESTROY:
		gApp.GetOptions().SetWindowPlacement( "navigator", hWnd );
		break;
	case WM_CLOSE:
		gApp.GetOptions().SetNavigatorVisible( false );
		nav->Show( false );
		return 0;
	case WM_DRAWITEM: {
		DRAWITEMSTRUCT	*dis = ( DRAWITEMSTRUCT * ) lParam;
		idWindow		*window = ( idWindow * )dis->itemData;
		if( window ) {
			rvGEWindowWrapper	*wrapper	= rvGEWindowWrapper::GetWrapper( window );
			idStr				name    = window->GetName();
			RECT				rDraw;
			float				offset;
			bool				disabled;
			idWindow *parent = window;
			offset = 1;
			disabled = false;
			while( parent = parent->GetParent( ) ) {
				if( rvGEWindowWrapper::GetWrapper( parent )->IsHidden( ) ) {
					disabled = true;
				}
				offset += 10;
			}
			CopyRect( &rDraw, &dis->rcItem );
			rDraw.right = rDraw.left + GENAV_ITEMHEIGHT;
			rDraw.top ++;
			rDraw.right ++;
			FrameRect( dis->hDC, &rDraw, ( HBRUSH )GetStockObject( BLACK_BRUSH ) );
			rDraw.right --;
			FillRect( dis->hDC, &rDraw, GetSysColorBrush( COLOR_3DFACE ) );
			Draw3dRect( dis->hDC, &rDraw, GetSysColorBrush( COLOR_3DHILIGHT ), GetSysColorBrush( COLOR_3DSHADOW ) );
			InflateRect( &rDraw, -3, -3 );
			Draw3dRect( dis->hDC, &rDraw, GetSysColorBrush( COLOR_3DSHADOW ), GetSysColorBrush( COLOR_3DHILIGHT ) );
			if( !wrapper->IsHidden( ) ) {
				DrawIconEx( dis->hDC, rDraw.left, rDraw.top, disabled ? nav->mVisibleIconDisabled : nav->mVisibleIcon, 16, 16, 0, NULL, DI_NORMAL );
			}
			CopyRect( &rDraw, &dis->rcItem );
			rDraw.left += GENAV_ITEMHEIGHT;
			rDraw.left += 1;
			if( dis->itemState & ODS_SELECTED ) {
				FillRect( dis->hDC, &rDraw, GetSysColorBrush( COLOR_HIGHLIGHT ) );
			} else {
				FillRect( dis->hDC, &rDraw, GetSysColorBrush( COLOR_WINDOW ) );
			}
			if( wrapper->CanHaveChildren( ) && window->GetChildCount( ) ) {
				if( wrapper->IsExpanded( ) ) {
					DrawIconEx( dis->hDC, rDraw.left + offset, rDraw.top + 3, nav->mCollapseIcon, 16, 16, 0, NULL, DI_NORMAL );
				} else {
					DrawIconEx( dis->hDC, rDraw.left + offset, rDraw.top + 3, nav->mExpandIcon, 16, 16, 0, NULL, DI_NORMAL );
				}
			}
			HPEN pen = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_3DSHADOW ) );
			HPEN oldpen = ( HPEN )SelectObject( dis->hDC, pen );
			MoveToEx( dis->hDC, rDraw.left, dis->rcItem.top, NULL );
			LineTo( dis->hDC, dis->rcItem.right, dis->rcItem.top );
			MoveToEx( dis->hDC, rDraw.left, dis->rcItem.bottom, NULL );
			LineTo( dis->hDC, dis->rcItem.right, dis->rcItem.bottom );
			SelectObject( dis->hDC, oldpen );
			DeleteObject( pen );
			rDraw.left += offset;
			rDraw.left += 20;
			int colorIndex = ( ( dis->itemState & ODS_SELECTED ) ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT );
			SetTextColor( dis->hDC, GetSysColor( colorIndex ) );
			DrawText( dis->hDC, name, name.Length(), &rDraw, DT_LEFT | DT_VCENTER | DT_SINGLELINE );
			if( wrapper->GetVariableDict().GetNumKeyVals( ) || wrapper->GetScriptDict().GetNumKeyVals( ) ) {
				DrawIconEx( dis->hDC, dis->rcItem.right - 16, ( dis->rcItem.bottom + dis->rcItem.top ) / 2 - 6, ( dis->itemState & ODS_SELECTED ) ? nav->mScriptsLightIcon : nav->mScriptsIcon, 13, 13, 0, NULL, DI_NORMAL );
			}
		}
		break;
	}
	case WM_MEASUREITEM: {
		MEASUREITEMSTRUCT *mis = ( MEASUREITEMSTRUCT * ) lParam;
		mis->itemHeight = 22;
		break;
	}
	case WM_CREATE: {
		LPCREATESTRUCT	cs;
		LVCOLUMN		col;
		// Attach the class to the window first
		cs = ( LPCREATESTRUCT ) lParam;
		nav = ( rvGENavigator * ) cs->lpCreateParams;
		SetWindowLong( hWnd, GWL_USERDATA, ( LONG )nav );
		// Create the List view
		nav->mTree = CreateWindowEx( 0, "SysListView32", "", WS_VSCROLL | WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_NOCOLUMNHEADER | LVS_SHOWSELALWAYS, 0, 0, 0, 0, hWnd, ( HMENU )IDC_GUIED_WINDOWTREE, win32.hInstance, 0 );
		ListView_SetExtendedListViewStyle( nav->mTree, LVS_EX_FULLROWSELECT );
		ListView_SetBkColor( nav->mTree, GetSysColor( COLOR_3DFACE ) );
		ListView_SetTextBkColor( nav->mTree, GetSysColor( COLOR_3DFACE ) );
		nav->mListWndProc = ( WNDPROC )GetWindowLong( nav->mTree, GWL_WNDPROC );
		SetWindowLong( nav->mTree, GWL_USERDATA, ( LONG )nav );
		SetWindowLong( nav->mTree, GWL_WNDPROC, ( LONG )ListWndProc );
		// Insert the only column
		col.mask = 0;
		ListView_InsertColumn( nav->mTree, 0, &col );
		break;
	}
	case WM_SIZE: {
		RECT rClient;
		MoveWindow( nav->mTree, 0, 0, LOWORD( lParam ), HIWORD( lParam ), TRUE );
		GetClientRect( nav->mTree, &rClient );
		ListView_SetColumnWidth( nav->mTree, 0, rClient.right - rClient.left - 1 );
		break;
	}
	case WM_NCACTIVATE:
		return gApp.ToolWindowActivate( gApp.GetMDIFrame(), msg, wParam, lParam );
	case WM_NOTIFY: {
		LPNMHDR nh;
		nh = ( LPNMHDR ) lParam;
		switch( nh->code ) {
		case NM_CLICK:
		case NM_DBLCLK: {
			DWORD dwpos = GetMessagePos();
			LVHITTESTINFO info;
			info.pt.x = LOWORD( dwpos );
			info.pt.y = HIWORD( dwpos );
			MapWindowPoints( HWND_DESKTOP, nh->hwndFrom, &info.pt, 1 );
			int index = ListView_HitTest( nav->mTree, &info );
			if( index != -1 ) {
				RECT	rItem;
				int		offset;
				ListView_GetItemRect( nav->mTree, index, &rItem, LVIR_BOUNDS );
				LVITEM item;
				item.mask = LVIF_PARAM;
				item.iItem = index;
				ListView_GetItem( nav->mTree, &item );
				idWindow *window = ( idWindow * )item.lParam;
				rvGEWindowWrapper *wrapper = rvGEWindowWrapper::GetWrapper( window );
				offset = wrapper->GetDepth( ) * 10 + 1;
				if( info.pt.x < GENAV_ITEMHEIGHT ) {
					if( !rvGEWindowWrapper::GetWrapper( window )->IsHidden( ) ) {
						nav->mWorkspace->HideWindow( window );
					} else {
						nav->mWorkspace->UnhideWindow( window );
					}
				} else if( info.pt.x > GENAV_ITEMHEIGHT + offset && info.pt.x < GENAV_ITEMHEIGHT + offset + 16 ) {
					if( wrapper->CanHaveChildren( ) && window->GetChildCount( ) ) {
						if( wrapper->IsExpanded( ) ) {
							wrapper->Collapse( );
							nav->Update( );
						} else {
							wrapper->Expand( );
							nav->Update( );
						}
					}
				} else if( nh->code == NM_DBLCLK ) {
					SendMessage( gApp.GetMDIFrame( ), WM_COMMAND, MAKELONG( ID_GUIED_ITEM_PROPERTIES, 0 ), 0 );
				}
			}
			break;
		}
		case NM_RCLICK: {
			DWORD dwpos = GetMessagePos();
			LVHITTESTINFO info;
			info.pt.x = LOWORD( dwpos );
			info.pt.y = HIWORD( dwpos );
			MapWindowPoints( HWND_DESKTOP, nh->hwndFrom, &info.pt, 1 );
			int index = ListView_HitTest( nav->mTree, &info );
			if( index != -1 ) {
				ClientToScreen( hWnd, &info.pt );
				HMENU menu = GetSubMenu( LoadMenu( gApp.GetInstance(), MAKEINTRESOURCE( IDR_GUIED_ITEM_POPUP ) ), 0 );
				TrackPopupMenu( menu, TPM_RIGHTBUTTON | TPM_LEFTALIGN, info.pt.x, info.pt.y, 0, gApp.GetMDIFrame( ), NULL );
				DestroyMenu( menu );
			}
			break;
		}
		case LVN_ITEMCHANGED: {
			NMLISTVIEW *nml = ( NMLISTVIEW * ) nh;
			if( ( nml->uNewState & LVIS_SELECTED ) != ( nml->uOldState & LVIS_SELECTED ) ) {
				LVITEM item;
				item.iItem = nml->iItem;
				item.mask = LVIF_PARAM;
				ListView_GetItem( nav->mTree, &item );
				if( nml->uNewState & LVIS_SELECTED ) {
					nav->mWorkspace->GetSelectionMgr().Add( ( idWindow * )item.lParam, false );
				} else {
					nav->mWorkspace->GetSelectionMgr().Remove( ( idWindow * )item.lParam );
				}
			}
			break;
		}
		}
		break;
	}
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}