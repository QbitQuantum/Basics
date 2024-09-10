void CMasterServerConfig::LoadRentConfig()
{

	CWOBackendReq req("api_GetRentServers.aspx");
	req.AddParam("411", "1");

	if(!req.Issue())
	{
		r3dOutToLog("Read RentServers FAILED, code: %d\n", req.resultCode_);
		return;
	}

	pugi::xml_document xmlFile;
	req.ParseXML(xmlFile);
	pugi::xml_node xmlSafelock = xmlFile.child("Rent_Servers");
	
	while(!xmlSafelock.empty())
	{
		r3dPoint3D Position;
		char Password[512];
		char Name[512];
		char MapSettings[512];
		
        uint32_t gameServerId = xmlSafelock.attribute("gameServerId").as_uint();
	    r3dscpy(MapSettings,xmlSafelock.attribute("MapSettings").value());
	    uint32_t Region = xmlSafelock.attribute("Region").as_uint();
	    r3dscpy(Name, xmlSafelock.attribute("Name").value());
	    uint32_t MapID = xmlSafelock.attribute("MapID").as_uint();
	    r3dscpy(Password, xmlSafelock.attribute("Password").value());
	    uint32_t MaxPlayers = xmlSafelock.attribute("MaxPlayers").as_uint();
	    uint32_t Owner = xmlSafelock.attribute("Owner").as_uint();
	    uint32_t ExpireTime = xmlSafelock.attribute("ExpireTime").as_uint();
	    uint32_t RentalTime = xmlSafelock.attribute("RentalTime").as_uint();
		uint32_t Crosshair = xmlSafelock.attribute("Crosshair").as_uint();
		uint32_t SNP = xmlSafelock.attribute("SNP").as_uint();

		if(!gMasterGameServer.IsGameServerIdStarted((int)gameServerId))
		{
			r3dOutToLog("Loading Rent Server %i.......\n",gameServerId);
			__int64 secs1 = _time64(&secs1);
			if (secs1<ExpireTime)
			{
				GBGameInfo ginfo;
				ginfo.expirein = ExpireTime;
				strcpy(ginfo.name,Name);
				strcpy(ginfo.PasswordGame,Password);
				ginfo.mapId = MapID;
				ginfo.region = Region;
				ginfo.maxPlayers = MaxPlayers;
				ginfo.ownercustomerid = Owner;
				strcpy(ginfo.MapSettings,MapSettings);
				ginfo.gameServerId = gameServerId;
				ginfo.enableCrosshair = ((int)Crosshair == 1)?true:false;
				ginfo.enableSnipers = ((int)SNP == 1)?true:false;

				CMSNewGameData ngd(ginfo, "", 0);
				DWORD ip;
				DWORD port;
				__int64 sessionId;
				gMasterGameServer.CreateNewGame(ngd, &ip, &port, &sessionId);
				r3dOutToLog("Rent Server ID %i is loaded\n",gameServerId);
			}
			/*else {
				DeleteRentServer(gameServerId);
			}*/
		}
		xmlSafelock = xmlSafelock.next_sibling();
	}
}