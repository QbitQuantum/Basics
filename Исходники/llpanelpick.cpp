//static
void LLPanelPick::processPickInfoReply(LLMessageSystem *msg, void **)
{
    // Extract the agent id and verify the message is for this
    // client.
    LLUUID agent_id;
    msg->getUUID("AgentData", "AgentID", agent_id );
    if (agent_id != gAgent.getID())
    {
        llwarns << "Agent ID mismatch in processPickInfoReply"
            << llendl;
		return;
    }

    LLUUID pick_id;
    msg->getUUID("Data", "PickID", pick_id);

    LLUUID creator_id;
    msg->getUUID("Data", "CreatorID", creator_id);

	BOOL top_pick;
	msg->getBOOL("Data", "TopPick", top_pick);

    LLUUID parcel_id;
    msg->getUUID("Data", "ParcelID", parcel_id);

	std::string name;
	msg->getString("Data", "Name", name);

	std::string desc;
	msg->getString("Data", "Desc", desc);

	LLUUID snapshot_id;
	msg->getUUID("Data", "SnapshotID", snapshot_id);

    // "Location text" is actually the owner name, the original
    // name that owner gave the parcel, and the location.
	std::string location_text;
    msg->getString("Data", "User", location_text);
    location_text.append(", ");

	std::string original_name;
    msg->getString("Data", "OriginalName", original_name);
	if (!original_name.empty())
	{
		location_text.append(original_name);
		location_text.append(", ");
	}

	std::string sim_name;
	msg->getString("Data", "SimName", sim_name);
	location_text.append(sim_name);
	location_text.append(" ");

	//Fix for location text importing - RK
	for (panel_list_t::iterator iter = sAllPanels.begin(); iter != sAllPanels.end(); ++iter)
	{
		LLPanelPick* self = *iter;
		if(!self->mImporting)	self->mLocationText = location_text;
		else location_text = self->mLocationText;
		self->mImporting = false;
	}

	LLVector3d pos_global;
	msg->getVector3d("Data", "PosGlobal", pos_global);

    S32 region_x = llround((F32)pos_global.mdV[VX]) % REGION_WIDTH_UNITS;
    S32 region_y = llround((F32)pos_global.mdV[VY]) % REGION_WIDTH_UNITS;
	S32 region_z = llround((F32)pos_global.mdV[VZ]);
   
    location_text.append(llformat("(%d, %d, %d)", region_x, region_y, region_z));

	S32 sort_order;
    msg->getS32("Data", "SortOrder", sort_order);

	BOOL enabled;
	msg->getBOOL("Data", "Enabled", enabled);

    // Look up the panel to fill in
	for (panel_list_t::iterator iter = sAllPanels.begin(); iter != sAllPanels.end(); ++iter)
	{
		LLPanelPick* self = *iter;
		// For top picks, must match pick id
		if (self->mPickID != pick_id)
		{
			continue;
		}

		self->mDataReceived = TRUE;

        // Found the panel, now fill in the information
		self->mPickID = pick_id;
		self->mCreatorID = creator_id;
		self->mParcelID = parcel_id;
		self->mSimName.assign(sim_name);
		self->mPosGlobal = pos_global;

		// Update UI controls
        self->mNameEditor->setText(std::string(name));
        self->mDescEditor->setText(std::string(desc));
        self->mSnapshotCtrl->setImageAssetID(snapshot_id);
        self->mLocationEditor->setText(location_text);
        self->mEnabledCheck->set(enabled);

		self->mSortOrderEditor->setText(llformat("%d", sort_order));
    }
}