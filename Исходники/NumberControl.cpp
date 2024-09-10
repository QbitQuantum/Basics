void NumberControl::processRender(const GsRect<float> &RectDispCoordFloat)
{
	// Transform to the display coordinates
	GsRect<float> displayRect = mRect;
	displayRect.transform(RectDispCoordFloat);
	SDL_Rect lRect = displayRect.SDLRect();

    GsWeakSurface blitsfc(gVideoDriver.getBlitSurface());

    // Now lets draw the text of the list control
    GsFont &Font = gGraphics.getFont(mFontID);

    Font.drawFont( blitsfc, mText, lRect.x+24, lRect.y, false );
    Font.drawFont( blitsfc, ":", lRect.x+24+mText.size()*8, lRect.y, false );

    if(mSlider)
    {
        gGraphics.getFont(2).drawFont( blitsfc, sliderStr(), lRect.x+16+(mText.size()+2)*8, lRect.y, false );
    }
    else
    {
        std::string text = (mDecSel) ? "\025" : " ";
        text += itoa(mValue);
        if(mIncSel)
            text += static_cast<char>(17);
        else
            text += " ";

        Font.drawFont( blitsfc, text, lRect.x+24+(mText.size()+2)*8, lRect.y, false );
    }

    drawTwirl(lRect);

}