void LLChatHistory::appendMessage(const LLChat& chat, const LLSD &args, const LLStyle::Params& input_append_params)
{
	bool use_plain_text_chat_history = args["use_plain_text_chat_history"].asBoolean();

	llassert(mEditor);
	if (!mEditor)
	{
		return;
	}

	mEditor->setPlainText(use_plain_text_chat_history);

	if (!mEditor->scrolledToEnd() && chat.mFromID != gAgent.getID() && !chat.mFromName.empty())
	{
		mUnreadChatSources.insert(chat.mFromName);
		mMoreChatPanel->setVisible(TRUE);
		std::string chatters;
		for (unread_chat_source_t::iterator it = mUnreadChatSources.begin();
			it != mUnreadChatSources.end();)
		{
			chatters += *it;
			if (++it != mUnreadChatSources.end())
			{
				chatters += ", ";
			}
		}
		LLStringUtil::format_map_t args;
		args["SOURCES"] = chatters;

		if (mUnreadChatSources.size() == 1)
		{
			mMoreChatText->setValue(LLTrans::getString("unread_chat_single", args));
		}
		else
		{
			mMoreChatText->setValue(LLTrans::getString("unread_chat_multiple", args));
		}
		S32 height = mMoreChatText->getTextPixelHeight() + 5;
		mMoreChatPanel->reshape(mMoreChatPanel->getRect().getWidth(), height);
	}

	LLColor4 txt_color = LLUIColorTable::instance().getColor("White");
	LLViewerChat::getChatColor(chat,txt_color);
	LLFontGL* fontp = LLViewerChat::getChatFont();	
	std::string font_name = LLFontGL::nameFromFont(fontp);
	std::string font_size = LLFontGL::sizeFromFont(fontp);	
	LLStyle::Params style_params;
	style_params.color(txt_color);
	style_params.readonly_color(txt_color);
	style_params.font.name(font_name);
	style_params.font.size(font_size);	
	style_params.font.style(input_append_params.font.style);

	std::string prefix = chat.mText.substr(0, 4);

	//IRC styled /me messages.
	bool irc_me = prefix == "/me " || prefix == "/me'";

	// Delimiter after a name in header copy/past and in plain text mode
	std::string delimiter = ": ";
	std::string shout = LLTrans::getString("shout");
	std::string whisper = LLTrans::getString("whisper");
	if (chat.mChatType == CHAT_TYPE_SHOUT || 
		chat.mChatType == CHAT_TYPE_WHISPER ||
		chat.mText.compare(0, shout.length(), shout) == 0 ||
		chat.mText.compare(0, whisper.length(), whisper) == 0)
	{
		delimiter = " ";
	}

	// Don't add any delimiter after name in irc styled messages
	if (irc_me || chat.mChatStyle == CHAT_STYLE_IRC)
	{
		delimiter = LLStringUtil::null;
		style_params.font.style = "ITALIC";
	}

	bool message_from_log = chat.mChatStyle == CHAT_STYLE_HISTORY;
	// We graying out chat history by graying out messages that contains full date in a time string
	if (message_from_log)
	{
		style_params.color(LLColor4::grey);
		style_params.readonly_color(LLColor4::grey);
	}

	if (use_plain_text_chat_history)
	{
		LLStyle::Params timestamp_style(style_params);
		if (!message_from_log)
		{
			LLColor4 timestamp_color = LLUIColorTable::instance().getColor("ChatTimestampColor");
			timestamp_style.color(timestamp_color);
			timestamp_style.readonly_color(timestamp_color);
		}
		mEditor->appendText("[" + chat.mTimeStr + "] ", mEditor->getText().size() != 0, timestamp_style);

		if (utf8str_trim(chat.mFromName).size() != 0)
		{
			// Don't hotlink any messages from the system (e.g. "Second Life:"), so just add those in plain text.
			if ( chat.mSourceType == CHAT_SOURCE_OBJECT && chat.mFromID.notNull())
			{
				// for object IMs, create a secondlife:///app/objectim SLapp
				std::string url = LLSLURL("objectim", chat.mFromID, "").getSLURLString();
				url += "?name=" + chat.mFromName;
				url += "&owner=" + chat.mOwnerID.asString();

				std::string slurl = args["slurl"].asString();
				if (slurl.empty())
				{
				    LLViewerRegion *region = LLWorld::getInstance()->getRegionFromPosAgent(chat.mPosAgent);
				    if(region)
				      {
					LLSLURL region_slurl(region->getName(), chat.mPosAgent);
					slurl = region_slurl.getLocationString();
				      }
				}
				url += "&slurl=" + LLURI::escape(slurl);

				// set the link for the object name to be the objectim SLapp
				// (don't let object names with hyperlinks override our objectim Url)
				LLStyle::Params link_params(style_params);
				link_params.color.control = "HTMLLinkColor";
				link_params.link_href = url;
				mEditor->appendText("<nolink>" + chat.mFromName + "</nolink>"  + delimiter,
									false, link_params);
			}
			else if ( chat.mFromName != SYSTEM_FROM && chat.mFromID.notNull() && !message_from_log)
			{
				LLStyle::Params link_params(style_params);
				link_params.overwriteFrom(LLStyleMap::instance().lookupAgent(chat.mFromID));
				// Convert the name to a hotlink and add to message.
				mEditor->appendText(chat.mFromName + delimiter, false, link_params);
			}
			else
			{
				mEditor->appendText(chat.mFromName + delimiter, false, style_params);
			}
		}
	}
	else
	{
		LLView* view = NULL;
		LLInlineViewSegment::Params p;
		p.force_newline = true;
		p.left_pad = mLeftWidgetPad;
		p.right_pad = mRightWidgetPad;

		LLDate new_message_time = LLDate::now();

		if (mLastFromName == chat.mFromName 
			&& mLastFromID == chat.mFromID
			&& mLastMessageTime.notNull() 
			&& (new_message_time.secondsSinceEpoch() - mLastMessageTime.secondsSinceEpoch()) < 60.0
			&& mIsLastMessageFromLog == message_from_log)  //distinguish between current and previous chat session's histories
		{
			view = getSeparator();
			p.top_pad = mTopSeparatorPad;
			p.bottom_pad = mBottomSeparatorPad;
		}
		else
		{
			view = getHeader(chat, style_params);
			if (mEditor->getText().size() == 0)
				p.top_pad = 0;
			else
				p.top_pad = mTopHeaderPad;
			p.bottom_pad = mBottomHeaderPad;
			
		}
		p.view = view;

		//Prepare the rect for the view
		LLRect target_rect = mEditor->getDocumentView()->getRect();
		// squeeze down the widget by subtracting padding off left and right
		target_rect.mLeft += mLeftWidgetPad + mEditor->getHPad();
		target_rect.mRight -= mRightWidgetPad;
		view->reshape(target_rect.getWidth(), view->getRect().getHeight());
		view->setOrigin(target_rect.mLeft, view->getRect().mBottom);

		std::string widget_associated_text = "\n[" + chat.mTimeStr + "] ";
		if (utf8str_trim(chat.mFromName).size() != 0 && chat.mFromName != SYSTEM_FROM)
			widget_associated_text += chat.mFromName + delimiter;

		mEditor->appendWidget(p, widget_associated_text, false);
		mLastFromName = chat.mFromName;
		mLastFromID = chat.mFromID;
		mLastMessageTime = new_message_time;
		mIsLastMessageFromLog = message_from_log;
	}

	if (chat.mNotifId.notNull())
	{
		LLNotificationPtr notification = LLNotificationsUtil::find(chat.mNotifId);
		if (notification != NULL)
		{
			LLIMToastNotifyPanel* notify_box = new LLIMToastNotifyPanel(
					notification, chat.mSessionID);
			//we can't set follows in xml since it broke toasts behavior
			notify_box->setFollowsLeft();
			notify_box->setFollowsRight();
			notify_box->setFollowsTop();

			ctrl_list_t ctrls = notify_box->getControlPanel()->getCtrlList();
			S32 offset = 0;
			// Children were added by addChild() which uses push_front to insert them into list,
			// so to get buttons in correct order reverse iterator is used (EXT-5906) 
			for (ctrl_list_t::reverse_iterator it = ctrls.rbegin(); it != ctrls.rend(); it++)
			{
				LLButton * button = dynamic_cast<LLButton*> (*it);
				if (button != NULL)
				{
					button->setOrigin( offset,
							button->getRect().mBottom);
					button->setLeftHPad(2 * HPAD);
					button->setRightHPad(2 * HPAD);
					// set zero width before perform autoResize()
					button->setRect(LLRect(button->getRect().mLeft,
							button->getRect().mTop, button->getRect().mLeft,
							button->getRect().mBottom));
					button->setAutoResize(true);
					button->autoResize();
					offset += HPAD + button->getRect().getWidth();
					button->setFollowsNone();
				}
			}

			LLTextEditor* text_editor = notify_box->getChild<LLTextEditor>("text_editor_box", TRUE);
			S32 text_heigth = 0;
			if(text_editor != NULL)
			{
				text_heigth = text_editor->getTextBoundingRect().getHeight();
			}

			//Prepare the rect for the view
			LLRect target_rect = mEditor->getDocumentView()->getRect();
			// squeeze down the widget by subtracting padding off left and right
			target_rect.mLeft += mLeftWidgetPad + mEditor->getHPad();
			target_rect.mRight -= mRightWidgetPad;
			notify_box->reshape(target_rect.getWidth(),
					notify_box->getRect().getHeight());
			notify_box->setOrigin(target_rect.mLeft, notify_box->getRect().mBottom);

			if (text_editor != NULL)
			{
				S32 text_heigth_delta =
						text_editor->getTextBoundingRect().getHeight()
								- text_heigth;
				notify_box->reshape(target_rect.getWidth(),
								notify_box->getRect().getHeight() + text_heigth_delta);
			}

			LLInlineViewSegment::Params params;
			params.view = notify_box;
			params.left_pad = mLeftWidgetPad;
			params.right_pad = mRightWidgetPad;
			mEditor->appendWidget(params, "\n", false);
		}
	}
	else
	{
		std::string message = irc_me ? chat.mText.substr(3) : chat.mText;


		//MESSAGE TEXT PROCESSING
		//*HACK getting rid of redundant sender names in system notifications sent using sender name (see EXT-5010)
		if (use_plain_text_chat_history && gAgentID != chat.mFromID && chat.mFromID.notNull())
		{
			std::string slurl_about = SLURL_APP_AGENT + chat.mFromID.asString() + SLURL_ABOUT;
			if (message.length() > slurl_about.length() && 
				message.compare(0, slurl_about.length(), slurl_about) == 0)
			{
				message = message.substr(slurl_about.length(), message.length()-1);
			}
		}

		if (irc_me && !use_plain_text_chat_history)
		{
			message = chat.mFromName + message;
		}
		
		mEditor->appendText(message, FALSE, style_params);
	}

	mEditor->blockUndo();

	// automatically scroll to end when receiving chat from myself
	if (chat.mFromID == gAgentID)
	{
		mEditor->setCursorAndScrollToEnd();
	}
}