void CSrvMsgHandler::onLoad(const char* srvName, const unsigned int srvId, unsigned short moduleId)
{
	if (!GatewayProxyConfig::config::getConfigValue(CCfg::getValue("GatewayProxyService", "BusinessXmlConfigFile")).isSetConfigValueSuccess())
	{
		ReleaseErrorLog("set business xml config value error");
		stopService();
		return;
	}
	
    const DBConfig::config& dbCfg = DBConfig::config::getConfigValue(CCfg::getValue("GatewayProxyService", "DbConfigFile"));
	if (!dbCfg.isSetConfigValueSuccess())
	{
		ReleaseErrorLog("set db xml config value error");
		stopService();
		return;
	}

	if (!m_redisDbOpt.connectSvr(dbCfg.redis_db_cfg.center_db_ip.c_str(), dbCfg.redis_db_cfg.center_db_port,
	    dbCfg.redis_db_cfg.center_db_timeout * MillisecondUnit))
	{
		ReleaseErrorLog("gateway connect center redis service failed, ip = %s, port = %u, time out = %u",
		dbCfg.redis_db_cfg.center_db_ip.c_str(), dbCfg.redis_db_cfg.center_db_port, dbCfg.redis_db_cfg.center_db_timeout);
		
		stopService();
		return;
	}
	
	static const unsigned int gatewayProxySrvId = getSrvId();
	m_gatewayProxySrvData.ip = CSocket::toIPInt(CCfg::getValue("NetConnect", "NetIP"));  // 外网IP
	m_gatewayProxySrvData.port = atoi(CCfg::getValue("NetConnect", "Port"));
	m_gatewayProxySrvData.curTimeSecs = time(NULL);
	m_gatewayProxySrvData.currentPersons = 0;
	int rc = m_redisDbOpt.setHField(GatewayProxyListKey, GatewayProxyListKeyLen,
	                                (const char*)&gatewayProxySrvId, sizeof(gatewayProxySrvId), (const char*)&m_gatewayProxySrvData, sizeof(m_gatewayProxySrvData));
	if (rc != 0)
	{
		ReleaseErrorLog("set gateway proxy service data to redis center service failed, rc = %d", rc);
		stopService();
		return;
	}
	
	m_gameHallId = GatewayProxyConfig::config::getConfigValue().commonCfg.game_hall_id;
	
	// 定时保存数据到redis
	unsigned int millisecondUnit = 1000; // 秒转换为毫秒乘值
	unsigned int timerId = setTimer(millisecondUnit * atoi(CCfg::getValue("GatewayProxyService", "SaveDataToDBInterval")),
	                                (TimerHandler)&CSrvMsgHandler::saveDataToDb, 0, NULL, (unsigned int)-1);

    ReleaseInfoLog("gateway message handler load, service name = %s, id = %d, timer id = %u", srvName, srvId, timerId);
}