DatabaseMySQL::DatabaseMySQL() :
	m_timeoutTask(0)
{
	m_connected = false;
	if(!mysql_init(&m_handle))
	{
		std::clog << std::endl << "Failed to initialize MySQL connection handler." << std::endl;
		return;
	}

	uint32_t timeout = g_config.getNumber(ConfigManager::MYSQL_READ_TIMEOUT);
	if(timeout)
		mysql_options(&m_handle, MYSQL_OPT_READ_TIMEOUT, (const char*)&timeout);

	timeout = g_config.getNumber(ConfigManager::MYSQL_WRITE_TIMEOUT);
	if(timeout)
		mysql_options(&m_handle, MYSQL_OPT_WRITE_TIMEOUT, (const char*)&timeout);

	my_bool reconnect = true;
	mysql_options(&m_handle, MYSQL_OPT_RECONNECT, &reconnect);
	if(!mysql_real_connect(&m_handle, g_config.getString(ConfigManager::SQL_HOST).c_str(), g_config.getString(
		ConfigManager::SQL_USER).c_str(), g_config.getString(ConfigManager::SQL_PASS).c_str(), g_config.getString(
		ConfigManager::SQL_DB).c_str(), g_config.getNumber(ConfigManager::SQL_PORT), NULL, 0))
	{
		std::clog << "Failed connecting to database - MYSQL ERROR: " << mysql_error(&m_handle) << " (" << mysql_errno(&m_handle) << ")" << std::endl;
		return;
	}

	m_connected = true;
	if(mysql_get_client_version() <= 50019)
		//MySQL servers <= 5.0.19 have a bug where MYSQL_OPT_RECONNECT option is reset by mysql_real_connect calls.
		//Read this http://dev.mysql.com/doc/refman/5.0/en/mysql-options.html for more information.
		std::clog << std::endl << "> WARNING: Outdated MySQL server detected, consider upgrading to a newer version." << std::endl;

	timeout = g_config.getNumber(ConfigManager::SQL_KEEPALIVE) * 1000;
	if(timeout)
		m_timeoutTask = Scheduler::getInstance().addEvent(createSchedulerTask(timeout,
			boost::bind(&DatabaseMySQL::keepAlive, this)));

	if(!g_config.getBool(ConfigManager::HOUSE_STORAGE))
		return;

	//we cannot lock mutex here :)
	DBResult* result = storeQuery("SHOW variables LIKE 'max_allowed_packet';");
	if(!result)
		return;

	if(result->getDataLong("Value") < 16776192)
		std::clog << std::endl << "> WARNING: max_allowed_packet might be set too low for binary map storage." << std::endl
			<< "Use the following query to raise max_allow_packet: SET GLOBAL max_allowed_packet = 16776192;" << std::endl;

	result->free();
}