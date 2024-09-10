// Draw TreeCtrl Items
void VividTree::DrawItems( CDC *pDC )
{
	// draw items
	HTREEITEM show_item, parent;
	CRect rc_item;
	CString name;
	COLORREF color;
	DWORD tree_style;
	BITMAP bm;
	CDC dc_mem;
	CBitmap *button;
	int count = 0;
	int state;
	bool selected;
	bool has_children;

	show_item = GetFirstVisibleItem();
	if ( show_item == NULL )
		return;

	dc_mem.CreateCompatibleDC(NULL);
	color = pDC->GetTextColor();
	tree_style = ::GetWindowLong( m_hWnd, GWL_STYLE ); 

	do
	{
		state = GetItemState( show_item, TVIF_STATE );
		parent = GetParentItem( show_item );
		has_children = ItemHasChildren( show_item ) || parent == NULL;
		selected = (state & TVIS_SELECTED) && ((this == GetFocus()) || 
				(tree_style & TVS_SHOWSELALWAYS));

		if ( GetItemRect( show_item, rc_item, TRUE ) )
		{
			if( selected)
			{
				CRect rc_all;
				GetItemRect(show_item,&rc_all, FALSE);
				pDC->FillSolidRect(&rc_all, RGB(170,155,119));
			}
			if ( has_children  || selected )
			{
				COLORREF from;
				CRect rect;
				// Show 
				if ( selected )
					from = m_gradient_bkgd_sel;
				else
					from = m_gradient_bkgd_to - (m_gradient_bkgd_from - m_gradient_bkgd_to);
				rect.top = rc_item.top;
				rect.bottom = rc_item.bottom;
				rect.right = m_h_size + m_h_offset;
				if ( !has_children )
					rect.left = rc_item.left + m_h_offset;
				else
					rect.left = m_h_offset;
				//GradientFillRect( pDC, rect, from, m_gradient_bkgd_to, FALSE );
				//pDC->SetTextColor( RGB( 0, 0, 255 ) );
				pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

				if ( has_children )
				{
					// Draw an Open/Close button
					if ( state & TVIS_EXPANDED )
						button = &m_bmp_tree_open;
					else
						button = &m_bmp_tree_closed;
					VERIFY(button->GetObject(sizeof(bm), (LPVOID)&bm));
					CBitmap *bmp_old = (CBitmap*)dc_mem.SelectObject(button); 
					pDC->TransparentBlt(rc_item.left - bm.bmWidth - 2, rc_item.top, bm.bmWidth, bm.bmHeight, 
						&dc_mem, 0, 0,bm.bmWidth,bm.bmWidth, GetSysColor(COLOR_HIGHLIGHTTEXT));
					//pDC->BitBlt( rc_item.left - bm.bmWidth - 2, rc_item.top, bm.bmWidth, bm.bmHeight, 
					//	&dc_mem, 0, 0, SRCCOPY );
					// CleanUp
					dc_mem.SelectObject( bmp_old );
				}
			}
			if ( !has_children )
			{
				// lookup the ICON instance (if any) and draw it
				HICON icon;
				icon = GetItemIcon( show_item );
				if ( icon != NULL )
					DrawIconEx( pDC->m_hDC, rc_item.left - 18, rc_item.top, icon, 16, 16,0,0, DI_NORMAL );
			}
			name = GetItemText( show_item );
			rc_item.DeflateRect( 0,1,0,1 );
			if ( selected )
			{
				if ( !has_children  )
					pDC->SetTextColor( GetSysColor(COLOR_HIGHLIGHTTEXT) );
				COLORREF col = pDC->GetBkColor();
				//pDC->SetBkColor( /*GetSysColor(COLOR_HIGHLIGHT)*/RGB(170,155,119) );
				pDC->DrawText( name, rc_item, DT_LEFT );
				pDC->SetTextColor( color );
				pDC->SetBkColor( col );
			}
			else
			{
				pDC->SetTextColor( GetSysColor(COLOR_HIGHLIGHTTEXT) );
				pDC->DrawText( name, rc_item, DT_LEFT );
				pDC->SetTextColor( color );
			}
			//if ( state & TVIS_BOLD )
			//	pDC->SelectObject( font );
		}
	} while ( (show_item = GetNextVisibleItem( show_item )) != NULL );
}