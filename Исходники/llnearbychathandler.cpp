void LLNearbyChatScreenChannel::arrangeToasts()
{
	if(mStopProcessing || isHovering())
		return;

	if (mFloaterSnapRegion == NULL)
	{
		mFloaterSnapRegion = gViewerWindow->getRootView()->getChildView("floater_snap_region");
	}
	
	if (!getParent())
	{
		// connect to floater snap region just to get resize events, we don't care about being a proper widget 
		mFloaterSnapRegion->addChild(this);
		setFollows(FOLLOWS_ALL);
	}

	LLRect	toast_rect;	
	updateRect();

	LLRect channel_rect;
	mFloaterSnapRegion->localRectToOtherView(mFloaterSnapRegion->getLocalRect(), &channel_rect, gFloaterView);
	channel_rect.mLeft += 10;
	channel_rect.mRight = channel_rect.mLeft + 300;

	S32 channel_bottom = channel_rect.mBottom;

	// <FS:Ansariel> Configurable nearby chat toasts offset
	//S32		bottom = channel_bottom + 80;
	S32		bottom = channel_bottom + gSavedSettings.getS32("FSNearbyChatToastsOffset");
	S32		margin = gSavedSettings.getS32("ToastGap");

	//sort active toasts
	std::sort(m_active_toasts.begin(),m_active_toasts.end(),sort_toasts_predicate);

	//calc max visible item and hide other toasts.

	for(toast_vec_t::iterator it = m_active_toasts.begin(); it != m_active_toasts.end(); ++it)
	{
		LLToast* toast = it->get();
		if (!toast)
		{
			llwarns << "NULL found in the active chat toasts list!" << llendl;
			continue;
		}

		S32 toast_top = bottom + toast->getRect().getHeight() + margin;

		if(toast_top > channel_rect.getHeight())
		{
			while(it!=m_active_toasts.end())
			{
				addToToastPool(it->get());
				it=m_active_toasts.erase(it);
			}
			break;
		}

		toast_rect = toast->getRect();
		toast_rect.setLeftTopAndSize(channel_rect.mLeft , bottom + toast_rect.getHeight(), toast_rect.getWidth() ,toast_rect.getHeight());

		toast->setRect(toast_rect);
		bottom += toast_rect.getHeight() - toast->getTopPad() + margin;
	}
	
	// use reverse order to provide correct z-order and avoid toast blinking
	
	for(toast_vec_t::reverse_iterator it = m_active_toasts.rbegin(); it != m_active_toasts.rend(); ++it)
	{
		LLToast* toast = it->get();
		if (toast)
		{
		toast->setIsHidden(false);
		toast->setVisible(TRUE);
		}
	}

}