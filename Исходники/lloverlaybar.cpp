void LLOverlayBar::layoutButtons()
{
	LLView* state_buttons_panel = getChildView("state_buttons");

	if (state_buttons_panel->getVisible())
	{
		LLViewQuery query;
		LLWidgetTypeFilter<LLButton> widget_filter;
		query.addPreFilter(LLEnabledFilter::getInstance());
		query.addPreFilter(&widget_filter);

		child_list_t button_list = query(state_buttons_panel);

		const S32 MAX_BAR_WIDTH = 600;
		S32 bar_width = llclamp(state_buttons_panel->getRect().getWidth(), 0, MAX_BAR_WIDTH);

		// calculate button widths
		const S32 MAX_BUTTON_WIDTH = 150;
		S32 segment_width = llclamp(lltrunc((F32)(bar_width) / (F32)button_list.size()), 0, MAX_BUTTON_WIDTH);
		S32 btn_width = segment_width - gSavedSettings.getS32("StatusBarPad");

		// Evenly space all buttons, starting from left
		S32 left = 0;
		S32 bottom = 1;

		for (child_list_reverse_iter_t child_iter = button_list.rbegin();
			child_iter != button_list.rend(); ++child_iter)
		{
			LLView *view = *child_iter;
			LLRect r = view->getRect();
			r.setOriginAndSize(left, bottom, btn_width, r.getHeight());
			view->setRect(r);
			left += segment_width;
		}
	}
}