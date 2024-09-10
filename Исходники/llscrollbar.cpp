void LLScrollbar::draw()
{
	if (!getRect().isValid()) return;

	if(mBGVisible)
	{
		gl_rect_2d(getLocalRect(), mBGColor.get(), TRUE);
	}

	S32 local_mouse_x;
	S32 local_mouse_y;
	LLUI::getMousePositionLocal(this, &local_mouse_x, &local_mouse_y);
	BOOL other_captor = gFocusMgr.getMouseCapture() && gFocusMgr.getMouseCapture() != this;
	BOOL hovered = getEnabled() && !other_captor && (hasMouseCapture() || mThumbRect.pointInRect(local_mouse_x, local_mouse_y));
	if (hovered)
	{
		mCurGlowStrength = lerp(mCurGlowStrength, mHoverGlowStrength, LLCriticalDamp::getInterpolant(0.05f));
	}
	else
	{
		mCurGlowStrength = lerp(mCurGlowStrength, 0.f, LLCriticalDamp::getInterpolant(0.05f));
	}

	// Draw background and thumb.
	if (   ( mOrientation == VERTICAL&&(mThumbImageV.isNull() || mThumbImageH.isNull()) ) 
		|| (mOrientation == HORIZONTAL&&(mTrackImageH.isNull() || mTrackImageV.isNull()) ))
	{
		gl_rect_2d(mOrientation == HORIZONTAL ? mThickness : 0, 
		mOrientation == VERTICAL ? getRect().getHeight() - 2 * mThickness : getRect().getHeight(),
		mOrientation == HORIZONTAL ? getRect().getWidth() - 2 * mThickness : getRect().getWidth(), 
		mOrientation == VERTICAL ? mThickness : 0, mTrackColor.get(), TRUE);

		gl_rect_2d(mThumbRect, mThumbColor.get(), TRUE);

	}
	else
	{
		// Thumb
		LLRect outline_rect = mThumbRect;
		outline_rect.stretch(2);
		// Background
		
		if(mOrientation == HORIZONTAL)
		{
			mTrackImageH->drawSolid(mThickness								//S32 x
								   , 0										//S32 y
								   , getRect().getWidth() - 2 * mThickness  //S32 width
								   , getRect().getHeight()					//S32 height
								   , mTrackColor.get());                    //const LLColor4& color
			
			if (gFocusMgr.getKeyboardFocus() == this)
			{
				mTrackImageH->draw(outline_rect, gFocusMgr.getFocusColor());
			}
			
			mThumbImageH->draw(mThumbRect, mThumbColor.get());
			if (mCurGlowStrength > 0.01f)
			{
				gGL.setSceneBlendType(LLRender::BT_ADD_WITH_ALPHA);
				mThumbImageH->drawSolid(mThumbRect, LLColor4(1.f, 1.f, 1.f, mCurGlowStrength));
				gGL.setSceneBlendType(LLRender::BT_ALPHA);
			}
			
		}
		else if(mOrientation == VERTICAL)
		{
			mTrackImageV->drawSolid(  0										//S32 x
								   , mThickness								//S32 y
								   , getRect().getWidth()					//S32 width
								   , getRect().getHeight() - 2 * mThickness	//S32 height
								   , mTrackColor.get());                    //const LLColor4& color
			if (gFocusMgr.getKeyboardFocus() == this)
			{
				mTrackImageV->draw(outline_rect, gFocusMgr.getFocusColor());
			}
			
			mThumbImageV->draw(mThumbRect, mThumbColor.get());
			if (mCurGlowStrength > 0.01f)
			{
				gGL.setSceneBlendType(LLRender::BT_ADD_WITH_ALPHA);
				mThumbImageV->drawSolid(mThumbRect, LLColor4(1.f, 1.f, 1.f, mCurGlowStrength));
				gGL.setSceneBlendType(LLRender::BT_ALPHA);
			}
		}
	}

	// Draw children
	LLView::draw();
} // end draw