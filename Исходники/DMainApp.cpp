BOOL CDAppMain::InitServer()
{
    if ( !Globals::LoadConfigure() )
    {
        return rfalse( 0, 0, "LoadConfigure failure" );
    }

    //搜寻帐号服务器和场景服务器，并试图建立连接
    m_bQuit = FALSE;

	LPCSTR ip = NULL, port = NULL, account = NULL;

    Globals::GetDatabaseIPPORT( ip, port );
    if ( !m_DatabaseClient.Connect( ip, port ) )
        return rfalse(0, 0, "无法连接数据库服务器！");

    //Globals::GetAccountIPPORT( ip, port );
    //if ( !m_AccountClient.Connect( ip, port ) )
   //     return rfalse(0, 0, "无法连接帐号服务器！");
	if ( !m_AccountModuleManage.RegisterALLACC() )
			return rfalse(0, 0, "无法连接帐号服务器！");

    Globals::GetDBCenterIPPORT( ip, port );
    if ( !m_dbCenterClient.Connect( ip, port ) )
        /*return */rfalse( 2, 0, "无法连接中央数据库服务器[%s:%s]！", ip, port );
	
	Globals::GetCenterServerIPPORT(ip, port);
	if (!m_CenterClient.Connect(ip, port))
	{
		return rfalse(2, 1, "无法连接中心服!!!!!");
	}

    // 读取中央数据库列表数据失败时，也可能是正常的情况，所以不需要处理返回值
    Globals::LoadDbcList();

    Globals::GetGameServerPort( port );
    if ( !m_ServerManager.Host( port ) )
        return rfalse(0, 0, "无法启动服务器（S）端口监听！");

    Globals::GetPlayerServerPort( port );
    if ( !m_PlayerManager.Host( port ) )
        return rfalse(0, 0, "无法启动服务器（P）端口监听！");

	/*if (!m_NetGMModule.Init())
		return rfalse(0, 0, "无法启动服务器（GM）端口监听！");*/
	
	Globals::GetGMServerPort(port);
	if (!m_NetGMModule.Init(port))
		return rfalse(0, 0, "无法启动服务器（GM）端口监听！");

	Globals::GetCollectPort(port);
	if (!m_DataCollect.InitializeNet((char *)port))
        return rfalse(0, 0, "无法启动采集服务端口监听！");

    char vermsg[40];
    _snprintf( vermsg, 20, "版本号：Build%04d", SERVER_VERSION );
    rfalse(2, 1, vermsg);

	sprintf(vermsg,"玩家数据版本号：Build 0x%x",SFixPlayerDataBuf::GetVersion() );
	rfalse(2, 1, vermsg);

	int nport = 0;
	Globals::GetServerAccount(account);
	Globals::GetServerIPPORT(ip, nport);

	SQRegisterLoginServer _msg;
	_msg.dwIP = inet_addr(ip);
	_msg.dwPort = nport;
	_msg.index = 0;
	_msg._dNew = 0;
	_msg._dActivity = 0;
	_msg._dRush = 0;
	try
	{
		lite::Serializer slm(_msg.streamservername, sizeof(_msg.streamservername));
		slm(account);
		size_t _esize = slm.EndEdition();
		m_CenterClient.SendToCenterServer(&_msg, static_cast<WORD>(sizeof(_msg) - _esize));
	}
	catch (lite::Xcpt &)
	{
		return FALSE;
	}
	rfalse(2, 1, "Registering To CenterServer");
    rfalse(2, 1, "登陆服务器[%s]启动啦！", Globals::GetChargeMode() ? "收费" : "免费" );

	return TRUE;
}