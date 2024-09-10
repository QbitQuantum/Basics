void TLView::DrawItem(wxDC& dc, TLItem* item, long left, long delta_left, long top, long width, long height)
{
/* - Item itself - */
	Draw3dRect( &dc, left, top, width, height, item->GetSample()->GetColour() );
/* - Selection - */
	if ( item->IsSelected() ) {
		dc.SetPen( wxPen( *wxWHITE, 3, wxSHORT_DASH ) );
		dc.SetBrush( *wxTRANSPARENT_BRUSH );
		dc.DrawRectangle( left, top, width, height );
	}
/* - Label (Filename) - */
	if ( width > 1 ) {
		dc.SetPen( *wxBLACK_PEN );
		dc.SetClippingRegion( left, top, width, height );
		dc.SetFont( *wxSMALL_FONT );
		wxFileName fn( item->GetSample()->GetFilename() );
		long v3 = left + delta_left;
			dc.DrawText( fn.GetName(), v3, top + 1 );
/* - Extras ;) -*/ 
		dc.SetPen( *wxBLACK_PEN );
		dc.SetBrush( *wxWHITE_BRUSH );
		if ( item->m_toggleEnvelope ) {
			item->DrawEnvelope( dc, left + delta_left, top );
		}
		dc.DrawIcon(*dropDownIcon, left+delta_left+(item->GetLen()/GetRealZoom())-7,top+height-7);
		dc.DestroyClippingRegion();
	}
//	dc.DrawRectangle( left + item->m_x_test, top+item->m_y_test, 10, 10);
}