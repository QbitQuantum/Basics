void CGUINumberControl::processRender(const GsRect<float> &RectDispCoordFloat)
{

	// Transform to the display coordinates
	GsRect<float> displayRect = mRect;
	displayRect.transform(RectDispCoordFloat);
    GsRect<Uint16> lRect(displayRect);

    GsWeakSurface blitsfc(gVideoDriver.getBlitSurface());

    if( mReleased )
    {
        blitsfc.drawRect( lRect, 1, 0x00BBBBBB, 0x00CFCFCF );
    }
    else if( mPressed )
    {
        blitsfc.drawRect( lRect, 1, 0x00BBBBBB, 0x00DFDFDF );
    }
    else if( mHovered )
    {
        blitsfc.drawRect( lRect, 1, 0x00BBBBBB, 0x00EFEFEF );
    }
    else
    {
        blitsfc.drawRect( lRect, 1, 0x00BBBBBB, 0x00FFFFFF );
    }

    // Now lets draw the text of the list control
    GsFont &Font = gGraphics.getFont(mFontID);

    Font.drawFontCentered( blitsfc,
                           mText,
                           lRect,
                           false );
}