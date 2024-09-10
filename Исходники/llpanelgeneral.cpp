BOOL LLPanelGeneral::postBuild()
{
	LLComboBox* fade_out_combobox = getChild<LLComboBox>("fade_out_combobox");
	fade_out_combobox->setCurrentByIndex(gSavedSettings.getS32("RenderName"));

	LLComboBox* combo = getChild<LLComboBox>("default_location_combo");
	childSetCommitCallback("default_location_combo", onLocationChanged, this);
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

	childSetValue("show_location_checkbox", gSavedSettings.getBOOL("ShowStartLocation"));
	childSetValue("show_all_title_checkbox", gSavedSettings.getBOOL("RenderHideGroupTitleAll"));
	childSetValue("show_my_name_checkbox", gSavedSettings.getBOOL("RenderNameHideSelf"));
	childSetValue("large_avatar_names_checkbox", !gSavedSettings.getBOOL("SmallAvatarNames"));
	childSetValue("highlight_friends_checkbox", gSavedSettings.getBOOL("HighlightFriends"));
	//childSetValue("show_my_title_checkbox", gSavedSettings.getBOOL("RenderHideGroupTitle")); -- MC

	childSetEnabled("afk_timeout_spinner", gSavedSettings.getBOOL("AllowIdleAFK"));
	childSetValue("afk_timeout_spinner", llround(gSavedSettings.getF32("AFKTimeout") / 60)); // User enters minutes, we store as seconds -- MC
	childSetValue("afk_timeout_checkbox", gSavedSettings.getBOOL("AllowIdleAFK"));
	childSetCommitCallback("afk_timeout_checkbox", onCommitAFKCheckbox, this);

	childSetValue("mini_map_notify_chat", gSavedSettings.getBOOL("MiniMapNotifyChatRange"));
	childSetValue("mini_map_notify_sim", gSavedSettings.getBOOL("MiniMapNotifySimRange"));

// 	mDisplayNamesUsage =  gSavedSettings.getU32("DisplayNamesUsage");
// 	mLegacyNamesForFriends =  gSavedSettings.getBOOL("LegacyNamesForFriends");

	LLComboBox* time_combobox = getChild<LLComboBox>("time_combobox");
	time_combobox->setCurrentByIndex(gSavedSettings.getU32("TimeFormat"));
	
	childSetValue("language_combobox", 	gSavedSettings.getString("Language"));
	
	// if we have no agent, we can't let them choose anything
	// if we have an agent, then we only let them choose if they have a choice
	bool can_choose = gAgent.getID().notNull() &&
					 (gAgent.isMature() || gAgent.isGodlike());
	
	if (can_choose)
	{
		// if they're not adult or a god, they shouldn't see the adult selection, so delete it
		if (!gAgent.isAdult() && !gAgent.isGodlike())
		{
			LLComboBox* maturity_combo = getChild<LLComboBox>("maturity_desired_combobox");
			// we're going to remove the adult entry from the combo. This obviously depends
			// on the order of items in the XML file, but there doesn't seem to be a reasonable
			// way to depend on the field in XML called 'name'.
			maturity_combo->remove(0);
		}
	}
	
	U32 preferred_maturity = gSavedSettings.getU32("PreferredMaturity");
	childSetValue("maturity_desired_combobox", int(preferred_maturity));
	std::string selected_item_label = getChild<LLComboBox>("maturity_desired_combobox")->getSelectedItemLabel();
	childSetValue("maturity_desired_textbox", selected_item_label);
	
	childSetVisible("maturity_desired_combobox", can_choose);
	childSetVisible("maturity_desired_textbox",	!can_choose);

	childSetAction("grid_btn", onClickGrid, this);
			
	return TRUE;
}