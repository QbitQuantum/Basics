BOOL LLFloaterTOS::postBuild()
{	
	childSetAction("Continue", onContinue, this);
	childSetAction("Cancel", onCancel, this);
	childSetCommitCallback("agree_chk", updateAgree, this);

	if ( mType != TOS_TOS )
	{
		llinfos << "tos_type != TOS_TOS" << llendl;
		// this displays the critical message
		LLTextEditor *editor = getChild<LLTextEditor>("tos_text");
		editor->setHandleEditKeysDirectly( TRUE );
		editor->setEnabled( FALSE );
		editor->setWordWrap(TRUE);
		editor->setFocus(TRUE);
		// editor->setValue(LLSD(mMessage));
		editor->setValue(mMessage);

		return TRUE;
	}

	// disable Agree to TOS radio button until the page has fully loaded
	LLCheckBoxCtrl* tos_agreement = getChild<LLCheckBoxCtrl>("agree_chk");
	tos_agreement->setEnabled( false );

	// hide the SL text widget if we're displaying TOS with using a browser widget.
	LLTextEditor *editor = getChild<LLTextEditor>("tos_text");
	editor->setVisible(FALSE);

	LLWebBrowserCtrl* web_browser = getChild<LLWebBrowserCtrl>("tos_html");
	if ( web_browser )
	{
		// start to observe it so we see navigate complete events
		web_browser->addObserver( this );

		gResponsePtr = LLIamHereTOS::build( this );
		LLHTTPClient::head( getString( "real_url" ), gResponsePtr );
	}

	return TRUE;
}