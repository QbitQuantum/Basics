bool TalkAction::sellHouse(Player* player, const std::string& words, const std::string& param)
{
	if (!player)
	{
		return false;
	}

	House* house = Houses::getInstance().getHouseByPlayerId(player->getGUID());

	if (!house)
	{
		player->sendCancel("You do not own any house.");
		return false;
	}

	if (!Houses::getInstance().payRent(player, house))
	{
		player->sendCancel("You have to pay the rent before selling your house and you do not have enough money.");
		return false;
	}

	Player* tradePartner = g_game.getPlayerByName(param);

	if (!(tradePartner && tradePartner != player))
	{
		player->sendCancel("Trade player not found.");
		return false;
	}

	if (!tradePartner->isPremium() && g_config.getNumber(ConfigManager::HOUSE_ONLY_PREMIUM))
	{
		player->sendCancel("Trade player doesn't have a premium account.");
		return false;
	}

	if (tradePartner->getPlayerInfo(PLAYERINFO_LEVEL) < g_config.getNumber(ConfigManager::HOUSE_LEVEL))
	{
		player->sendCancel("Trade player level is too low.");
		return false;
	}

	if (Houses::getInstance().getHouseByPlayerId(tradePartner->getGUID()))
	{
		player->sendCancel("Trade player already owns a house.");
		return false;
	}

	if (!Position::areInRange<2, 2, 0>(tradePartner->getPosition(), player->getPosition()))
	{
		player->sendCancel("Trade player is too far away.");
		return false;
	}

	Item* transferItem = house->getTransferItem();

	if (!transferItem)
	{
		player->sendCancel("You can not trade this house.");
		return false;
	}

	transferItem->getParent()->setParent(player);

	if (g_game.internalStartTrade(player, tradePartner, transferItem))
	{
		return true;
	}
	else
	{
		house->resetTransferItem();
	}

	return false;
}