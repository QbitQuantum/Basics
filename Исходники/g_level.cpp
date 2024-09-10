void G_DoLoadLevel (int position, bool autosave)
{ 
	static int lastposition = 0;
	gamestate_t oldgs = gamestate;
	int i;

	if (NextSkill >= 0)
	{
		UCVarValue val;
		val.Int = NextSkill;
		gameskill.ForceSet (val, CVAR_Int);
		NextSkill = -1;
	}

	if (position == -1)
		position = lastposition;
	else
		lastposition = position;

	G_InitLevelLocals ();
	StatusBar->DetachAllMessages ();

	// Force 'teamplay' to 'true' if need be.
	if (level.flags2 & LEVEL2_FORCETEAMPLAYON)
		teamplay = true;

	// Force 'teamplay' to 'false' if need be.
	if (level.flags2 & LEVEL2_FORCETEAMPLAYOFF)
		teamplay = false;

	FString mapname = level.MapName;
	mapname.ToLower();
	Printf (
			"\n\35\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36"
			"\36\36\36\36\36\36\36\36\36\36\36\36\37\n\n"
			TEXTCOLOR_BOLD "%s - %s\n\n",
			mapname.GetChars(), level.LevelName.GetChars());

	if (wipegamestate == GS_LEVEL)
		wipegamestate = GS_FORCEWIPE;

	if (gamestate != GS_TITLELEVEL)
	{
		gamestate = GS_LEVEL; 
	}

	// Set the sky map.
	// First thing, we have a dummy sky texture name,
	//	a flat. The data is in the WAD only because
	//	we look for an actual index, instead of simply
	//	setting one.
	skyflatnum = TexMan.GetTexture (gameinfo.SkyFlatName, FTexture::TEX_Flat, FTextureManager::TEXMAN_Overridable);

	// DOOM determines the sky texture to be used
	// depending on the current episode and the game version.
	// [RH] Fetch sky parameters from FLevelLocals.
	sky1texture = level.skytexture1;
	sky2texture = level.skytexture2;

	// [RH] Set up details about sky rendering
	R_InitSkyMap ();

	for (i = 0; i < MAXPLAYERS; i++)
	{ 
		if (playeringame[i] && (deathmatch || players[i].playerstate == PST_DEAD))
			players[i].playerstate = PST_ENTER;	// [BC]
		memset (players[i].frags,0,sizeof(players[i].frags));
		if (!(dmflags2 & DF2_YES_KEEPFRAGS) && (alwaysapplydmflags || deathmatch))
			players[i].fragcount = 0;
	}

	if (changeflags & CHANGELEVEL_NOMONSTERS)
	{
		level.flags2 |= LEVEL2_NOMONSTERS;
	}
	else
	{
		level.flags2 &= ~LEVEL2_NOMONSTERS;
	}
	if (changeflags & CHANGELEVEL_PRERAISEWEAPON)
	{
		level.flags2 |= LEVEL2_PRERAISEWEAPON;
	}

	level.maptime = 0;
	P_SetupLevel (level.MapName, position);

	AM_LevelInit();

	// [RH] Start lightning, if MAPINFO tells us to
	if (level.flags & LEVEL_STARTLIGHTNING)
	{
		P_StartLightning ();
	}

	gameaction = ga_nothing; 

	// clear cmd building stuff
	ResetButtonStates ();

	SendItemUse = NULL;
	SendItemDrop = NULL;
	mousex = mousey = 0; 
	sendpause = sendsave = sendturn180 = SendLand = false;
	LocalViewAngle = 0;
	LocalViewPitch = 0;
	paused = 0;

	//Added by MC: Initialize bots.
	if (deathmatch)
	{
		bglobal.Init ();
	}

	if (timingdemo)
	{
		static bool firstTime = true;

		if (firstTime)
		{
			starttime = I_GetTime (false);
			firstTime = false;
		}
	}

	level.starttime = gametic;
	G_UnSnapshotLevel (!savegamerestore);	// [RH] Restore the state of the level.
	G_FinishTravel ();
	// For each player, if they are viewing through a player, make sure it is themselves.
	for (int ii = 0; ii < MAXPLAYERS; ++ii)
	{
		if (playeringame[ii] && (players[ii].camera == NULL || players[ii].camera->player != NULL))
		{
			players[ii].camera = players[ii].mo;
		}
	}
	StatusBar->AttachToPlayer (&players[consoleplayer]);
	P_DoDeferedScripts ();	// [RH] Do script actions that were triggered on another map.
	
	if (demoplayback || oldgs == GS_STARTUP || oldgs == GS_TITLELEVEL)
		C_HideConsole ();

	C_FlushDisplay ();

	// [RH] Always save the game when entering a new level.
	if (autosave && !savegamerestore && disableautosave < 1)
	{
		DAutosaver GCCNOWARN *dummy = new DAutosaver;
	}
}