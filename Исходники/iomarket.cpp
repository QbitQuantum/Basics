uint32_t IOMarket::getOfferIdByCounter(uint32_t timestamp, uint16_t counter)
{
	Database* db = Database::getInstance();
	DBQuery query;
	query << "SELECT `id` FROM `market_offers` WHERE `created` = " << (timestamp - g_config.getNumber(ConfigManager::MARKET_OFFER_DURATION))
		<< " AND (`id` & 65535) = " << counter << " AND `world_id` = " << g_config.getNumber(ConfigManager::WORLD_ID) << " LIMIT 1;";
	
	DBResult* result;
	if(!(result = db->storeQuery(query.str())))
		return 0;

	uint32_t tmp = result->getDataInt("id");
	result->free();
	return tmp;
}