//---------------------------------------------------------------------------
// Public methods
//---------------------------------------------------------------------------
LLPanelLogin::LLPanelLogin(const LLRect &rect,
						 BOOL show_server,
						 void (*callback)(S32 option, void* user_data),
						 void *cb_data)
:	LLPanel(std::string("panel_login"), LLRect(0,600,800,0), FALSE),		// not bordered
	mLogoImage(),
	mCallback(callback),
	mCallbackData(cb_data),
	mHtmlAvailable( TRUE )
{
	setFocusRoot(TRUE);

	setBackgroundVisible(FALSE);
	setBackgroundOpaque(TRUE);

	// instance management
	if (LLPanelLogin::sInstance)
	{
		llwarns << "Duplicate instance of login view deleted" << llendl;
		delete LLPanelLogin::sInstance;

		// Don't leave bad pointer in gFocusMgr
		gFocusMgr.setDefaultKeyboardFocus(NULL);
	}

	LLPanelLogin::sInstance = this;

	// add to front so we are the bottom-most child
	gViewerWindow->getRootView()->addChildAtEnd(this);

	// Logo
	mLogoImage = LLUI::getUIImage("startup_logo.j2c");

	LLUICtrlFactory::getInstance()->buildPanel(this, "panel_login.xml");
	
#if USE_VIEWER_AUTH
	//leave room for the login menu bar
	setRect(LLRect(0, rect.getHeight()-18, rect.getWidth(), 0)); 
#endif
	reshape(rect.getWidth(), rect.getHeight());

#if !USE_VIEWER_AUTH
	childSetPrevalidate("first_name_edit", LLLineEditor::prevalidatePrintableNoSpace);
	childSetPrevalidate("last_name_edit", LLLineEditor::prevalidatePrintableNoSpace);

		LLComboBox* name_combo = getChild<LLComboBox>("name_combo");
	// Only works as intended with this combination of flags,
	// and in this order of setting them, therefore overriding xui
	name_combo->setAllowTextEntry(TRUE);
	name_combo->setTextEntryVisible(FALSE);
	// Send it down the line, or the invisible text entry covers up our normal
	// input fields if placed after them in xui
	sendChildToBack(getChildView("name_combo"));

	bool mru_enabled = gSavedSettings.getBOOL("LoginMRUEnabled");
	if (mru_enabled)
	{
		LLSD name_list = gSavedSettings.getLLSD("LoginMRUList");
		if (name_list.isArray())
		{
			for (LLSD::array_iterator iter = name_list.endArray() - 1; iter >= name_list.beginArray(); --iter)
			{
				if (iter->isMap() && iter->has("first") && iter->has("last"))
				{
					name_combo->add((*iter)["first"].asString() + " " + (*iter)["last"].asString(), *iter);
				}
			}
		}
		childSetCommitCallback("name_combo", onSelectLoginMRU, this);
	}
	setLoginMRUEnabled(mru_enabled);


	childSetCommitCallback("password_edit", mungePassword);
	childSetKeystrokeCallback("password_edit", onPassKey, this);
	childSetUserData("password_edit", this);

	// change z sort of clickable text to be behind buttons
	sendChildToBack(getChildView("channel_text"));
	sendChildToBack(getChildView("forgot_password_text"));

	LLLineEditor* edit = getChild<LLLineEditor>("password_edit");
	if (edit) edit->setDrawAsterixes(TRUE);

	LLComboBox* combo = getChild<LLComboBox>("start_location_combo");
	combo->setAllowTextEntry(TRUE, 128, FALSE);

	// The XML file loads the combo with the following labels:
	// 0 - "My Home"
	// 1 - "My Last Location"
	// 2 - "<Type region name>"

	BOOL login_last = gSavedSettings.getBOOL("LoginLastLocation");
	std::string sim_string = LLURLSimString::sInstance.mSimString;
	if (!sim_string.empty())
	{
		// Replace "<Type region name>" with this region name
		combo->remove(2);
		combo->add( sim_string );
		combo->setTextEntry(sim_string);
		combo->setCurrentByIndex( 2 );
	}
	else if (login_last)
	{
		combo->setCurrentByIndex( 1 );
	}
	else
	{
		combo->setCurrentByIndex( 0 );
	}

	combo->setCommitCallback( &set_start_location );

	LLComboBox* server_choice_combo = sInstance->getChild<LLComboBox>("server_combo");
	server_choice_combo->setCommitCallback(onSelectServer);
	server_choice_combo->setFocusLostCallback(onServerComboLostFocus);

	childSetAction("connect_btn", onClickConnect, this);

	setDefaultBtn("connect_btn");

	// childSetAction("quit_btn", onClickQuit, this);

	std::string channel = llformat("(%s)",
		DX_CHANNEL ); 
	// Kirsten uses version Viewer headers not saved settings! for channel info.
	std::string version = llformat("%d.%d.%d (%d)",
		LL_VERSION_MAJOR,
		LL_VERSION_MINOR,
		LL_VERSION_PATCH,
		LL_VIEWER_BUILD );
	LLTextBox* channel_text = getChild<LLTextBox>("channel_text");
	channel_text->setTextArg("[CHANNEL]", channel); // though not displayed
	channel_text->setTextArg("[VERSION]", version);
	channel_text->setClickedCallback(onClickVersion);
	channel_text->setCallbackUserData(this);
	
	LLTextBox* forgot_password_text = getChild<LLTextBox>("forgot_password_text");
	forgot_password_text->setClickedCallback(onClickForgotPassword);

	LLTextBox* create_new_account_text = getChild<LLTextBox>("create_new_account_text");
	create_new_account_text->setClickedCallback(onClickNewAccount);
#endif    
	
	// get the web browser control
	LLWebBrowserCtrl* web_browser = getChild<LLWebBrowserCtrl>("login_html");
	// Need to handle login secondlife:///app/ URLs
	web_browser->setTrusted( true );

	// observe browser events
	web_browser->addObserver( this );

	// don't make it a tab stop until SL-27594 is fixed
	web_browser->setTabStop(FALSE);
	web_browser->navigateToLocalPage( "loading", "loading.html" );

	// make links open in external browser
	web_browser->setOpenInExternalBrowser( true );

	// force the size to be correct (XML doesn't seem to be sufficient to do this) (with some padding so the other login screen doesn't show through)
	LLRect htmlRect = getRect();
#if USE_VIEWER_AUTH
	htmlRect.setCenterAndSize( getRect().getCenterX() - 2, getRect().getCenterY(), getRect().getWidth() + 6, getRect().getHeight());
#else
	htmlRect.setCenterAndSize( getRect().getCenterX() - 2, getRect().getCenterY() + 40, getRect().getWidth() + 6, getRect().getHeight() - 78 );
#endif
	web_browser->setRect( htmlRect );
	web_browser->reshape( htmlRect.getWidth(), htmlRect.getHeight(), TRUE );
	reshape( getRect().getWidth(), getRect().getHeight(), 1 );

	// kick off a request to grab the url manually
	gResponsePtr = LLIamHereLogin::build( this );
	std::string login_page = gSavedSettings.getString("LoginPage");
	if (login_page.empty())
	{
		login_page = getString( "real_url" );
	}
	LLHTTPClient::head( login_page, gResponsePtr );

#if !USE_VIEWER_AUTH
	// Initialize visibility (and don't force visibility - use prefs)
	refreshLocation( false );
#endif

}