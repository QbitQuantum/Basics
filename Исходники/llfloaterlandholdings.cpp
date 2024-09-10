// static
void LLFloaterLandHoldings::processPlacesReply(LLMessageSystem* msg, void**)
{
	LLFloaterLandHoldings* self = sInstance;

	// Is this packet from an old, closed window?
	if (!self)
	{
		return;
	}

	LLCtrlListInterface *list = self->childGetListInterface("parcel list");
	if (!list) return;

	// If this is the first packet, clear out the "loading..." indicator
	if (!self->mFirstPacketReceived)
	{
		self->mFirstPacketReceived = TRUE;
		list->operateOnAll(LLCtrlSelectionInterface::OP_DELETE);
	}

	LLUUID	owner_id;
	std::string	name;
	std::string	desc;
	S32		actual_area;
	S32		billable_area;
	U8		flags;
	F32		global_x;
	F32		global_y;
	std::string	sim_name;
	std::string land_sku;
	std::string land_type;
	
	S32 i;
	S32 count = msg->getNumberOfBlocks("QueryData");
	for (i = 0; i < count; i++)
	{
		msg->getUUID("QueryData", "OwnerID", owner_id, i);
		msg->getString("QueryData", "Name", name, i);
		msg->getString("QueryData", "Desc", desc, i);
		msg->getS32("QueryData", "ActualArea", actual_area, i);
		msg->getS32("QueryData", "BillableArea", billable_area, i);
		msg->getU8("QueryData", "Flags", flags, i);
		msg->getF32("QueryData", "GlobalX", global_x, i);
		msg->getF32("QueryData", "GlobalY", global_y, i);
		msg->getString("QueryData", "SimName", sim_name, i);

		if ( msg->getSizeFast(_PREHASH_QueryData, i, _PREHASH_ProductSKU) > 0 )
		{
			msg->getStringFast(	_PREHASH_QueryData, _PREHASH_ProductSKU, land_sku, i);
			llinfos << "Land sku: " << land_sku << llendl;
			land_type = LLProductInfoRequestManager::instance().getDescriptionForSku(land_sku);
		}
		else
		{
			land_sku.clear();
			land_type = LLTrans::getString("land_type_unknown");
		}
		
		self->mActualArea += actual_area;
		self->mBillableArea += billable_area;

		S32 region_x = llround(global_x) % REGION_WIDTH_UNITS;
		S32 region_y = llround(global_y) % REGION_WIDTH_UNITS;

		std::string location;
		location = llformat("%s (%d, %d)", sim_name.c_str(), region_x, region_y);

		std::string area;
		if(billable_area == actual_area)
		{
			area = llformat("%d", billable_area);
		}
		else
		{
			area = llformat("%d / %d", billable_area, actual_area);
		}
		
		std::string hidden;
		hidden = llformat("%f %f", global_x, global_y);

		LLSD element;
		element["columns"][0]["column"] = "name";
		element["columns"][0]["value"] = name;
		element["columns"][0]["font"] = "SANSSERIF";
		
		element["columns"][1]["column"] = "location";
		element["columns"][1]["value"] = location;
		element["columns"][1]["font"] = "SANSSERIF";
		
		element["columns"][2]["column"] = "area";
		element["columns"][2]["value"] = area;
		element["columns"][2]["font"] = "SANSSERIF";
		
		element["columns"][3]["column"] = "type";
		element["columns"][3]["value"] = land_type;
		element["columns"][3]["font"] = "SANSSERIF";
		
		// hidden is always last column
		element["columns"][4]["column"] = "hidden";
		element["columns"][4]["value"] = hidden;

		list->addElement(element);
	}
	
	self->refreshAggregates();
}