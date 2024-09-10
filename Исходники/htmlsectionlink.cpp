void CHTMLSectionLink::GetObjectRect( WinHelper::CRect &rcBounds ) const
{
	HRGN rgn;
	if( GetRegion( rgn ) )
	{
		GetRgnBox( rgn, rcBounds );
		VAPI( DeleteObject( rgn ) );
	}
	else
	{
		ASSERT( FALSE );
	}
}