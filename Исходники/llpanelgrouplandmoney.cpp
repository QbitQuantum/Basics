//static
void LLPanelGroupLandMoney::impl::processGroupLand(LLMessageSystem* msg)
{
	S32 count = msg->getNumberOfBlocks("QueryData");
	if(count > 0)
	{
		S32 first_block = 0;

		LLUUID owner_id;
		LLUUID trans_id;

		msg->getUUID("QueryData", "OwnerID", owner_id, 0);
		msg->getUUID("TransactionData", "TransactionID", trans_id);

		if(owner_id.isNull())
		{
			// special block which has total contribution
			++first_block;
			
			S32 total_contribution;
			msg->getS32("QueryData", "ActualArea", total_contribution, 0);
			mPanel.getChild<LLUICtrl>("total_contributed_land_value")->setTextArg("[AREA]", llformat("%d", total_contribution));

			S32 committed;
			msg->getS32("QueryData", "BillableArea", committed, 0);
			mPanel.getChild<LLUICtrl>("total_land_in_use_value")->setTextArg("[AREA]", llformat("%d", committed));
			
			S32 available = total_contribution - committed;
			mPanel.getChild<LLUICtrl>("land_available_value")->setTextArg("[AREA]", llformat("%d", available));

			if ( mGroupOverLimitTextp && mGroupOverLimitIconp )
			{
				mGroupOverLimitIconp->setVisible(available < 0);
				mGroupOverLimitTextp->setVisible(available < 0);
			}
		}

		if ( trans_id != mTransID ) return;
		// This power was removed to make group roles simpler
		//if ( !gAgent.hasPowerInGroup(mGroupID, GP_LAND_VIEW_OWNED) ) return;
		if (!gAgent.isInGroup(mPanel.mGroupID)) return;
		mGroupParcelsp->setCommentText(mEmptyParcelsText);

		std::string name;
		std::string desc;
		S32 actual_area;
		S32 billable_area;
		U8 flags;
		F32 global_x;
		F32 global_y;
		std::string sim_name;
		std::string land_sku;
		std::string land_type;
		
		for(S32 i = first_block; i < count; ++i)
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

			S32 region_x = llround(global_x) % REGION_WIDTH_UNITS;
			S32 region_y = llround(global_y) % REGION_WIDTH_UNITS;
			std::string location = sim_name + llformat(" (%d, %d)", region_x, region_y);
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

			LLSD row;

			row["columns"][0]["column"] = "name";
			row["columns"][0]["value"] = name;
			row["columns"][0]["font"] = "SANSSERIF_SMALL";

			row["columns"][1]["column"] = "location";
			row["columns"][1]["value"] = location;
			row["columns"][1]["font"] = "SANSSERIF_SMALL";
			
			row["columns"][2]["column"] = "area";
			row["columns"][2]["value"] = area;
			row["columns"][2]["font"] = "SANSSERIF_SMALL";
			
			row["columns"][3]["column"] = "type";
			row["columns"][3]["value"] = land_type;
			row["columns"][3]["font"] = "SANSSERIF_SMALL";
			
			// hidden is always last column
			row["columns"][4]["column"] = "hidden";
			row["columns"][4]["value"] = hidden;
			
			mGroupParcelsp->addElement(row);
		}
	}
}