void LLPanelPrimMediaControls::updateShape()
{
	LLViewerMediaImpl* media_impl = getTargetMediaImpl();
	LLViewerObject* objectp = getTargetObject();
	
	if(!media_impl || gFloaterTools->getVisible())
	{
		setVisible(FALSE);
		return;
	}

	LLPluginClassMedia* media_plugin = NULL;
	if(media_impl->hasMedia())
	{
		media_plugin = media_impl->getMediaPlugin();
	}
	
	LLParcel *parcel = LLViewerParcelMgr::getInstance()->getAgentParcel();

	bool can_navigate = parcel->getMediaAllowNavigate();
	bool enabled = false;
	bool is_zoomed = (mCurrentZoom != ZOOM_NONE) && (mTargetObjectID == mZoomObjectID) && (mTargetObjectFace == mZoomObjectFace);
	// There is no such thing as "has_focus" being different from normal controls set
	// anymore (as of user feedback from bri 10/09).  So we cheat here and force 'has_focus'
	// to 'true' (or, actually, we use a setting)
	bool has_focus = (gSavedSettings.getBOOL("PrimMediaControlsUseHoverControlSet")) ? media_impl->hasFocus() : true;
	setVisible(enabled);

	if (objectp)
	{
		bool mini_controls = false;
		LLMediaEntry *media_data = objectp->getTE(mTargetObjectFace)->getMediaData();
		if (media_data && NULL != dynamic_cast<LLVOVolume*>(objectp))
		{
			// Don't show the media controls if we do not have permissions
			enabled = dynamic_cast<LLVOVolume*>(objectp)->hasMediaPermission(media_data, LLVOVolume::MEDIA_PERM_CONTROL);
			mini_controls = (LLMediaEntry::MINI == media_data->getControls());
		}
		const bool is_hud = objectp->isHUDAttachment();
		
		//
		// Set the state of the buttons
		//
		
		// XXX RSP: TODO: FIXME: clean this up so that it is clearer what mode we are in,
		// and that only the proper controls get made visible/enabled according to that mode. 
		mBackCtrl->setVisible(has_focus);
		mFwdCtrl->setVisible(has_focus);
		mReloadCtrl->setVisible(has_focus);
		mStopCtrl->setVisible(false);
		mHomeCtrl->setVisible(has_focus);
		mZoomCtrl->setVisible(!is_zoomed);
		mUnzoomCtrl->setVisible(is_zoomed);
		mOpenCtrl->setVisible(true);
		mMediaAddressCtrl->setVisible(has_focus && !mini_controls);
		mMediaPlaySliderPanel->setVisible(has_focus && !mini_controls);
		mVolumeCtrl->setVisible(false);
		
		mWhitelistIcon->setVisible(!mini_controls && (media_data)?media_data->getWhiteListEnable():false);
		// Disable zoom if HUD
		mZoomCtrl->setEnabled(!is_hud);
		mUnzoomCtrl->setEnabled(!is_hud);
		mSecureLockIcon->setVisible(false);
		mCurrentURL = media_impl->getCurrentMediaURL();
		
		mBackCtrl->setEnabled((media_impl != NULL) && media_impl->canNavigateBack() && can_navigate);
		mFwdCtrl->setEnabled((media_impl != NULL) && media_impl->canNavigateForward() && can_navigate);
		mStopCtrl->setEnabled(has_focus && can_navigate);
		mHomeCtrl->setEnabled(has_focus && can_navigate);
		LLPluginClassMediaOwner::EMediaStatus result = ((media_impl != NULL) && media_impl->hasMedia()) ? media_plugin->getStatus() : LLPluginClassMediaOwner::MEDIA_NONE;
		
		mVolumeCtrl->setVisible(has_focus);
		mVolumeCtrl->setEnabled(has_focus);
		mVolumeSliderCtrl->setEnabled(has_focus && shouldVolumeSliderBeVisible());
		mVolumeSliderCtrl->setVisible(has_focus && shouldVolumeSliderBeVisible());

		if(media_plugin && media_plugin->pluginSupportsMediaTime())
		{
			mReloadCtrl->setEnabled(false);
			mReloadCtrl->setVisible(false);
			mMediaStopCtrl->setVisible(has_focus);
			mHomeCtrl->setVisible(has_focus);
			mBackCtrl->setVisible(false);
			mFwdCtrl->setVisible(false);
			mMediaAddressCtrl->setVisible(false);
			mMediaAddressCtrl->setEnabled(false);
			mMediaPlaySliderPanel->setVisible(has_focus && !mini_controls);
			mMediaPlaySliderPanel->setEnabled(has_focus && !mini_controls);
			mSkipFwdCtrl->setVisible(has_focus && !mini_controls);
			mSkipFwdCtrl->setEnabled(has_focus && !mini_controls);
			mSkipBackCtrl->setVisible(has_focus && !mini_controls);
			mSkipBackCtrl->setEnabled(has_focus && !mini_controls);
			
			mVolumeCtrl->setVisible(has_focus);
			mVolumeCtrl->setEnabled(has_focus);
			mVolumeSliderCtrl->setEnabled(has_focus && shouldVolumeSliderBeVisible());
			mVolumeSliderCtrl->setVisible(has_focus && shouldVolumeSliderBeVisible());
			
			mWhitelistIcon->setVisible(false);
			mSecureLockIcon->setVisible(false);
			if (mMediaPanelScroll)
			{
				mMediaPanelScroll->setVisible(false);
				mScrollUpCtrl->setVisible(false);
				mScrollDownCtrl->setVisible(false);
				mScrollRightCtrl->setVisible(false);
				mScrollDownCtrl->setVisible(false);
			}
			
			F32 volume = media_impl->getVolume();
			// movie's url changed
			if(mCurrentURL!=mPreviousURL)
			{
				mMovieDuration = media_plugin->getDuration();
				mPreviousURL = mCurrentURL;
			}
			
			if(mMovieDuration == 0) 
			{
				mMovieDuration = media_plugin->getDuration();
				mMediaPlaySliderCtrl->setValue(0);
				mMediaPlaySliderCtrl->setEnabled(false);
			}
			// TODO: What if it's not fully loaded
			
			if(mUpdateSlider && mMovieDuration!= 0)
			{
				F64 current_time =  media_plugin->getCurrentTime();
				F32 percent = current_time / mMovieDuration;
				mMediaPlaySliderCtrl->setValue(percent);
				mMediaPlaySliderCtrl->setEnabled(true);
			}
			
			// video vloume
			if(volume <= 0.0)
			{
				mMuteBtn->setToggleState(true);
			}
			else if (volume >= 1.0)
			{
				mMuteBtn->setToggleState(false);
			}
			else
			{
				mMuteBtn->setToggleState(false);
			}
			
			switch(result)
			{
				case LLPluginClassMediaOwner::MEDIA_PLAYING:
					mPlayCtrl->setEnabled(FALSE);
					mPlayCtrl->setVisible(FALSE);
					mPauseCtrl->setEnabled(TRUE);
					mPauseCtrl->setVisible(has_focus);
					
					break;
				case LLPluginClassMediaOwner::MEDIA_PAUSED:
				default:
					mPauseCtrl->setEnabled(FALSE);
					mPauseCtrl->setVisible(FALSE);
					mPlayCtrl->setEnabled(TRUE);
					mPlayCtrl->setVisible(has_focus);
					break;
			}
		}
		else   // web based
		{
			if(media_plugin)
			{
				mCurrentURL = media_plugin->getLocation();
			}
			else
			{
				mCurrentURL.clear();
			}
			
			mPlayCtrl->setVisible(FALSE);
			mPauseCtrl->setVisible(FALSE);
			mMediaStopCtrl->setVisible(FALSE);
			mMediaAddressCtrl->setVisible(has_focus && !mini_controls);
			mMediaAddressCtrl->setEnabled(has_focus && !mini_controls);
			mMediaPlaySliderPanel->setVisible(FALSE);
			mMediaPlaySliderPanel->setEnabled(FALSE);
			mSkipFwdCtrl->setVisible(FALSE);
			mSkipFwdCtrl->setEnabled(FALSE);
			mSkipBackCtrl->setVisible(FALSE);
			mSkipBackCtrl->setEnabled(FALSE);
			
			if(media_impl->getVolume() <= 0.0)
			{
				mMuteBtn->setToggleState(true);
			}
			else
			{
				mMuteBtn->setToggleState(false);
			}

			if (mMediaPanelScroll)
			{
				mMediaPanelScroll->setVisible(has_focus);
				mScrollUpCtrl->setVisible(has_focus);
				mScrollDownCtrl->setVisible(has_focus);
				mScrollRightCtrl->setVisible(has_focus);
				mScrollDownCtrl->setVisible(has_focus);
			}
			// TODO: get the secure lock bool from media plug in
			std::string prefix =  std::string("https://");
			std::string test_prefix = mCurrentURL.substr(0, prefix.length());
			LLStringUtil::toLower(test_prefix);
			if(test_prefix == prefix)
			{
				mSecureLockIcon->setVisible(has_focus);
			}
			
			if(mCurrentURL!=mPreviousURL)
			{
				setCurrentURL();
				mPreviousURL = mCurrentURL;
			}
			
			if(result == LLPluginClassMediaOwner::MEDIA_LOADING)
			{
				mReloadCtrl->setEnabled(FALSE);
				mReloadCtrl->setVisible(FALSE);
				mStopCtrl->setEnabled(TRUE);
				mStopCtrl->setVisible(has_focus);
			}
			else
			{
				mReloadCtrl->setEnabled(TRUE);
				mReloadCtrl->setVisible(has_focus);
				mStopCtrl->setEnabled(FALSE);
				mStopCtrl->setVisible(FALSE);
			}
		}
		
		
		if(media_plugin)
		{
			//
			// Handle progress bar
			//
			if(LLPluginClassMediaOwner::MEDIA_LOADING == media_plugin->getStatus())
			{	
				mMediaProgressPanel->setVisible(true);
				mMediaProgressBar->setValue(media_plugin->getProgressPercent());
			}
			else
			{
				mMediaProgressPanel->setVisible(false);
			}
		}
		
		if(media_impl)
		{
			//
			// Handle Scrolling
			//
			switch (mScrollState) 
			{
				case SCROLL_UP:
					media_impl->scrollWheel(0, -1, MASK_NONE);
					break;
				case SCROLL_DOWN:
					media_impl->scrollWheel(0, 1, MASK_NONE);
					break;
				case SCROLL_LEFT:
					media_impl->scrollWheel(1, 0, MASK_NONE);
					//				media_impl->handleKeyHere(KEY_LEFT, MASK_NONE);
					break;
				case SCROLL_RIGHT:
					media_impl->scrollWheel(-1, 0, MASK_NONE);
					//				media_impl->handleKeyHere(KEY_RIGHT, MASK_NONE);
					break;
				case SCROLL_NONE:
		default:
					break;
			}
		}
		
		setVisible(enabled);
		
		//
		// Calculate position and shape of the controls
		//
		std::vector<LLVector3>::iterator vert_it;
		std::vector<LLVector3>::iterator vert_end;
		std::vector<LLVector3> vect_face;
		
		LLVolume* volume = objectp->getVolume();
		
		if (volume)
		{
			const LLVolumeFace& vf = volume->getVolumeFace(mTargetObjectFace);
			
			LLVector3 ext[2];
			ext[0].set(vf.mExtents[0].getF32ptr());
			ext[1].set(vf.mExtents[1].getF32ptr());
			
			LLVector3 center = (ext[0]+ext[1])*0.5f;
			LLVector3 size = (ext[1]-ext[0])*0.5f;
			LLVector3 vert[] =
			{
				center + size.scaledVec(LLVector3(1,1,1)),
				center + size.scaledVec(LLVector3(-1,1,1)),
				center + size.scaledVec(LLVector3(1,-1,1)),
				center + size.scaledVec(LLVector3(-1,-1,1)),
				center + size.scaledVec(LLVector3(1,1,-1)),
				center + size.scaledVec(LLVector3(-1,1,-1)),
				center + size.scaledVec(LLVector3(1,-1,-1)),
				center + size.scaledVec(LLVector3(-1,-1,-1)),
			};

			LLVOVolume* vo = (LLVOVolume*) objectp;

			for (U32 i = 0; i < 8; i++)
			{
				vect_face.push_back(vo->volumePositionToAgent(vert[i]));	
			}
		}
		vert_it = vect_face.begin();
		vert_end = vect_face.end();
		
		LLMatrix4a mat;
		if (!is_hud) 
		{
			mat.setMul(glh_get_current_projection(),glh_get_current_modelview());
		}
		else {
			LLMatrix4a proj, modelview;
			if (get_hud_matrices(proj, modelview))
			{
				//mat = proj * modelview;
				mat.setMul(proj,modelview);
			}
		}
		LLVector4a min;
		min.splat(1.f);
		LLVector4a max;
		max.splat(-1.f);
		for(; vert_it != vert_end; ++vert_it)
		{
			// project silhouette vertices into screen space
			LLVector4a screen_vert;
			screen_vert.load3(vert_it->mV,1.f);

			mat.perspectiveTransform(screen_vert,screen_vert);

			// add to screenspace bounding box
			min.setMin(screen_vert,min);
			max.setMax(screen_vert,max);
		}
		
		// convert screenspace bbox to pixels (in screen coords)
		LLRect window_rect = gViewerWindow->getWorldViewRectScaled();
		LLCoordGL screen_min;
		screen_min.mX = ll_round((F32)window_rect.mLeft + (F32)window_rect.getWidth() * (min.getF32ptr()[VX] + 1.f) * 0.5f);
		screen_min.mY = ll_round((F32)window_rect.mBottom + (F32)window_rect.getHeight() * (min.getF32ptr()[VY] + 1.f) * 0.5f);
		
		LLCoordGL screen_max;
		screen_max.mX = ll_round((F32)window_rect.mLeft + (F32)window_rect.getWidth() * (max.getF32ptr()[VX] + 1.f) * 0.5f);
		screen_max.mY = ll_round((F32)window_rect.mBottom + (F32)window_rect.getHeight() * (max.getF32ptr()[VY] + 1.f) * 0.5f);
		
		// grow panel so that screenspace bounding box fits inside "media_region" element of panel
		LLRect media_panel_rect;
		// Get the height of the controls (less the volume slider)
		S32 controls_height = mMediaControlsStack->getRect().getHeight() - mVolumeSliderCtrl->getRect().getHeight();
		getParent()->screenRectToLocal(LLRect(screen_min.mX, screen_max.mY, screen_max.mX, screen_min.mY), &media_panel_rect);
		media_panel_rect.mTop += controls_height;
		
		// keep all parts of panel on-screen
		// Area of the top of the world view to avoid putting the controls
		window_rect.mTop -= mTopWorldViewAvoidZone;
		// Don't include "spacing" bookends on left & right of the media controls
		window_rect.mLeft -= mLeftBookend->getRect().getWidth();
		window_rect.mRight += mRightBookend->getRect().getWidth();
		// Don't include the volume slider
		window_rect.mBottom -= mVolumeSliderCtrl->getRect().getHeight();
		media_panel_rect.intersectWith(window_rect);
		
		// clamp to minimum size, keeping rect inside window
		S32 centerX = media_panel_rect.getCenterX();
		S32 centerY = media_panel_rect.getCenterY();
		// Shrink screen rect by min width and height, to ensure containment
		window_rect.stretch(-mMinWidth/2, -mMinHeight/2);
		window_rect.clampPointToRect(centerX, centerY);
		media_panel_rect.setCenterAndSize(centerX, centerY, 
										  llmax(mMinWidth, media_panel_rect.getWidth()),
										  llmax(mMinHeight, media_panel_rect.getHeight()));
		
		// Finally set the size of the panel
		setShape(media_panel_rect, true);
		
		// Test mouse position to see if the cursor is stationary
		LLCoordWindow cursor_pos_window;
		getWindow()->getCursorPosition(&cursor_pos_window);
		
		// If last pos is not equal to current pos, the mouse has moved
		// We need to reset the timer, and make sure the panel is visible
		if(cursor_pos_window.mX != mLastCursorPos.mX ||
		   cursor_pos_window.mY != mLastCursorPos.mY ||
		   mScrollState != SCROLL_NONE)
		{
			mInactivityTimer.start();
			mLastCursorPos = cursor_pos_window;
		}
		
		if(isMouseOver() || hasFocus())
		{
			// Never fade the controls if the mouse is over them or they have keyboard focus.
			mFadeTimer.stop();
		}
		else if(!mClearFaceOnFade && (mInactivityTimer.getElapsedTimeF32() < mInactiveTimeout))
		{
			// Mouse is over the object, but has not been stationary for long enough to fade the UI
			mFadeTimer.stop();
		}
		else if(! mFadeTimer.getStarted() )
		{
			// we need to start fading the UI (and we have not already started)
			mFadeTimer.reset();
			mFadeTimer.start();
		}
		else
		{
			// I don't think this is correct anymore.  This is done in draw() after the fade has completed.
			//			setVisible(FALSE);
		}
	}
}