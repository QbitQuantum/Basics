LLCheckBoxCtrl::LLCheckBoxCtrl(const std::string& name, const LLRect& rect, 
							    const std::string& label, 
								const LLFontGL* font,
								void (*commit_callback)(LLUICtrl* ctrl, void* userdata),
								void* callback_user_data,
								BOOL initial_value,
								BOOL use_radio_style,
								const std::string& control_which)
:	LLUICtrl(name, rect, TRUE, commit_callback, callback_user_data, FOLLOWS_LEFT | FOLLOWS_TOP),
	mTextEnabledColor( LLUI::sColorsGroup->getColor( "LabelTextColor" ) ),
	mTextDisabledColor( LLUI::sColorsGroup->getColor( "LabelDisabledColor" ) ),
	mRadioStyle( use_radio_style ),
	mInitialValue( initial_value ),
	mSetValue( initial_value )
{
	if (font)
	{
		mFont = font;
	}
	else
	{
		mFont = LLFontGL::getFontSansSerifSmall();
	}

	// must be big enough to hold all children
	setUseBoundingRect(TRUE);

	mKeyboardFocusOnClick = TRUE;

	// Label (add a little space to make sure text actually renders)
	const S32 FUDGE = 10;
	S32 text_width = mFont->getWidth( label ) + FUDGE;
	S32 text_height = llround(mFont->getLineHeight());
	LLRect label_rect;
	label_rect.setOriginAndSize(
		LLCHECKBOXCTRL_HPAD + LLCHECKBOXCTRL_BTN_SIZE + LLCHECKBOXCTRL_SPACING,
		LLCHECKBOXCTRL_VPAD + 1, // padding to get better alignment
		text_width + LLCHECKBOXCTRL_HPAD,
		text_height );

	// *HACK Get rid of this with SL-55508... 
	// this allows blank check boxes and radio boxes for now
	std::string local_label = label;
	if(local_label.empty())
	{
		local_label = " ";
	}

	mLabel = new LLTextBox( std::string("CheckboxCtrl Label"), label_rect, local_label, mFont );
	mLabel->setFollowsLeft();
	mLabel->setFollowsBottom();
	addChild(mLabel);

	// Button
	// Note: button cover the label by extending all the way to the right.
	LLRect btn_rect;
	btn_rect.setOriginAndSize(
		LLCHECKBOXCTRL_HPAD,
		LLCHECKBOXCTRL_VPAD,
		LLCHECKBOXCTRL_BTN_SIZE + LLCHECKBOXCTRL_SPACING + text_width + LLCHECKBOXCTRL_HPAD,
		llmax( text_height, LLCHECKBOXCTRL_BTN_SIZE ) + LLCHECKBOXCTRL_VPAD);
	std::string active_true_id, active_false_id;
	std::string inactive_true_id, inactive_false_id;
	if (mRadioStyle)
	{
		active_true_id = "UIImgRadioActiveSelectedUUID";
		active_false_id = "UIImgRadioActiveUUID";
		inactive_true_id = "UIImgRadioInactiveSelectedUUID";
		inactive_false_id = "UIImgRadioInactiveUUID";
		mButton = new LLButton(std::string("Radio control button"), btn_rect,
							   active_false_id, active_true_id, control_which,
							   &LLCheckBoxCtrl::onButtonPress, this, LLFontGL::getFontSansSerif() ); 
		mButton->setDisabledImages( inactive_false_id, inactive_true_id );
		mButton->setHoverGlowStrength(0.35f);
	}
	else
	{
		active_false_id = "UIImgCheckboxActiveUUID";
		active_true_id = "UIImgCheckboxActiveSelectedUUID";
		inactive_true_id = "UIImgCheckboxInactiveSelectedUUID";
		inactive_false_id = "UIImgCheckboxInactiveUUID";
		mButton = new LLButton(std::string("Checkbox control button"), btn_rect,
							   active_false_id, active_true_id, control_which,
							   &LLCheckBoxCtrl::onButtonPress, this, LLFontGL::getFontSansSerif() ); 
		mButton->setDisabledImages( inactive_false_id, inactive_true_id );
		mButton->setHoverGlowStrength(0.35f);
	}
	mButton->setIsToggle(TRUE);
	mButton->setToggleState( initial_value );
	mButton->setFollowsLeft();
	mButton->setFollowsBottom();
	mButton->setCommitOnReturn(FALSE);
	addChild(mButton);
}