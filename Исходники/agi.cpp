int AgiEngine::agiInit() {
	int ec, i;

	debug(2, "initializing");
	debug(2, "game version = 0x%x", getVersion());

	// initialize with adj.ego.move.to.x.y(0, 0) so to speak
	_game.adjMouseX = _game.adjMouseY = 0;

	// reset all flags to false and all variables to 0
	memset(_game.flags, 0, sizeof(_game.flags));
	memset(_game.vars, 0, sizeof(_game.vars));

	// clear all resources and events
	for (i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
		memset(&_game.views[i], 0, sizeof(struct AgiView));
		memset(&_game.pictures[i], 0, sizeof(struct AgiPicture));
		memset(&_game.logics[i], 0, sizeof(struct AgiLogic));
		memset(&_game.sounds[i], 0, sizeof(class AgiSound *)); // _game.sounds contains pointers now
		memset(&_game.dirView[i], 0, sizeof(struct AgiDir));
		memset(&_game.dirPic[i], 0, sizeof(struct AgiDir));
		memset(&_game.dirLogic[i], 0, sizeof(struct AgiDir));
		memset(&_game.dirSound[i], 0, sizeof(struct AgiDir));
	}

	// clear view table
	for (i = 0; i < SCREENOBJECTS_MAX; i++)
		memset(&_game.screenObjTable[i], 0, sizeof(struct ScreenObjEntry));

	memset(&_game.addToPicView, 0, sizeof(struct ScreenObjEntry));

	_words->clearEgoWords();

	if (!_menu)
		_menu = new GfxMenu(this, _gfx, _picture, _text);

	_gfx->initPriorityTable();

	// Clear the string buffer on startup, but not when the game restarts, as
	// some scripts expect that the game strings remain unaffected after a
	// restart. An example is script 98 in SQ2, which is not invoked on restart
	// to ask Ego's name again. The name is supposed to be maintained in string 1.
	// Fixes bug #3292784.
	if (!_restartGame) {
		for (i = 0; i < MAX_STRINGS; i++)
			_game.strings[i][0] = 0;
	}

	// setup emulation

	switch (getVersion() >> 12) {
	case 2:
		debug("Emulating Sierra AGI v%x.%03x",
		      (int)(getVersion() >> 12) & 0xF,
		      (int)(getVersion()) & 0xFFF);
		break;
	case 3:
		debug("Emulating Sierra AGI v%x.002.%03x",
		      (int)(getVersion() >> 12) & 0xF,
		      (int)(getVersion()) & 0xFFF);
		break;
	}

	if (getPlatform() == Common::kPlatformAmiga)
		_game.gameFlags |= ID_AMIGA;

	if (getFeatures() & GF_AGDS)
		_game.gameFlags |= ID_AGDS;

	if (_game.gameFlags & ID_AMIGA)
		debug(1, "Amiga padded game detected.");

	if (_game.gameFlags & ID_AGDS)
		debug(1, "AGDS mode enabled.");

	ec = _loader->init();   // load vol files, etc

	if (ec == errOK)
		ec = _loader->loadObjects(OBJECTS);

	// note: demogs has no words.tok
	if (ec == errOK)
		ec = _loader->loadWords(WORDS);

	// Load logic 0 into memory
	if (ec == errOK)
		ec = _loader->loadResource(RESOURCETYPE_LOGIC, 0);

#ifdef __DS__
	// Normally, the engine loads the predictive text dictionary when the predictive dialog
	// is shown.  On the DS version, the word completion feature needs the dictionary too.

	// FIXME - loadDict() no long exists in AGI as this has been moved to within the
	// GUI Predictive Dialog, but DS Word Completion is probably broken due to this...
#endif

	_keyHoldMode = false;
	_keyHoldModeLastKey = Common::KEYCODE_INVALID;

	_game.mouseFence.setWidth(0); // Reset

	// Reset in-game timer
	inGameTimerReset();

	// Sync volume settings from ScummVM system settings
	setVolumeViaSystemSetting();

	return ec;
}