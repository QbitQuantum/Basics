void CGUITextSelectionList::processRender(const GsRect<float> &RectDispCoordFloat)
{
	// Blit the List surface
	SDL_Surface *Blitsurface = gVideoDriver.getBlitSurface();

	// Transform to the display coordinates
    GsRect<float> displayRect = mRect;
	displayRect.transform(RectDispCoordFloat);

	SDL_Rect lRect = displayRect.SDLRect();
	SDL_FillRect(Blitsurface, &lRect, 0xFFFFFFFF);

	// Now lets draw the text of the list control
	GsFont &Font = gGraphics.getFont(mFontID);

	// Move 16 Pixel so we have space for the cursor/twirl to show the selection
    const int sepHeight = Font.getPixelTextHeight()+2;
	const int xpos = lRect.x+16+1;
	const int ypos = lRect.y+10;
	unsigned int textlimitWidth = (lRect.w-16)/8;

    mScrollbar.mLastToShow = (lRect.h/sepHeight)-1;

	lRect.h = 10;
    lRect.x += 12;
    lRect.w -= 12;
	std::string trimmedText;
	std::list<std::string> :: iterator it = mItemList.begin();

    for(int i=0 ; i<mScrollbar.scrollPos() ; it++, i++);

    for ( int line = 0;  it != mItemList.end() && line<mScrollbar.mLastToShow ; it++, line++ )
	{
        if(mPressedSelection == int(line) + mScrollbar.scrollPos() )
        {
            lRect.y = ypos+(line*10)-1;
            SDL_FillRect(Blitsurface, &lRect, 0xFFA5A5F1);
        }
        else if(mReleasedSelection == int(line) + mScrollbar.scrollPos() )
		{
            lRect.y = ypos+(line*10)-1;

            if(mSelected)
                SDL_FillRect(Blitsurface, &lRect, 0xFFB5B5F1);
            else
                SDL_FillRect(Blitsurface, &lRect, 0xFFC5C5C5);
		}
        else if(mHoverSelection == int(line) + mScrollbar.scrollPos() )
        {
            lRect.y = ypos+(line*sepHeight)-1;
            SDL_FillRect(Blitsurface, &lRect, 0xFFE5E5F1);
        }


		trimmedText = *it;
		if(trimmedText.size() > textlimitWidth)
			trimmedText = trimmedText.substr(0, textlimitWidth);

		Font.drawFont(Blitsurface, trimmedText, xpos, ypos+(line*10), false);
	}

    mScrollbar.mMaxScrollAmt = mItemList.size()-mScrollbar.lastToShow();

    // Do we need a scrollbar?
    if(mScrollbar.mMaxScrollAmt>0)
    {
        mScrollbar.processRender(displayRect);
        //drawScrollBar(displayRect.SDLRect());
    }

}