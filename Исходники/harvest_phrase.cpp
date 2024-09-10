//-----------------------------------------------
// CHarvestPhrase validate
//-----------------------------------------------
bool CHarvestPhrase::validate()
{
	H_AUTO(CHarvestPhrase_validate);
	
	_BeingProcessed = true;

	// entities cant harvest if in combat
	TDataSetRow entityRowId = CPhraseManager::getInstance().getEntityEngagedMeleeBy( _ActorRowId );
	if (TheDataset.isAccessible(entityRowId))
	{
		///\todo david : send message
		_BeingProcessed = false;
		return false;
	}
	entityRowId = CPhraseManager::getInstance().getEntityEngagedRangeBy( _ActorRowId );
	if (TheDataset.isAccessible(entityRowId))
	{
		///\todo david : send message
		_BeingProcessed = false;
		return false;
	}
	
	CCharacter * player = PlayerManager.getChar(_ActorRowId);
	if (!player)
	{
		_BeingProcessed = false;
		return false;
	}

	const sint32 hp = player->currentHp();
	if ( hp < _HPCost  )
	{
		///\todo david : send message
		_BeingProcessed = false;
		return false;
	}
	const sint32 sta = player->getScores()._PhysicalScores[ SCORES::stamina ].Current;
	if ( sta < _StaminaCost  )
	{
		///\todo david : send message
		_BeingProcessed = false;
		return false;
	}
	if (hp <= 0	|| player->isDead())
	{
		///\todo david : send message
		_BeingProcessed = false;
		return false;
	}	

	/// todo david : test if on mount

	// on first validate, get the harvested item and check it's validity
	if ( state() == Evaluated)
	{
	// TEMPORARY CHANGE THIS WHEN THE BRICK WILL HAVE THE RIGHT PARAMS-------
		if (_RootSheetId == CSheetId("bhf01.sbrick"))
		{
			// this is the forage action
			// end harvest but doesn't close the interface
			/*player->endHarvest(false);

			// begin harvest
			player->staticActionInProgress( true );
			player->harvestDeposit(true);	
			player->depositSearchSkill(SKILLS::SH);
			player->openHarvest();
			player->tempInventoryMode(TEMP_INV_MODE::HarvestDeposit);
			CZoneManager::getInstance().harvestDeposit(player);

			if (player->getHarvestInfos().Sheet != CSheetId::Unknown)
			{
				//player->harvestAsked(0);
				_Deposit = true;
				_RawMaterialId = player->getHarvestInfos().Sheet;
				_MinQuality = player->getHarvestInfos().MinQuality;
				_MaxQuality = player->getHarvestInfos().MaxQuality;
				_Quantity = player->getHarvestInfos().Quantity;
				player->harvestedMpQuantity((uint8)_Quantity);	
			}
			else
			{
				player->sendMessageToClient( player->getId(), "WOS_HARVEST_FOUND_NOTHING");
				player->sendCloseTempInventoryImpulsion();
				player->getHarvestInfos().Sheet = CSheetId::Unknown;
				player->endHarvest();
				_BeingProcessed = false;
				return false;
			}*/
		}
	// TEMPORARY ---------------------------------------------
		const CStaticItem *item = CSheets::getForm(_RawMaterialId);
		if (item != 0)
		{
			CCharacter::sendDynamicSystemMessage(player->getId(), "WOS_HARVEST_SEARCHING");
/*				string msgName = "WOS_HARVEST_SEARCHING";
			CMessage msg("STATIC_STRING");
			msg.serial( const_cast<CEntityId&> (player->getId()) );
			set<CEntityId> excluded;
			msg.serialCont( excluded );
			msg.serial( msgName );
			sendMessageViaMirror ("IOS", msg);
*/			}
		else
		{
			nlwarning("HARVEST : Cannot find form for raw material %s, cancel harvest", _RawMaterialId.toString().c_str());
			CCharacter::sendDynamicSystemMessage(player->getId(), "WOS_HARVEST_FOUND_NOTHING");
//				player->sendMessageToClient( player->getId(), "WOS_HARVEST_FOUND_NOTHING");
			player->sendCloseTempInventoryImpulsion();
			player->getHarvestInfos().Sheet = CSheetId::Unknown;
			player->endHarvest();
			_BeingProcessed = false;
			return false;
		}
	}

	return true;
}// CHarvestPhrase validate