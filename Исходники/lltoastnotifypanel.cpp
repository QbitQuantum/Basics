void LLToastNotifyPanel::updateButtonsLayout(const std::vector<index_button_pair_t>& buttons, S32 h_pad)
{
	S32 left = 0;
	//reserve place for ignore button
	S32 bottom_offset = mIsScriptDialog ? (BTN_HEIGHT + IGNORE_BTN_TOP_DELTA + BOTTOM_PAD) : BOTTOM_PAD;
	S32 max_width = mControlPanel->getRect().getWidth();
	LLButton* ignore_btn = NULL;
	for (std::vector<index_button_pair_t>::const_iterator it = buttons.begin(); it != buttons.end(); it++)
	{
		if (it->first == -1)
		{
			ignore_btn = it->second;
			continue;
		}
		LLButton* btn = it->second;
		LLRect btn_rect(btn->getRect());
		if (left + btn_rect.getWidth() > max_width)// whether there is still some place for button+h_pad in the mControlPanel
		{
			// looks like we need to add button to the next row
			left = 0;
			bottom_offset += (BTN_HEIGHT + VPAD);
		}
		//we arrange buttons from bottom to top for backward support of old script
		btn_rect.setOriginAndSize(left, bottom_offset, btn_rect.getWidth(),	btn_rect.getHeight());
		btn->setRect(btn_rect);
		left = btn_rect.mLeft + btn_rect.getWidth() + h_pad;
		mControlPanel->addChild(btn, -1);
	}
	if (mIsScriptDialog && ignore_btn != NULL)
	{
		LLRect ignore_btn_rect(ignore_btn->getRect());
		S32 buttons_per_row = max_width / BUTTON_WIDTH; //assume that h_pad far less than BUTTON_WIDTH
		S32 ignore_btn_left = buttons_per_row * BUTTON_WIDTH + (buttons_per_row	- 1) * h_pad - ignore_btn_rect.getWidth();
		if (ignore_btn_left + ignore_btn_rect.getWidth() > max_width)// make sure that the ignore button is in panel
		{
			ignore_btn_left = max_width - ignore_btn_rect.getWidth() - 2 * HPAD;
		}
		ignore_btn_rect.setOriginAndSize(ignore_btn_left, BOTTOM_PAD,// always move ignore button at the bottom
				ignore_btn_rect.getWidth(), ignore_btn_rect.getHeight());
		ignore_btn->setRect(ignore_btn_rect);
		mControlPanel->addChild(ignore_btn, -1);
	}
}