bool IOMapSerialize::saveHouseItems(Database* db, House* house)
{
	std::string config = asLowerCaseString(g_config.getString(ConfigManager::HOUSE_STORAGE));
	if(config == "binary-tilebased")
	{
		DBQuery query;
		query << "DELETE FROM `tile_store` WHERE `house_id` = " << house->getId()
			<< " AND `world_id` = " << g_config.getNumber(ConfigManager::WORLD_ID);
		if(!db->query(query.str()))
			return false;

		DBInsert stmt(db);
		stmt.setQuery("INSERT INTO `tile_store` (`house_id`, `world_id`, `data`) VALUES ");
		return saveHouseBinaryTileBased(db, stmt, house) && stmt.execute();
	}
	else if(config == "binary")
	{
		DBQuery query;
		query << "DELETE FROM `house_data` WHERE `house_id` = "<< house->getId()
			<< " AND `world_id` = " << g_config.getNumber(ConfigManager::WORLD_ID);
		if(!db->query(query.str()))
			return false;

		DBInsert stmt(db);
		stmt.setQuery("INSERT INTO `house_data` (`house_id`, `world_id`, `data`) VALUES ");
		return saveHouseBinary(db, stmt, house) && stmt.execute();
	}

	DBQuery query;
	query << "DELETE FROM `tile_items` WHERE `tile_id` IN (SELECT `id` FROM `tiles` WHERE `house_id` = "
		<< house->getId() << " AND `world_id` = " << g_config.getNumber(ConfigManager::WORLD_ID)
		<< ") AND `world_id` = " << g_config.getNumber(ConfigManager::WORLD_ID);
	if(!db->query(query.str()))
		return false;

	query.str("");
	query << "DELETE FROM `tiles` WHERE `house_id` = " << house->getId()
		<< " AND `world_id` = " << g_config.getNumber(ConfigManager::WORLD_ID);
	if(!db->query(query.str()))
		return false;

	query.str("");
	query << "SELECT `id` FROM `tiles` WHERE `world_id` = " << g_config.getNumber(ConfigManager::WORLD_ID) << " ORDER BY `id` DESC LIMIT 1;";

	DBResult* result;
	if(!(result = db->storeQuery(query.str())))
		return false;

	uint32_t tileId = result->getDataInt("id") + 1;
	result->free();
	return saveHouseRelational(db, house, tileId);
}