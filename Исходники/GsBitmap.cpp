void CGUIBitmap::processRender(const GsRect<float> &RectDispCoordFloat)
{    
    if(mScaledBitmap.empty())
        return;

	// Transform to the display coordinates
	GsRect<float> displayRect = mRect;
	displayRect.transform(RectDispCoordFloat);
    GsRect<Uint16> lRect = displayRect.SDLRect();

    if( mScaledBitmap.getWidth() != lRect.w ||
        mScaledBitmap.getHeight() != lRect.h )
    {
        mScaledBitmap = GsBitmap( *mpBitmap.get() );
        lRect.x = 0;    lRect.y = 0;
        mScaledBitmap.scaleTo(lRect);
    }
    else
    {
        mScaledBitmap.draw( lRect.x, lRect.y );
    }
}