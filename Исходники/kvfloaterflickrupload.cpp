void KVFloaterFlickrUpload::uploadSnapshot()
{
	mTitle = childGetValue("title_form").asString();
	LLSD params;
	params["title"] = childGetValue("title_form");
	params["safety_level"] = childGetValue("rating_combo");
	std::string tags = childGetValue("tags_form");
	std::string description = childGetValue("description_form");
	if(childGetValue("show_position_check").asBoolean())
	{
		// Work out where this was taken.
		LLVector3d clamped_global = LLWorld::getInstance()->clipToVisibleRegions(gAgent.getPositionGlobal(), mPosTakenGlobal);
		LLViewerRegion* region = LLWorld::getInstance()->getRegionFromPosGlobal(clamped_global);
		if(!region)
		{
			// Clamping failed? Shouldn't happen.
			// Use the agent's position instead; if the region the agent is in doesn't exist we have some serious issues,
			// and crashing is an entirely reasonable thing to do.
			region = gAgent.getRegion();
			clamped_global = gAgent.getPositionGlobal();
		}
		std::string region_name = region->getName();
		LLVector3 region_pos = region->getPosRegionFromGlobal(clamped_global);
		std::ostringstream region_tags;
		region_tags << " \"secondlife:region=" << region_name << "\"";
		region_tags << " secondlife:x=" << llround(region_pos[VX]);
		region_tags << " secondlife:y=" << llround(region_pos[VY]);
		region_tags << " secondlife:z=" << llround(region_pos[VZ]);

		// Now let's give some precise camera values.
		region_tags << " secondlife:camera_pos_x=" << (mPosTakenGlobal[VX] - region->getOriginGlobal()[VX]);
		region_tags << " secondlife:camera_pos_y=" << (mPosTakenGlobal[VY] - region->getOriginGlobal()[VY]);
		region_tags << " secondlife:camera_pos_z=" << mPosTakenGlobal[VZ];
		tags += region_tags.str();

		// Include an SLurl in the description, too (maybe).
		if(gSavedSettings.getBOOL("KittyFlickrIncludeSLURL"))
		{
			LLSLURL url(region_name, region_pos);
			std::ostringstream region_desc;
			region_desc << "<em><a href='" << url.getSLURLString() << "'>";
			region_desc << "Taken at " << region_name << " (";
			region_desc << llround(region_pos[VX]) << ", ";
			region_desc << llround(region_pos[VY]) << ", ";
			region_desc << llround(region_pos[VZ]) << ")";
			region_desc << "</a></em>";
			if(description != "")
			{
				description += "\n\n";
			}
			description += region_desc.str();
		}
	}
	params["tags"] = tags;
	params["description"] = description;
	LL_INFOS("FlickrAPI") << "Uploading snapshot with metadata: " << params << LL_ENDL;

	params["auth_token"] = gSavedPerAccountSettings.getLLSD("KittyFlickrToken");
	LLUploadDialog::modalUploadDialog(getString("uploading"));
	KVFlickrRequest::uploadPhoto(params, mCompressedImage, boost::bind(&KVFloaterFlickrUpload::imageUploaded, this, _1, _2));
}