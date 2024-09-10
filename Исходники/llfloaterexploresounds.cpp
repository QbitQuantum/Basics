// static
BOOL LLFloaterExploreSounds::tick()
{
	//if(childGetValue("pause_chk").asBoolean()) return FALSE;

	bool show_collision_sounds = childGetValue("collision_chk").asBoolean();
	bool show_repeated_assets = childGetValue("repeated_asset_chk").asBoolean();
	bool show_avatars = childGetValue("avatars_chk").asBoolean();
	bool show_objects = childGetValue("objects_chk").asBoolean();

	std::list<LLSoundHistoryItem> history;
	if(childGetValue("pause_chk").asBoolean())
	{
		history = mLastHistory;
	}
	else
	{
		std::map<LLUUID, LLSoundHistoryItem>::iterator map_iter = gSoundHistory.begin();
		std::map<LLUUID, LLSoundHistoryItem>::iterator map_end = gSoundHistory.end();
		for( ; map_iter != map_end; ++map_iter)
		{
			history.push_back((*map_iter).second);
		}
		LLSoundHistoryItemCompare c;
		history.sort(c);
		mLastHistory = history;
	}

	LLScrollListCtrl* list = getChild<LLScrollListCtrl>("sound_list");

	// Save scroll pos and selection so they can be restored
	S32 scroll_pos = list->getScrollPos();
	LLDynamicArray<LLUUID> selected_ids;
	std::vector<LLScrollListItem*> selected_items = list->getAllSelected();
	std::vector<LLScrollListItem*>::iterator selection_iter = selected_items.begin();
	std::vector<LLScrollListItem*>::iterator selection_end = selected_items.end();
	for(; selection_iter != selection_end; ++selection_iter)
		selected_ids.push_back((*selection_iter)->getUUID());

	list->clearRows();

	std::list<LLUUID> unique_asset_list;

	std::list<LLSoundHistoryItem>::iterator iter = history.begin();
	std::list<LLSoundHistoryItem>::iterator end = history.end();
	for( ; iter != end; ++iter)
	{
		LLSoundHistoryItem item = (*iter);

		bool is_avatar = item.mOwnerID == item.mSourceID;
		if(is_avatar && !show_avatars) continue;

		bool is_object = !is_avatar;
		if(is_object && !show_objects) continue;

		bool is_repeated_asset = std::find(unique_asset_list.begin(), unique_asset_list.end(), item.mAssetID) != unique_asset_list.end();
		if(is_repeated_asset && !show_repeated_assets) continue;

		if(!item.mReviewed)
		{
			item.mReviewedCollision	= std::find(&collision_sounds[0], &collision_sounds[num_collision_sounds], item.mAssetID) != &collision_sounds[num_collision_sounds];
			item.mReviewed = true;
		}
		bool is_collision_sound = item.mReviewedCollision;
		if(is_collision_sound && !show_collision_sounds) continue;

		unique_asset_list.push_back(item.mAssetID);

		LLSD element;
		element["id"] = item.mID;

		LLSD& playing_column = element["columns"][0];
		playing_column["column"] = "playing";
		if(item.mPlaying)
			playing_column["value"] = " Playing";
		else
			playing_column["value"] = llformat("%.1f min ago", (LLTimer::getElapsedSeconds() - item.mTimeStopped) / 60.f);

		LLSD& type_column = element["columns"][1];
		type_column["column"] = "type";
		if(item.mType == LLAudioEngine::AUDIO_TYPE_UI)
		{
			// this shouldn't happen for now, as UI is forbidden in the log
			type_column["value"] = "UI";
		}
		else
		{
			std::string type;

			if(is_avatar)
			{
				type = "Avatar";
			}
			else
			{
				if(item.mIsTrigger)
				{
					type = "llTriggerSound";
				}
				else
				{
					if(item.mIsLooped)
						type = "llLoopSound";
					else
						type = "llPlaySound";
				}
			}

			type_column["value"] = type;
		}

		LLSD& owner_column = element["columns"][2];
		owner_column["column"] = "owner";
		std::string fullname;
		BOOL is_group;
		if(gCacheName->getIfThere(item.mOwnerID, fullname, is_group))
		{
			if(is_group) fullname += " (Group)";
			owner_column["value"] = fullname;
		}
		else
			owner_column["value"] = item.mOwnerID.asString();

		LLSD& sound_column = element["columns"][3];
		sound_column["column"] = "sound";

		if (item.mOwnerID == gAgent.getID())
			sound_column["value"] = item.mAssetID.asString();
		else
			sound_column["value"] = LLUUID::null.asString();

		list->addElement(element, ADD_BOTTOM);
	}

	list->selectMultiple(selected_ids);
	list->setScrollPos(scroll_pos);

	return FALSE;
}