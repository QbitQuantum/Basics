void CHTMLControlSection::OnDraw( GS::CDrawContext &dc )
{
	if( dc.IsPrinting() )
	{
		dc.FillRect( *this, RGB( 255, 0, 0 ) );
	}
}