void clFileAssociationsListWin::DrawItem( wal::GC& gc, int n, crect rect )
{
	if ( n < 0 || n >= ( int )m_ItemList->size( ) )
	{
		gc.SetFillColor( UiGetColor( uiBackground, 0, 0, 0xB0B000 ) );
		gc.FillRect( rect ); //CCC
		return;
	}

	UiCondList ucl;

	if ( ( n % 2 ) == 0 ) { ucl.Set( uiOdd, true ); }

	if ( n == this->GetCurrent() ) { ucl.Set( uiCurrentItem, true ); }

	unsigned bg = UiGetColor( uiBackground, uiItem, &ucl, 0xB0B000 );
	unsigned color = UiGetColor( uiColor, uiItem, &ucl, 0 );
	unsigned fcColor = UiGetColor( uiFcColor, uiItem, &ucl, 0xFFFF );

	gc.SetFillColor( bg );
	gc.FillRect( rect );

	const clNCFileAssociation* p = &m_ItemList->at( n );

	if ( p )
	{
		gc.Set( GetFont() );
		gc.SetTextColor( color );
		gc.TextOutF( rect.left + 10, rect.top + 1, p->GetMask().data() );
		gc.SetTextColor( fcColor );
		gc.TextOutF( rect.left + 10, rect.top + 1, p->GetMask().data(), 1 );
	}
}