//--------------------------------------------------------------------------
void LLScreenChannel::showToastsTop()
{
	LLRect channel_rect = getChannelRect();

	LLRect	toast_rect;	
	S32		top = channel_rect.mTop;
	std::vector<ToastElem>::reverse_iterator it;

	updateRect();

	LLDockableFloater* floater = dynamic_cast<LLDockableFloater*>(LLDockableFloater::getInstanceHandle().get());

	// <FS:Ansariel> Show toasts in front of other floaters
	BOOL toasts_in_front = gSavedSettings.getBOOL("FSShowToastsInFront");

	// Use a local variable instead of mToastList.
	// mToastList can be modified during recursive calls and then all iteratos will be invalidated.
	std::vector<ToastElem> vToastList( mToastList );

	for(it = vToastList.rbegin(); it != vToastList.rend(); ++it)
	{
		if(it != vToastList.rbegin())
		{
			LLToast* toast = (it-1)->getToast();
			if (!toast)
			{
				llwarns << "Attempt to display a deleted toast." << llendl;
				return;
			}

			top = toast->getRect().mBottom - toast->getTopPad();
			gSavedSettings.getS32("ToastGap");
		}

		LLToast* toast = it->getToast();
		if (!toast)
		{
			llwarns << "Attempt to display a deleted toast." << llendl;
			return;
		}

		toast_rect = toast->getRect();
		toast_rect.setLeftTopAndSize(channel_rect.mRight - toast_rect.getWidth(),
			top, toast_rect.getWidth(),
			toast_rect.getHeight());
		toast->setRect(toast_rect);

		if(floater && floater->overlapsScreenChannel())
		{
			if(it == vToastList.rbegin())
			{
				// move first toast above docked floater
				S32 shift = -floater->getRect().getHeight();
				if(floater->getDockControl())
				{
					shift -= floater->getDockControl()->getTongueHeight();
				}
				toast->translate(0, shift);
			}

			LLRect channel_rect = getChannelRect();
			// don't show toasts if there is not enough space
			if(toast_rect.mBottom < channel_rect.mBottom)
			{
				break;
			}
		}

		bool stop_showing_toasts = toast->getRect().mBottom < channel_rect.mBottom;

		if(!stop_showing_toasts)
		{
			if( it != vToastList.rend()-1)
			{
				S32 toast_bottom = toast->getRect().mBottom - gSavedSettings.getS32("ToastGap");
				stop_showing_toasts = toast_bottom < channel_rect.mBottom;
			}
		} 

		// at least one toast should be visible
		if(it == vToastList.rbegin())
		{
			stop_showing_toasts = false;
		}

		if(stop_showing_toasts)
			break;

		if (!toast->getVisible())
		{
			// HACK
			// EXT-2653: it is necessary to prevent overlapping for secondary showed toasts
			toast->setVisible(TRUE);
		}		
		// <FS:Ansariel> Show toasts in front of other floaters
		//if (!toast->hasFocus())
		if (!toast->hasFocus() && !toasts_in_front)
		// </FS:Ansariel> Show toasts in front of other floaters
		{
			// Fixing Z-order of toasts (EXT-4862)
			// Next toast will be positioned under this one.
			gFloaterView->sendChildToBack(toast);
		}
	}

	// Dismiss toasts we don't have space for (STORM-391).
	std::vector<LLToast*> toasts_to_hide;

	if(it != vToastList.rend())
	{
		mHiddenToastsNum = 0;

		for(; it != vToastList.rend(); it++)
		{
			LLToast* toast = it->getToast();
			if (toast)
			{
				toasts_to_hide.push_back(toast);
			}
		}
	}

	for (std::vector<LLToast*>::iterator it = toasts_to_hide.begin(), end_it = toasts_to_hide.end();
		it != end_it;
		++it)
	{
		(*it)->hide();
	}
}