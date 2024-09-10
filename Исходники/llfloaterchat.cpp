// static
void LLFloaterChat::addChatHistory(const LLChat& chat, bool log_to_file)
{	
	if (log_to_file && (gSavedPerAccountSettings.getBOOL("LogChat"))) 
	{
		if (chat.mChatType != CHAT_TYPE_WHISPER && chat.mChatType != CHAT_TYPE_SHOUT)
		{
			LLLogChat::saveHistory("chat", chat.mFromName, chat.mFromID, chat.mText);
		}
		else
		{
			LLLogChat::saveHistory("chat", "", chat.mFromID, chat.mFromName + " " + chat.mText);
		}
	}
	
	LLColor4 color = get_text_color(chat);
	
	if (!log_to_file) color = LLColor4::grey;	//Recap from log file.

	if (chat.mChatType == CHAT_TYPE_DEBUG_MSG)
	{
		if(gSavedSettings.getBOOL("ShowScriptErrors") == FALSE)
			return;
		if (gSavedSettings.getS32("ShowScriptErrorsLocation") == 1)
		{
			LLFloaterScriptDebug::addScriptLine(chat.mText,
												chat.mFromName, 
												color, 
												chat.mFromID);
			return;
		}
	}
	
	// could flash the chat button in the status bar here. JC
	LLFloaterChat* chat_floater = LLFloaterChat::getInstance();
	LLViewerTextEditor*	history_editor = chat_floater->getChild<LLViewerTextEditor>("Chat History Editor");
	LLViewerTextEditor*	history_editor_with_mute = chat_floater->getChild<LLViewerTextEditor>("Chat History Editor with mute");

	if (!chat.mMuted)
	{
		add_timestamped_line(history_editor, chat, color);
		add_timestamped_line(history_editor_with_mute, chat, color);
	}
	else
	{
		// desaturate muted chat
		LLColor4 muted_color = lerp(color, LLColor4::grey, 0.5f);
		add_timestamped_line(history_editor_with_mute, chat, color);
	}
	
	// add objects as transient speakers that can be muted
	if (chat.mSourceType == CHAT_SOURCE_OBJECT)
	{
		chat_floater->mPanel->setSpeaker(chat.mFromID, chat.mFromName, LLSpeaker::STATUS_NOT_IN_CHANNEL, LLSpeaker::SPEAKER_OBJECT);
	}

	// start tab flashing on incoming text from other users (ignoring system text, etc)
	if (!chat_floater->isInVisibleChain() && chat.mSourceType == CHAT_SOURCE_AGENT)
	{
		LLFloaterChatterBox::getInstance()->setFloaterFlashing(chat_floater, TRUE);
	}
}