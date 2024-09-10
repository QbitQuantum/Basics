void LLFloaterMessageLog::conditionalLog(LogPayload entry)
{	
	if(!mMessageLogFilterApply)
		childSetText("log_status_text", llformat("Showing %d messages of %d", mFloaterMessageLogItems.size(), mMessagesLogged));

	FloaterMessageItem item = new LLEasyMessageLogEntry(entry, mEasyMessageReader);


	std::set<std::string>::const_iterator end_msg_name = item->mNames.end();
	std::set<std::string>::iterator iter_msg_name = item->mNames.begin();

	bool have_positive = false;

	for(; iter_msg_name != end_msg_name; ++iter_msg_name)
	{
		std::string find_name = *iter_msg_name;
		LLStringUtil::toLower(find_name);

		//keep the message if we allowed its name so long as one of its other names hasn't been blacklisted
		if(!have_positive && !mMessageLogFilter.mPositiveNames.empty())
		{
			if(std::find(mMessageLogFilter.mPositiveNames.begin(), mMessageLogFilter.mPositiveNames.end(), find_name) != mMessageLogFilter.mPositiveNames.end())
				have_positive = true;
		}
		if(!mMessageLogFilter.mNegativeNames.empty())
		{
			if(std::find(mMessageLogFilter.mNegativeNames.begin(), mMessageLogFilter.mNegativeNames.end(), find_name) != mMessageLogFilter.mNegativeNames.end())
			{
				delete item;
			return;
			}
		}
		//we don't have any negative filters and we have a positive match
		else if(have_positive)
			break;
	}

	//we had a positive filter but no positive matches
	if(!mMessageLogFilter.mPositiveNames.empty() && !have_positive)
	{
		delete item;
		return;
	}

	mFloaterMessageLogItems.push_back(item); // moved from beginning...

	if(item->mType == LLEasyMessageLogEntry::HTTP_REQUEST)
	{
		mIncompleteHTTPConvos.insert(HTTPConvoMap::value_type(item->mRequestID, item));
	}

	std::string net_name("\?\?\?");
	BOOL outgoing = item->isOutgoing();
	switch(item->mType)
	{
	case LLEasyMessageLogEntry::TEMPLATE:
		{
			LLHost find_host = outgoing ? item->mToHost : item->mFromHost;
			net_name = find_host.getIPandPort();
			std::list<LLNetListItem*>::iterator end = sNetListItems.end();
			for(std::list<LLNetListItem*>::iterator iter = sNetListItems.begin(); iter != end; ++iter)
			{
				if((*iter)->mCircuitData->getHost() == find_host)
				{
					net_name = (*iter)->mName;
					break;
				}
			}
		}
		break;
	case LLEasyMessageLogEntry::HTTP_REQUEST:
		{
			std::string url = get_base_url(item->mURL);
			std::list<LLNetListItem*>::iterator end = sNetListItems.end();
			for(std::list<LLNetListItem*>::iterator iter = sNetListItems.begin(); iter != end; ++iter)
			{
				LLViewerRegion* regionp = LLWorld::getInstance()->getRegionFromHandle((*iter)->mHandle); //TODO: Find a better way to do this.
				if(regionp && regionp->getCapURLNames(url).size())
				{
					net_name = (*iter)->mName;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
	//add the message to the messagelog scroller
	LLSD element;
	element["id"] = item->mID;
	LLSD& sequence_column = element["columns"][0];
	sequence_column["column"] = "sequence";
	sequence_column["value"] = llformat("%u", item->mSequenceID);

	LLSD& type_column = element["columns"][1];
	type_column["column"] = "type";
	switch(item->mType)
	{
	case LLEasyMessageLogEntry::TEMPLATE:
		type_column["value"] = "UDP";
		break;
	case LLEasyMessageLogEntry::HTTP_REQUEST:
		type_column["value"] = "HTTP";
		break;
	default:
		type_column["value"] = "\?\?\?";
	}

	LLSD& direction_column = element["columns"][2];
	direction_column["column"] = "direction";
	if(item->mType == LLEasyMessageLogEntry::TEMPLATE)
		direction_column["value"] = outgoing ? "to" : "from";
	else if(item->mType == LLEasyMessageLogEntry::HTTP_REQUEST)
		direction_column["value"] = "both";

	LLSD& net_column = element["columns"][3];
	net_column["column"] = "net";
	net_column["value"] = net_name;

	LLSD& name_column = element["columns"][4];
	name_column["column"] = "name";
	name_column["value"] = item->getName();

	LLSD& summary_column = element["columns"][5];
	summary_column["column"] = "summary";
	summary_column["value"] = item->mSummary;
	LLScrollListCtrl* scrollp = getChild<LLScrollListCtrl>("message_log");

	S32 scroll_pos = scrollp->getScrollPos();
	scrollp->addElement(element, ADD_BOTTOM);

	if(scroll_pos > scrollp->getItemCount() - scrollp->getPageLines() - 4)
		scrollp->setScrollPos(scrollp->getItemCount());
}