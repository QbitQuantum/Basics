void LLFloaterMap::adjustLayout( bool expand )
{
	S32 radar_height = mPanelRadar->getRect().getHeight();
	S32 height = getRect().getHeight();
	LLRect map_rect = mPanelMap->getRect();
	S32 map_bottom = map_rect.mBottom;

	S32 min_width, min_height;
	getResizeLimits( &min_width, &min_height );

	S32 adjust = radar_height;
	if (!expand)
	{
		adjust = -adjust;
	}
	
	height += adjust;
	min_height += adjust;
	map_bottom += adjust;

	map_rect.set( map_rect.mLeft,  map_rect.mTop,
	              map_rect.mRight, map_bottom );
	mPanelMap->setRect(map_rect);

	setResizeLimits( min_width, min_height );
	reshape( getRect().getWidth(), height, false );

	LLRect temp_rect = getRect();
	temp_rect.translate( 0, -adjust );
	setRect( temp_rect );

	LLButton* toggle = getChild<LLButton>("toggle_radar");
	if (toggle)
	{
		temp_rect = toggle->getRect();
		temp_rect.translate( 0, adjust );
		toggle->setRect( temp_rect );
	}
}