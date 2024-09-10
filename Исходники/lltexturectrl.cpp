// virtual
void LLFloaterTexturePicker::draw()
{
	if (mOwner)
	{
		// draw cone of context pointing back to texture swatch	
		LLRect owner_rect;
		mOwner->localRectToOtherView(mOwner->getLocalRect(), &owner_rect, this);
		LLRect local_rect = getLocalRect();
		if (gFocusMgr.childHasKeyboardFocus(this) && mOwner->isInVisibleChain() && mContextConeOpacity > 0.001f)
		{
			gGL.getTexUnit(0)->unbind(LLTexUnit::TT_TEXTURE);
			LLGLEnable(GL_CULL_FACE);
			gGL.begin(LLRender::QUADS);
			{
				gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_IN_ALPHA * mContextConeOpacity);
				gGL.vertex2i(owner_rect.mLeft, owner_rect.mTop);
				gGL.vertex2i(owner_rect.mRight, owner_rect.mTop);
				gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_OUT_ALPHA * mContextConeOpacity);
				gGL.vertex2i(local_rect.mRight, local_rect.mTop);
				gGL.vertex2i(local_rect.mLeft, local_rect.mTop);

				gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_OUT_ALPHA * mContextConeOpacity);
				gGL.vertex2i(local_rect.mLeft, local_rect.mTop);
				gGL.vertex2i(local_rect.mLeft, local_rect.mBottom);
				gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_IN_ALPHA * mContextConeOpacity);
				gGL.vertex2i(owner_rect.mLeft, owner_rect.mBottom);
				gGL.vertex2i(owner_rect.mLeft, owner_rect.mTop);

				gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_OUT_ALPHA * mContextConeOpacity);
				gGL.vertex2i(local_rect.mRight, local_rect.mBottom);
				gGL.vertex2i(local_rect.mRight, local_rect.mTop);
				gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_IN_ALPHA * mContextConeOpacity);
				gGL.vertex2i(owner_rect.mRight, owner_rect.mTop);
				gGL.vertex2i(owner_rect.mRight, owner_rect.mBottom);


				gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_OUT_ALPHA * mContextConeOpacity);
				gGL.vertex2i(local_rect.mLeft, local_rect.mBottom);
				gGL.vertex2i(local_rect.mRight, local_rect.mBottom);
				gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_IN_ALPHA * mContextConeOpacity);
				gGL.vertex2i(owner_rect.mRight, owner_rect.mBottom);
				gGL.vertex2i(owner_rect.mLeft, owner_rect.mBottom);
			}
			gGL.end();
		}
	}

	if (gFocusMgr.childHasMouseCapture(getDragHandle()))
	{
		mContextConeOpacity = lerp(mContextConeOpacity, gSavedSettings.getF32("PickerContextOpacity"), LLCriticalDamp::getInterpolant(CONTEXT_FADE_TIME));
	}
	else
	{
		mContextConeOpacity = lerp(mContextConeOpacity, 0.f, LLCriticalDamp::getInterpolant(CONTEXT_FADE_TIME));
	}

	updateImageStats();

	// if we're inactive, gray out "apply immediate" checkbox
	childSetEnabled("show_folders_check", mActive && mCanApplyImmediately && !mNoCopyTextureSelected);
	childSetEnabled("Select", mActive);
	childSetEnabled("Pipette", mActive);
	childSetValue("Pipette", LLToolMgr::getInstance()->getCurrentTool() == LLToolPipette::getInstance());

	//RN: reset search bar to reflect actual search query (all caps, for example)
	mSearchEdit->setText(mInventoryPanel->getFilterSubString());

	//BOOL allow_copy = FALSE;
	if( mOwner ) 
	{
		mTexturep = NULL;
		if(mImageAssetID.notNull())
		{
			mTexturep = gImageList.getImage(mImageAssetID, MIPMAP_YES, IMMEDIATE_NO);
			mTexturep->setBoostLevel(LLViewerImageBoostLevel::BOOST_PREVIEW);
		}
		else if (!mFallbackImageName.empty())
		{
			mTexturep = gImageList.getImageFromFile(mFallbackImageName);
			mTexturep->setBoostLevel(LLViewerImageBoostLevel::BOOST_PREVIEW);
		}

		if (mTentativeLabel)
		{
			mTentativeLabel->setVisible( FALSE  );
		}

		childSetEnabled("Default",  mImageAssetID != mOwner->getDefaultImageAssetID());
		childSetEnabled("Blank",   mImageAssetID != mWhiteImageAssetID );
		childSetEnabled("None", mOwner->getAllowNoTexture() && !mImageAssetID.isNull() );

		LLFloater::draw();

		if( isMinimized() )
		{
			return;
		}

		// Border
		LLRect border( BORDER_PAD, 
				getRect().getHeight() - LLFLOATER_HEADER_SIZE - BORDER_PAD, 
				((TEX_PICKER_MIN_WIDTH / 2) - TEXTURE_INVENTORY_PADDING - HPAD) - BORDER_PAD,
				BORDER_PAD + FOOTER_HEIGHT + (getRect().getHeight() - TEX_PICKER_MIN_HEIGHT));
		gl_rect_2d( border, LLColor4::black, FALSE );


		// Interior
		LLRect interior = border;
		interior.stretch( -1 ); 

		if( mTexturep )
		{
			if( mTexturep->getComponents() == 4 )
			{
				gl_rect_2d_checkerboard( interior );
			}

			gl_draw_scaled_image( interior.mLeft, interior.mBottom, interior.getWidth(), interior.getHeight(), mTexturep );

			// Pump the priority
			mTexturep->addTextureStats( (F32)(interior.getWidth() * interior.getHeight()) );

			// Draw Tentative Label over the image
			if( mOwner->getTentative() && !mIsDirty )
			{
				mTentativeLabel->setVisible( TRUE );
				drawChild(mTentativeLabel);
			}
		}
		else
		{
			gl_rect_2d( interior, LLColor4::grey, TRUE );

			// Draw X
			gl_draw_x(interior, LLColor4::black );
		}
	}
}