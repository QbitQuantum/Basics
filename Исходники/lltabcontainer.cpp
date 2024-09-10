BOOL LLTabContainer::setTab(S32 which)
{
	if (which == -1)
	{
		if (mNextTabIdx == -1)
		{
			return FALSE;
		}
		which = mNextTabIdx;
		mNextTabIdx = -1;
	}

	LLTabTuple* selected_tuple = getTab(which);
	if (!selected_tuple)
	{
		return FALSE;
	}

	BOOL is_visible = FALSE;
	if (selected_tuple->mButton->getEnabled())
	{
		setCurrentPanelIndex(which);

		S32 i = 0;
		for(tuple_list_t::iterator iter = mTabList.begin(); iter != mTabList.end(); ++iter)
		{
			LLTabTuple* tuple = *iter;
			BOOL is_selected = ( tuple == selected_tuple );
			tuple->mTabPanel->setVisible( is_selected );
// 			tuple->mTabPanel->setFocus(is_selected); // not clear that we want to do this here.
			tuple->mButton->setToggleState( is_selected );
			// RN: this limits tab-stops to active button only, which would require arrow keys to switch tabs
			tuple->mButton->setTabStop( is_selected );
			
			if( is_selected && (mIsVertical || (getMaxScrollPos() > 0)))
			{
				// Make sure selected tab is within scroll region
				if (mIsVertical)
				{
					S32 num_visible = getTabCount() - getMaxScrollPos();
					if( i >= getScrollPos() && i <= getScrollPos() + num_visible)
					{
						setCurrentPanelIndex(which);
						is_visible = TRUE;
					}
					else
					{
						is_visible = FALSE;
					}
				}
				else
				{
					if( i < getScrollPos() )
					{
						setScrollPos(i);
					}
					else
					{
						S32 available_width_with_arrows = getRect().getWidth() - mRightTabBtnOffset - 2 * (LLPANEL_BORDER_WIDTH + TABCNTR_ARROW_BTN_SIZE  + TABCNTR_ARROW_BTN_SIZE + 1);
						S32 running_tab_width = tuple->mButton->getRect().getWidth();
						S32 j = i - 1;
						S32 min_scroll_pos = i;
						if (running_tab_width < available_width_with_arrows)
						{
							while (j >= 0)
							{
								LLTabTuple* other_tuple = getTab(j);
								running_tab_width += other_tuple->mButton->getRect().getWidth();
								if (running_tab_width > available_width_with_arrows)
								{
									break;
								}
								j--;
							}
							min_scroll_pos = j + 1;
						}
						setScrollPos(llclamp(getScrollPos(), min_scroll_pos, i));
						setScrollPos(llmin(getScrollPos(), getMaxScrollPos()));
					}
					is_visible = TRUE;
				}
			}
			i++;
		}
		if( selected_tuple->mOnChangeCallback )
		{
			selected_tuple->mOnChangeCallback( selected_tuple->mUserData, false );
		}
	}
	if (mIsVertical && getCurrentPanelIndex() >= 0)
	{
		LLTabTuple* tuple = getTab(getCurrentPanelIndex());
		tuple->mTabPanel->setVisible( TRUE );
		tuple->mButton->setToggleState( TRUE );
	}
	return is_visible;
}