void TileView::setTheme( Theme & t, const string prefix )
{
	Widget::setTheme( t, prefix );
  setBorder( t.getBorder( prefix+"tileview" ) );
	setCursor( t.getCursor( prefix+"tileview" ) );
}