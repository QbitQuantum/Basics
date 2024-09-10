bool CEngine::init(const char* configFile)
{
    // Init log file
    std::string logFile = "log/" + createTimeStamp() + ".log";
    if (!CLogger::initLogFile(logFile))
    {
        LOG_WARNING("Failed to create log file at %s.", logFile.c_str());
    }

	// Config data with default values
	std::string modeType = "demo"; // Startup mode for the application
	std::string sceneFile = "data/world/test_1.json"; // Scene file to load and render if mode is demo
	std::string gameFile = "data/game/defenders_of_cthedra/game.json"; // Game file to load if mode is game
	std::string rendererType = "deferred"; // Renderer type to use
	
	// Window parameters
	unsigned int windowWidth = 800;
	unsigned int windowHeight = 600;
	std::string windowTitle = "CG 2015";

	// Load config file based on extension
	bool loadSuccess = false;
	if (getFileExtension(configFile) == "ini")
	{
		CIniFile configIni;
		if (configIni.load(configFile))
		{
			// Load values
			modeType = configIni.getValue("mode", "type", "demo");
			sceneFile = configIni.getValue("scene", "file", "data/world/test_1.json");
			gameFile = configIni.getValue("game", "file", "data/game/defenders_of_cthedra/game.json");
			rendererType = configIni.getValue("renderer", "type", "forward");
			windowWidth = configIni.getValue("window", "width", 800);
			windowHeight = configIni.getValue("window", "height", 600);
			windowTitle = configIni.getValue("window", "type", "CG 2015");
			loadSuccess = true;
		}
	}
	else if (getFileExtension(configFile) == "json")
	{
		Json::Value root;
		if (load(configFile, root))
		{
			// Sub nodes
			Json::Value game = root["game"];
			Json::Value renderer = root["renderer"];
			Json::Value window = root["window"];

			// Load values
			modeType = "game"; // Json only supports game mode
			sceneFile = ""; // Scene file not supported/legacy
			load(game, "file", gameFile);
			load(renderer, "type", rendererType);
			load(window, "width", windowWidth);
			load(window, "height", windowHeight);
			load(window, "title", windowTitle);
			loadSuccess = true;
		}
	}
	else
	{
		LOG_WARNING("The config file %s has an unknown file extension.");
	}

	// Check if config loaded successfully
	if (!loadSuccess)
	{
		LOG_WARNING("Failed to load config file %s. Starting with default settings.", configFile);
		// TODO Return if no config exists?
	}

    // Create window for rendering
    if (!initWindow(windowWidth, windowHeight, windowTitle))
    {
        LOG_ERROR("Failed to initialize window.");
        return false;
    }
	// TODO GLFW handle not properly wrapped away, GFLW should not be used directly
	m_inputProvider = std::make_shared<CGlfwInputProvider>(m_window->getGlfwHandle());

    // Create central resource manager
    m_resourceManager.reset(createResourceManager());
    if (m_resourceManager == nullptr)
    {
        LOG_ERROR("Failed to initialize resource manager.");
        return false;
    }

	// Create and initialize graphics system
	m_graphicsSystem = std::make_shared<CGraphicsSystem>();
	if (!m_graphicsSystem->init(*m_resourceManager))
	{
		LOG_ERROR("Failed to initialize graphics system.");
		return false;
	}

	// Legacy stuff to keep demo mode working
	// TODO Should be removed
	if (modeType == "demo")
	{
		if (!initDemo(sceneFile))
		{
			LOG_ERROR("Failed to initialize demo mode.");
			return false;
		}
	}
	else // Create and initialize game system
	{
		if (!initGameSystem(gameFile))
		{
			LOG_ERROR("Failed to initialize game system.");
			return false;
		}
	}
    return true;
}