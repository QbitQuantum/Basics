ServerDatabase::ServerDatabase(ConfigManager* configManager) {
	const String& dbHost = configManager->getDBHost();
	const String& dbUser = configManager->getDBUser();
	const String& dbPass = configManager->getDBPass();
	const String& dbName = configManager->getDBName();
	const uint16& dbPort = configManager->getDBPort();

	databases = new Vector<Database*>();

	for (int i = 0; i < DEFAULT_SERVERDATABASE_INSTANCES; ++i) {
		Database* db = new server::db::mysql::MySqlDatabase(String("ServerDatabase" + String::valueOf(i)), dbHost);
		db->connect(dbName, dbUser, dbPass, dbPort);

		databases->add(db);
	}
}