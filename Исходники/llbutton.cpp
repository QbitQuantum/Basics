// virtual
void LLButton::draw()
{
	static LLCachedControl<bool> sEnableButtonFlashing(*LLUI::sSettingGroups["config"], "EnableButtonFlashing", true);
	F32 alpha = mUseDrawContextAlpha ? getDrawContext().mAlpha : getCurrentTransparency();

	bool pressed_by_keyboard = FALSE;
	if (hasFocus())
	{
		pressed_by_keyboard = gKeyboard->getKeyDown(' ') || (mCommitOnReturn && gKeyboard->getKeyDown(KEY_RETURN));
	}

	bool mouse_pressed_and_over = false;
	if (hasMouseCapture())
	{
		S32 local_mouse_x ;
		S32 local_mouse_y;
		LLUI::getMousePositionLocal(this, &local_mouse_x, &local_mouse_y);
		mouse_pressed_and_over = pointInView(local_mouse_x, local_mouse_y);
	}

	bool enabled = isInEnabledChain();

	bool pressed = pressed_by_keyboard 
					|| mouse_pressed_and_over
					|| mForcePressedState;
	bool selected = getToggleState();
	
	bool use_glow_effect = FALSE;
	LLColor4 highlighting_color = LLColor4::white;
	LLColor4 glow_color = LLColor4::white;
	LLRender::eBlendType glow_type = LLRender::BT_ADD_WITH_ALPHA;
	LLUIImage* imagep = NULL;

    //  Cancel sticking of color, if the button is pressed,
	//  or when a flashing of the previously selected button is ended
	if (mFlashingTimer
		&& ((selected && !mFlashingTimer->isFlashingInProgress() && !mForceFlashing) || pressed))
	{
		mFlashing = false;
	}

	bool flash = mFlashing && sEnableButtonFlashing;

	if (pressed && mDisplayPressedState)
	{
		imagep = selected ? mImagePressedSelected : mImagePressed;
	}
	else if ( mNeedsHighlight )
	{
		if (selected)
		{
			if (mImageHoverSelected)
			{
				imagep = mImageHoverSelected;
			}
			else
			{
				imagep = mImageSelected;
				use_glow_effect = TRUE;
			}
		}
		else
		{
			if (mImageHoverUnselected)
			{
				imagep = mImageHoverUnselected;
			}
			else
			{
				imagep = mImageUnselected;
				use_glow_effect = TRUE;
			}
		}
	}
	else 
	{
		imagep = selected ? mImageSelected : mImageUnselected;
	}

	// Override if more data is available
	// HACK: Use gray checked state to mean either:
	//   enabled and tentative
	// or
	//   disabled but checked
	if (!mImageDisabledSelected.isNull() 
		&& 
			( (enabled && getTentative()) 
			|| (!enabled && selected ) ) )
	{
		imagep = mImageDisabledSelected;
	}
	else if (!mImageDisabled.isNull() 
		&& !enabled 
		&& !selected)
	{
		imagep = mImageDisabled;
	}

	if (mFlashing)
	{
		// if button should flash and we have icon for flashing, use it as image for button
		if(flash && mImageFlash)
		{
			// setting flash to false to avoid its further influence on glow
			flash = false;
			imagep = mImageFlash;
		}
		// else use usual flashing via flash_color
		else if (mFlashingTimer)
		{
			LLColor4 flash_color = mFlashBgColor.get();
			use_glow_effect = TRUE;
			glow_type = LLRender::BT_ALPHA; // blend the glow

			if (mFlashingTimer->isCurrentlyHighlighted() || !mFlashingTimer->isFlashingInProgress())
			{
				glow_color = flash_color;
			}
			else if (mNeedsHighlight)
			{
                glow_color = highlighting_color;
			}
		}
	}

	if (mNeedsHighlight && !imagep)
	{
		use_glow_effect = TRUE;
	}

	// Figure out appropriate color for the text
	LLColor4 label_color;

	// label changes when button state changes, not when pressed
	if ( enabled )
	{
		if ( getToggleState() )
		{
			label_color = mSelectedLabelColor.get();
		}
		else
		{
			label_color = mUnselectedLabelColor.get();
		}
	}
	else
	{
		if ( getToggleState() )
		{
			label_color = mDisabledSelectedLabelColor.get();
		}
		else
		{
			label_color = mDisabledLabelColor.get();
		}
	}

	// Unselected label assignments
	LLWString label = getCurrentLabel();

	// overlay with keyboard focus border
	if (hasFocus())
	{
		F32 lerp_amt = gFocusMgr.getFocusFlashAmt();
		drawBorder(imagep, gFocusMgr.getFocusColor() % alpha, ll_round(lerp(1.f, 3.f, lerp_amt)));
	}
	
	if (use_glow_effect)
	{
		mCurGlowStrength = lerp(mCurGlowStrength,
					mFlashing ? (mFlashingTimer->isCurrentlyHighlighted() || !mFlashingTimer->isFlashingInProgress() || mNeedsHighlight? 1.f : 0.f) : mHoverGlowStrength,
					LLSmoothInterpolation::getInterpolant(0.05f));
	}
	else
	{
		mCurGlowStrength = lerp(mCurGlowStrength, 0.f, LLSmoothInterpolation::getInterpolant(0.05f));
	}

	// Draw button image, if available.
	// Otherwise draw basic rectangular button.
	if (imagep != NULL)
	{
		// apply automatic 50% alpha fade to disabled image
		LLColor4 disabled_color = mFadeWhenDisabled ? mDisabledImageColor.get() % 0.5f : mDisabledImageColor.get();
		if ( mScaleImage)
		{
			imagep->draw(getLocalRect(), (enabled ? mImageColor.get() : disabled_color) % alpha  );
			if (mCurGlowStrength > 0.01f)
			{
				gGL.setSceneBlendType(glow_type);
				imagep->drawSolid(0, 0, getRect().getWidth(), getRect().getHeight(), glow_color % (mCurGlowStrength * alpha));
				gGL.setSceneBlendType(LLRender::BT_ALPHA);
			}
		}
		else
		{
			imagep->draw(0, 0, (enabled ? mImageColor.get() : disabled_color) % alpha );
			if (mCurGlowStrength > 0.01f)
			{
				gGL.setSceneBlendType(glow_type);
				imagep->drawSolid(0, 0, glow_color % (mCurGlowStrength * alpha));
				gGL.setSceneBlendType(LLRender::BT_ALPHA);
			}
		}
	}
	else
	{
		// no image
		LL_DEBUGS() << "No image for button " << getName() << LL_ENDL;
		// draw it in pink so we can find it
		gl_rect_2d(0, getRect().getHeight(), getRect().getWidth(), 0, LLColor4::pink1 % alpha, FALSE);
	}

	// let overlay image and text play well together
	S32 text_left = mLeftHPad;
	S32 text_right = getRect().getWidth() - mRightHPad;
	S32 text_width = getRect().getWidth() - mLeftHPad - mRightHPad;

	// draw overlay image
	if (mImageOverlay.notNull())
	{
		// get max width and height (discard level 0)
		S32 overlay_width;
		S32 overlay_height;

		getOverlayImageSize(overlay_width, overlay_height);

		S32 center_x = getLocalRect().getCenterX();
		S32 center_y = getLocalRect().getCenterY();

		//FUGLY HACK FOR "DEPRESSED" BUTTONS
		if (pressed && mDisplayPressedState)
		{
			center_y--;
			center_x++;
		}

		center_y += (mImageOverlayBottomPad - mImageOverlayTopPad);
		// fade out overlay images on disabled buttons
		LLColor4 overlay_color = mImageOverlayColor.get();
		if (!enabled)
		{
			overlay_color = mImageOverlayDisabledColor.get();
		}
		else if (getToggleState())
		{
			overlay_color = mImageOverlaySelectedColor.get();
		}
		overlay_color.mV[VALPHA] *= alpha;

		switch(mImageOverlayAlignment)
		{
		case LLFontGL::LEFT:
			text_left += overlay_width + mImgOverlayLabelSpace;
			text_width -= overlay_width + mImgOverlayLabelSpace;
			mImageOverlay->draw(
				mLeftHPad,
				center_y - (overlay_height / 2), 
				overlay_width, 
				overlay_height, 
				overlay_color);
			break;
		case LLFontGL::HCENTER:
			mImageOverlay->draw(
				center_x - (overlay_width / 2), 
				center_y - (overlay_height / 2), 
				overlay_width, 
				overlay_height, 
				overlay_color);
			break;
		case LLFontGL::RIGHT:
			text_right -= overlay_width + mImgOverlayLabelSpace;
			text_width -= overlay_width + mImgOverlayLabelSpace;
			mImageOverlay->draw(
				getRect().getWidth() - mRightHPad - overlay_width,
				center_y - (overlay_height / 2), 
				overlay_width, 
				overlay_height, 
				overlay_color);
			break;
		default:
			// draw nothing
			break;
		}
	}

	// Draw label
	if( !label.empty() )
	{
		LLWStringUtil::trim(label);

		S32 x;
		switch( mHAlign )
		{
		case LLFontGL::RIGHT:
			x = text_right;
			break;
		case LLFontGL::HCENTER:
			x = text_left + (text_width / 2);
			break;
		case LLFontGL::LEFT:
		default:
			x = text_left;
			break;
		}

		S32 y_offset = 2 + (getRect().getHeight() - 20)/2;
	
		if (pressed && mDisplayPressedState)
		{
			y_offset--;
			x++;
		}

		// *NOTE: mantipov: before mUseEllipses is implemented in EXT-279 U32_MAX has been passed as
		// max_chars.
		// LLFontGL::render expects S32 max_chars variable but process in a separate way -1 value.
		// Due to U32_MAX is equal to S32 -1 value I have rest this value for non-ellipses mode.
		// Not sure if it is really needed. Probably S32_MAX should be always passed as max_chars.
		mLastDrawCharsCount = mGLFont->render(label, 0,
			(F32)x,
			(F32)(getRect().getHeight() / 2 + mBottomVPad),
			label_color % alpha,
			mHAlign, LLFontGL::VCENTER,
			LLFontGL::NORMAL,
			mDropShadowedText ? LLFontGL::DROP_SHADOW_SOFT : LLFontGL::NO_SHADOW,
			S32_MAX, text_width,
			NULL, mUseEllipses);
	}

	LLUICtrl::draw();
}