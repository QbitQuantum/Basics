void LLFloaterBuyLandUI::updateParcelInfo()
{
	LLParcel* parcel = mParcel->getParcel();
	mParcelValid = parcel && mRegion;
	mParcelIsForSale = false;
	mParcelIsGroupLand = false;
	mParcelGroupContribution = 0;
	mParcelPrice = 0;
	mParcelActualArea = 0;
	mParcelBillableArea = 0;
	mParcelSupportedObjects = 0;
	mParcelSoldWithObjects = false;
	mParcelLocation = "";
	mParcelSnapshot.setNull();
	mParcelSellerName = "";
	
	mCanBuy = false;
	mCannotBuyIsError = false;
	
	if (!mParcelValid)
	{
		mCannotBuyReason = getString("no_land_selected");
		return;
	}
	
	if (mParcel->getMultipleOwners())
	{
		mCannotBuyReason = getString("multiple_parcels_selected");
		return;
	}

	const LLUUID& parcelOwner = parcel->getOwnerID();
	
	mIsClaim = parcel->isPublic();
	if (!mIsClaim)
	{
		mParcelActualArea = parcel->getArea();
		mParcelIsForSale = parcel->getForSale();
		mParcelIsGroupLand = parcel->getIsGroupOwned();
		mParcelPrice = mParcelIsForSale ? parcel->getSalePrice() : 0;
		
		if (mParcelIsGroupLand)
		{
			LLUUID group_id = parcel->getGroupID();
			mParcelGroupContribution = gAgent.getGroupContribution(group_id);
		}
	}
	else
	{
		mParcelActualArea = mParcel->getClaimableArea();
		mParcelIsForSale = true;
		mParcelPrice = mParcelActualArea * parcel->getClaimPricePerMeter();
	}

	mParcelBillableArea =
		llround(mRegion->getBillableFactor() * mParcelActualArea);

 	mParcelSupportedObjects = llround(
		parcel->getMaxPrimCapacity() * parcel->getParcelPrimBonus()); 
 	// Can't have more than region max tasks, regardless of parcel 
 	// object bonus factor. 
 	LLViewerRegion* region = LLViewerParcelMgr::getInstance()->getSelectionRegion(); 
 	if(region) 
 	{ 
		S32 max_tasks_per_region = (S32)region->getMaxTasks(); 
		mParcelSupportedObjects = llmin(
			mParcelSupportedObjects, max_tasks_per_region); 
 	} 

	mParcelSoldWithObjects = parcel->getSellWithObjects();

	
	LLVector3 center = parcel->getCenterpoint();
	mParcelLocation = llformat("%s %d,%d",
				mRegion->getName().c_str(),
				(int)center[VX], (int)center[VY]
				);
	
	mParcelSnapshot = parcel->getSnapshotID();
	
	updateNames();
	
	bool haveEnoughCash = mParcelPrice <= mAgentCashBalance;
	S32 cashBuy = haveEnoughCash ? 0 : (mParcelPrice - mAgentCashBalance);
	mCurrency.setAmount(cashBuy, true);
	mCurrency.setZeroMessage(haveEnoughCash ? getString("none_needed") : LLStringUtil::null);

	// checks that we can buy the land

	if(mIsForGroup && !gAgent.hasPowerInActiveGroup(GP_LAND_DEED))
	{
		mCannotBuyReason = getString("cant_buy_for_group");
		return;
	}

	if (!mIsClaim)
	{
		const LLUUID& authorizedBuyer = parcel->getAuthorizedBuyerID();
		const LLUUID buyer = gAgent.getID();
		const LLUUID newOwner = mIsForGroup ? gAgent.getGroupID() : buyer;

		if (!mParcelIsForSale
			|| (mParcelPrice == 0  &&  authorizedBuyer.isNull()))
		{
			
			mCannotBuyReason = getString("parcel_not_for_sale");
			return;
		}

		if (parcelOwner == newOwner)
		{
			if (mIsForGroup)
			{
				mCannotBuyReason = getString("group_already_owns");
			}
			else
			{
				mCannotBuyReason = getString("you_already_own");
			}
			return;
		}

		if (!authorizedBuyer.isNull() && buyer != authorizedBuyer)
		{
			// Maybe the parcel is set for sale to a group we are in.
			bool authorized_group =
				gAgent.hasPowerInGroup(authorizedBuyer,GP_LAND_DEED)
				&& gAgent.hasPowerInGroup(authorizedBuyer,GP_LAND_SET_SALE_INFO);

			if (!authorized_group)
			{
				mCannotBuyReason = getString("set_to_sell_to_other");
				return;
			}
		}
	}
	else
	{
		if (mParcelActualArea == 0)
		{
			mCannotBuyReason = getString("no_public_land");
			return;
		}

		if (mParcel->hasOthersSelected())
		{
			// Policy: Must not have someone else's land selected
			mCannotBuyReason = getString("not_owned_by_you");
			return;
		}
	}

	mCanBuy = true;
}