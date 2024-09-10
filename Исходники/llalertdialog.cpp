void LLAlertDialog::createDialog(const std::vector<LLString>* optionsp, S32 default_option,
								 const LLString& msg_in, const LLString::format_map_t& args,
								 const LLString& edit_text)
{
	setBackgroundVisible(TRUE);
	setBackgroundOpaque(TRUE);

	const LLFontGL* font = gResMgr->getRes( font_name );
	const S32 LINE_HEIGHT = llfloor(font->getLineHeight() + 0.99f);
	const S32 EDITOR_HEIGHT = 20;

	// Buttons
	std::vector<LLString> default_option_list;
	mNumOptions = optionsp->size();
	if( 0 == mNumOptions )
	{
		default_option_list.push_back("Close");
		optionsp = &default_option_list;
		default_option = 0;
		mNumOptions = 1;
	}

	const std::vector<LLString>& options = *optionsp;
	mButtonData = new ButtonData[mNumOptions];

	// Calc total width of buttons
	S32 button_width = 0;
	S32 sp = font->getWidth("OO");
	for( S32 i = 0; i < mNumOptions; i++ )
	{
		S32 w = S32(font->getWidth( options[i] ) + 0.99f) + sp + 2 * LLBUTTON_H_PAD;
		button_width = llmax( w, button_width );
	}
	S32 btn_total_width = button_width;
	if( mNumOptions > 1 )
	{
		btn_total_width = (mNumOptions * button_width) + ((mNumOptions - 1) * BTN_HPAD);
	}

	// Message: create text box using raw string, as text has been structure deliberately
	// Use size of created text box to generate dialog box size
	LLString msg = msg_in;
	format( msg, args );		 
	llwarns << "Alert: " << msg << llendl;
	LLTextBox* msg_box = new LLTextBox( "Alert message", msg, (F32)MAX_ALLOWED_MSG_WIDTH, font );

	const LLRect& text_rect = msg_box->getRect();
	S32 dialog_width = llmax( btn_total_width, text_rect.getWidth() ) + 2 * HPAD;
	S32 dialog_height = text_rect.getHeight() + 3 * VPAD + BTN_HEIGHT;

	if (hasTitleBar())
	{
		dialog_height += LINE_HEIGHT; // room for title bar
	}

	if (edit_text.size() > 0)
	{
		dialog_width = llmax(dialog_width, S32(font->getWidth( edit_text ) + 0.99f));
		dialog_height += EDITOR_HEIGHT;
	}
	if (mCaution)
	{
		// Make room for the caution icon.
		dialog_width += 32 + HPAD;
	}
	reshape( dialog_width, dialog_height, FALSE );

	S32 msg_y = mRect.getHeight() - VPAD;
	S32 msg_x = HPAD;
	if (hasTitleBar())
	{
		msg_y -= LINE_HEIGHT; // room for title
	}

	if (mCaution)
	{
		LLIconCtrl* icon = new LLIconCtrl("icon", LLRect(msg_x, msg_y, msg_x+32, msg_y-32), "notify_caution_icon.tga");
		icon->setMouseOpaque(FALSE);
		addChild(icon);
		msg_x += 32 + HPAD;
		msg_box->setColor( LLUI::sColorsGroup->getColor( "AlertCautionTextColor" ) );
	}
	else
	{
		msg_box->setColor( LLUI::sColorsGroup->getColor( "AlertTextColor" ) );
	}
	LLRect rect;
	rect.setLeftTopAndSize( msg_x, msg_y, text_rect.getWidth(), text_rect.getHeight() );
	msg_box->setRect( rect );
	addChild(msg_box);

	// Buttons	
	S32 button_left = (mRect.getWidth() - btn_total_width) / 2;

	for( S32 i = 0; i < mNumOptions; i++ )
	{
		LLRect button_rect;
		button_rect.setOriginAndSize( button_left, VPAD, button_width, BTN_HEIGHT );

		LLButton* btn = new LLButton(
			"btn", button_rect,
			"","", "", 
			&LLAlertDialog::onButtonPressed, (void*)(&mButtonData[i]),
			font,
			options[i], 
			options[i]);

		mButtonData[i].mSelf = this;
		mButtonData[i].mButton = btn;
		mButtonData[i].mOption = i;

		addChild(btn);

		if( i == default_option )
		{
			btn->setFocus(TRUE);
		}

		button_left += button_width + BTN_HPAD;
	}

	// (Optional) Edit Box	
	if (edit_text.size() > 0)
	{
		S32 y = VPAD + BTN_HEIGHT + VPAD/2;
		mLineEditor = new LLLineEditor("lineeditor",
			LLRect( HPAD, y+EDITOR_HEIGHT, dialog_width-HPAD, y),
			edit_text,
			LLFontGL::sSansSerif,
			STD_STRING_STR_LEN);

		// make sure all edit keys get handled properly
		mLineEditor->setHandleEditKeysDirectly(TRUE);

		addChild(mLineEditor);
	}
}