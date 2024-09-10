/////////////////////////////////////////////////////////////////////////////
// init
/////////////////////////////////////////////////////////////////////////////
bool Vigasoco::init(std::string name)
{
	// calls template method to perform platform specific initialization
	if (!platformSpecificInit()){
		_errorMsg = "platformSpecificInit() failed";
		return false;
	}

	// creates the game driver
	_driver = createGameDriver(name);

	if (!_driver){
		_errorMsg = "unknown game " + name;
		return false;
	}

	// calls template method to create the palette
	createPalette();

	if (!_palette){
		_errorMsg = "createPalette() failed";
		return false;
	}

	// inits the palette (the last 2 colors are used by the core to display information)
	int numColors = _driver->getVideoInfo()->colors;

	// TODO: VGA 
	// Cambiar para no poner 256 a fuego
	_palette->init(256); // pruebas VGA
	

	// init the colors used by the core to display information
	/* 
	_palette->setColor(numColors + 0, 0x00, 0x00, 0x00);
	_palette->setColor(numColors + 1, 0xff, 0xff, 0xff);
	*/
	// TODO: VGA6, mientras probamos con VGA, metemos esto a fuego en el color 253 y 254
	_palette->setColor(253, 0x00, 0x00, 0x00);
	_palette->setColor(254, 0xff, 0xff, 0xff);


	// inits the fonts used by the core
	_fontManager = new FontManager(_palette, numColors/2);
	_fontManager->init();

	// creates the FileLoader
	FileLoader *fl = new FileLoader();

	// calls template method to add custom loaders
	addCustomLoaders(fl);

	// inits the game driver (load files, decode gfx, preprocessing, etc)
	if (!_driver->init(_palette)){
		// calls template method to remove custom loaders
		removeCustomLoaders(fl);

		delete fl;

		_errorMsg = "driver->init() failed\n" + _driver->getError();

		return false;
	}

	// calls template method to remove custom loaders
	removeCustomLoaders(fl);

	// deletes the FileLoader
	delete fl;

	// calls template method to get a DrawPlugin
	createDrawPlugin();

	if (!_drawPlugin){
		_errorMsg = "createDrawPlugin() failed";
		return false;
	}

	// inits the DrawPlugin with the selected GameDriver
	if (!_drawPlugin->init(_driver->getVideoInfo(), _palette)){
		_errorMsg = "drawPlugin->init() failed";
		return false;
	}
	// notify the driver that the drawPlugin has been initialized
	_driver->videoInitialized(_drawPlugin);

	// creates the input handler
	_inputHandler = new InputHandler();

	// calls template method to add input plugins
	addCustomInputPlugins();

	// inits the input handler
	if (!_inputHandler->init(_driver)){
		_errorMsg = "inputHandler->init() failed";
		return false;
	}

	// calls template method to get a high resolution timer
	createTimer();

	// creates the timing handler
	_timingHandler = new TimingHandler();

	// inits the timing handler
	if (!_timingHandler->init(_timer, _driver->getNumInterruptsPerSecond(), _driver->getNumInterruptsPerVideoUpdate(), _driver->getnumInterruptsPerLogicUpdate())){
		_errorMsg = "timerHandler->init() failed";
		return false;
	}

	// calls template method to get a AudioPlugin
	createAudioPlugin();

	if (!_audioPlugin){
		_errorMsg = "createAudioPlugin() failed";
		return false;
	}

	// inits the AudioPlugin with the selected GameDriver
	if (!_audioPlugin->init(/* TODO: _driver->getAudioInfo() */)){
		_errorMsg = "audioPlugin->init() failed";
		return false;
	}

	// notify the driver that the drawPlugin has been initialized
	_driver->audioInitialized(_audioPlugin);

	// creates the async thread
	createAsyncThread();

	if (!_asyncThread){
		_errorMsg = "createAsyncThread() failed";
		return false;
	}

	// calls template method to perform specific actions after initialization has been completed
	initCompleted();

	return true;
}