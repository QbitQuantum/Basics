TinselEngine::TinselEngine(OSystem *syst, const TinselGameDescription *gameDesc) :
		Engine(syst), _gameDescription(gameDesc), _random("tinsel") {
	_vm = this;

	_config = new Config(this);

	// Register debug flags
	DebugMan.addDebugChannel(kTinselDebugAnimations, "animations", "Animations debugging");
	DebugMan.addDebugChannel(kTinselDebugActions, "actions", "Actions debugging");
	DebugMan.addDebugChannel(kTinselDebugSound, "sound", "Sound debugging");
	DebugMan.addDebugChannel(kTinselDebugMusic, "music", "Music debugging");

	// Setup mixer
	syncSoundSettings();

	// Add DW2 subfolder to search path in case user is running directly from the CDs
	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "dw2");

	// Add subfolders needed for psx versions of Discworld 1
	if (TinselV1PSX)
		SearchMan.addDirectory(gameDataDir.getPath(), gameDataDir, 0, 3, true);

	const GameSettings *g;

	const char *gameid = ConfMan.get("gameid").c_str();
	for (g = tinselSettings; g->gameid; ++g)
		if (!scumm_stricmp(g->gameid, gameid))
			_gameId = g->id;

	int cd_num = ConfMan.getInt("cdrom");
	if (cd_num >= 0)
		_system->getAudioCDManager()->openCD(cd_num);

	_midiMusic = new MidiMusicPlayer();
	_pcmMusic = new PCMMusicPlayer();

	_sound = new SoundManager(this);

	_bmv = new BMVPlayer();

	_mousePos.x = 0;
	_mousePos.y = 0;
	_keyHandler = NULL;
	_dosPlayerDir = 0;
}