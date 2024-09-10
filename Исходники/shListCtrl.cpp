void CSHListCtrl::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// This function is called by the control in different 
	// stages during the control drawing process.
	if (!m_bKeyEvent)
		return;

	NMLVCUSTOMDRAW *pCD = (NMLVCUSTOMDRAW*)pNMHDR;
	// By default set the return value to do the default behavior.
	*pResult = 0;
	
	switch( pCD->nmcd.dwDrawStage )
	{
	case  CDDS_PREPAINT:  // First stage (for the whole control)
		// Tell the control we want to receive drawing messages  
		// for drawing items.
		*pResult = CDRF_NOTIFYITEMDRAW;
		// The next stage is handled in the default:
		break;
	case CDDS_ITEMPREPAINT | CDDS_SUBITEM: // Stage three (called for each subitem of the focused item)
		{
			// We don't want to draw anything here, but we need to respond 
			// of DODEFAULT will be the next stage.
			// Tell the control we want to handle drawing after the subitem 
			// is drawn.
			*pResult = CDRF_NOTIFYSUBITEMDRAW | CDRF_NOTIFYPOSTPAINT;
		}
		break;
	case CDDS_ITEMPOSTPAINT | CDDS_SUBITEM: // Stage four (called for each subitem of the focused item)
		{
			// We do the drawing here (well maybe).
			// This is actually after the control has done its drawing
			// on the subitem.  Since drawing a cell is near instantaneous
			// the user won't notice.
			int subitem = pCD->iSubItem;
			// Only do our own drawing if this subitem has focus at the item level.
			if( (pCD->nmcd.uItemState & CDIS_FOCUS) )
			{
				// If this subitem is the subitem with the current focus,
				// draw it.  Otherwise let the control draw it.  
				CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
				// We have to take into account the possibility that the 
				// columns may be reordered.
				if( subitem == Header_OrderToIndex( pHeader->m_hWnd,  m_CurSubItem ) )
				{
					// POSTERASE
					CDC* pDC = CDC::FromHandle(pCD->nmcd.hdc);
					// Calculate the offset of the text from the right and left of the cell.
					int offset = pDC->GetTextExtent(_T(" "), 1 ).cx*2;
					// The rect for the cell gives correct left and right values.
					CRect rect = pCD->nmcd.rc;
					CRect bounds;
					GetItemRect( pCD->nmcd.dwItemSpec, &bounds, LVIR_BOUNDS );
					// Get the top and bottom from the item itself.
					rect.top = bounds.top;
					rect.bottom = bounds.bottom;
					// Adjust rectangle for horizontal scroll and first column label
					{
						if( subitem == 0 )
						{
							CRect lrect;
							GetItemRect( pCD->nmcd.dwItemSpec, &lrect, LVIR_LABEL );
							rect.left = lrect.left;
							rect.right = lrect.right;
						}
						else
						{
							rect.right += bounds.left;
							rect.left  += bounds.left;
						}
					}
					// Clear the background with button face color
					pDC->FillRect(rect, &CBrush(::GetSysColor(COLOR_3DFACE)));
					// PREPAINT
					CString str;
					str = GetItemText( pCD->nmcd.dwItemSpec, pCD->iSubItem );
					// Deflate the rect by the horizontal offset.
					rect.DeflateRect( offset, 0 );
					// You could also make this column alignment sensitive here.
					pDC->DrawText( str, rect, 
						DT_SINGLELINE|DT_NOPREFIX|DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);
					// POSTPAINT
					// Draw rounded edge
					rect.InflateRect( offset, 0 );
					pDC->Draw3dRect( &rect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DFACE) );
					rect.DeflateRect( 1, 1 );
					pDC->Draw3dRect( &rect, ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DHILIGHT) );
					// Tell the control that we handled the drawing for this subitem.
					*pResult = CDRF_SKIPDEFAULT;
				}
			}
		}
		break;
	default: // Stage two handled here. (called for each item)
		if( !(pCD->nmcd.uItemState & CDIS_FOCUS) )
		{
			// If this item does not have focus, let the 
			// control draw the whole item.
			*pResult = CDRF_DODEFAULT;
		}
		else
		{
			// If this item has focus, tell the control we want
			// to handle subitem drawing.
			*pResult = CDRF_NOTIFYSUBITEMDRAW;
		}
		break;
	}
}