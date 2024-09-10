//-------------------------------------------------------------------------
void CDlgColours::OnDrawItem( int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	COLORREF 	crButton = m_oColor.Get( m_id_map[ nIDCtl ] );
	CDC dc;
	CBrush 		brush( crButton );

	dc.Attach( lpDrawItemStruct->hDC );
	dc.SelectStockObject( BLACK_PEN );
	dc.SelectObject( &brush );
	dc.Rectangle( &lpDrawItemStruct->rcItem );
	dc.Detach();
	
	super::OnDrawItem( nIDCtl, lpDrawItemStruct );
}