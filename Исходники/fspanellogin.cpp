void FSPanelLogin::addFavoritesToStartLocation()
{
	mShowFavorites = false;
	// Clear the combo.
	LLComboBox* combo = getChild<LLComboBox>("start_location_combo");
	if (!combo) return;
	int num_items = combo->getItemCount();
	for (int i = num_items - 1; i > 2; i--)
	{
		combo->remove(i);
	}

	// Load favorites into the combo.
	std::string user_defined_name = getChild<LLComboBox>("username_combo")->getSimple();
	std::string canonical_user_name = canonicalize_username(user_defined_name);
	U32 resident_pos = canonical_user_name.find("Resident");
	if (resident_pos > 0)
	{
		canonical_user_name = canonical_user_name.substr(0, resident_pos - 1);
	}
	std::string current_grid = getChild<LLComboBox>("server_combo")->getSimple();
	std::string current_user = canonical_user_name + " @ " + current_grid;
	LL_DEBUGS("Favorites") << "Current user: \"" << current_user << "\"" << LL_ENDL;
	std::string filename = gDirUtilp->getExpandedFilename(LL_PATH_USER_SETTINGS, "stored_favorites.xml");

	LLSD fav_llsd;
	llifstream file;
	file.open(filename.c_str());
	if (!file.is_open())
	{
		return;
	}
	LLSDSerialize::fromXML(fav_llsd, file);
	for (LLSD::map_const_iterator iter = fav_llsd.beginMap();
		iter != fav_llsd.endMap(); ++iter)
	{
		// The account name in stored_favorites.xml has Resident last name even if user has
		// a single word account name, so it can be compared case-insensitive with the
		// user defined "firstname lastname".
		S32 res = LLStringUtil::compareInsensitive(current_user, iter->first);
		if (res != 0)
		{
			LL_DEBUGS() << "Skipping favorites for " << iter->first << LL_ENDL;
			continue;
		}

		combo->addSeparator();
		LL_DEBUGS() << "Loading favorites for " << iter->first << LL_ENDL;
		LLSD user_llsd = iter->second;
		for (LLSD::array_const_iterator iter1 = user_llsd.beginArray();
			iter1 != user_llsd.endArray(); ++iter1)
		{
			std::string label = (*iter1)["name"].asString();
			std::string value = (*iter1)["slurl"].asString();
			if(label != "" && value != "")
			{
				mShowFavorites = true;
				combo->add(label, value);
			}
		}
		break;
	}

	LLFloaterPreference::updateShowFavoritesCheckbox(mShowFavorites);
}