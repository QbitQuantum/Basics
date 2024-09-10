CNetGame::CNetGame ( )
{
	fRestartWaitTime = 0.0f;
	this->allowAdminTeleport = FALSE;
	this->allowInteriorWeapons = FALSE;
	this->worldTime = 12;
	this->weather	= 1;
	this->enableBonusStuntForAll = true;
	this->gravity	= 0.008f;
	this->deathDropAmount = 0;
	this->enableZoneName = false;
	
	this->playerPool = NULL;
	this->vehiclePool = NULL;
	this->gamemodeManager = NULL;
	this->pickupPool = NULL;
	this->objectPool = NULL;
	this->menuPool = NULL;
	this->textDrawPool = NULL;
	this->disableNameTagLineOfSight = true;
	this->gangZonePool = NULL;
	this->text3DLabelsPool = NULL;
	this->bLanMode = FALSE;
	this->byteMod = 0x01;

	this->blimitGlobalChatRadius = false;
	this->dlimitGlobalChatRadius = 10000.0f;
	this->bLimitPlayerMarkerRadius = FALSE;
	this->dlimitPlayerMarkerRadius = 10000.0f;
	this->nameTagDrawDistance = 70.0f;
	this->disableInteriorEnterExit = false;

	this->currentGameModeIndex = 0;
	this->currentGameModeRepeat = 0;
	this->isFirstGameModeLoad = FALSE;
	this->scriptTimerManager = new CScriptTimers;
	this->scriptHttpManager = new CScriptHttp;

	#ifndef WIN32
		this->elapsedTime = 0.0;
	#endif

	if(__Console->GetIntVar("maxplayers") > MAX_PLAYERS)
		__Console->SetIntVar("maxplayers", MAX_PLAYERS);

	char* szBindAddress = __Console->GetStringVar("bind");
	if (szBindAddress && szBindAddress[0] == 0)
		szBindAddress = NULL;

	uint16_t Port = __Console->GetIntVar("port");
	uint16_t MaxPlayers = __Console->GetIntVar("maxplayers");
	BOOL useLanMode = __Console->GetBoolVar("lanmode");

	this->rakServerInterface = RakNetworkFactory::GetRakServerInterface();
	
	//NetGameStartTime = RakNet::GetTime();

	if (!this->rakServerInterface->Start(MaxPlayers, 0, iServerSleepTimer, Port, szBindAddress))
	{
		if (szBindAddress)
			logprintf("Unable to start server on %s:%d. Port in use?",szBindAddress, Port);
		else
			logprintf("Unable to start server on port: %d. Port in use?", Port);
		return;
	}
	
	LoadBanList();

	if(!this->setNextGamemodeFile(NULL)) 
	{
		logprintf("I couldn't load any gamemode scripts. Please verify your server.cfg");
		logprintf("It needs a gamemode0 line at the very least.");
		fcloseall();
		exit(1);
	}
		
	this->rakServerInterface->StartOccasionalPing();

	char* szPass = __Console->GetStringVar("password");
	if ((szPass) && (szPass[0] != 0)) { 
		this->rakServerInterface->SetPassword(szPass);
	}

	RegisterRPCs(this->rakServerInterface);

	char szTime[256];
	sprintf(szTime, "%02d:%02d", this->worldTime, 0);
	__Console->AddStringVar("worldtime", CONSOLE_VARFLAG_RULE, szTime);
	
	if(useLanMode)
		this->bLanMode = true;

	char szScriptFiles[512];
	int len;

	#ifdef WIN32
		GetCurrentDirectoryA(sizeof(szScriptFiles), szScriptFiles);
		len = strlen(szScriptFiles);
		if (szScriptFiles[len-1] != '\\')
		{
			szScriptFiles[len] = '\\';
			szScriptFiles[len+1] = '\0';
		}
		strcat(szScriptFiles, "scriptfiles\\");
		SetEnvironmentVariableA("AMXFILE", szScriptFiles);
	#else
		getcwd(szScriptFiles, sizeof(szScriptFiles));
		len = strlen(szScriptFiles);
		if (szScriptFiles[len-1] != '/')
		{
			szScriptFiles[len] = '/';
			szScriptFiles[len+1] = '\0';
		}
		strcat(szScriptFiles, "scriptfiles/");
		setenv("AMXFILE", szScriptFiles, 1);
	#endif

	this->filterscriptsManager = new CFilterscriptsManager();

	if (szBindAddress) 
	{
		printf( "\nStarted server on %s:%d, with maxplayers: %d lanmode is %s.\n\n",
			szBindAddress, Port, MaxPlayers, useLanMode?"ON":"OFF" );
	}
	else
	{
		printf( "\nStarted server on port: %d, with maxplayers: %d lanmode is %s.\n\n",
			Port, MaxPlayers, useLanMode?"ON":"OFF" );
	}

	this->gameState = 0;
}