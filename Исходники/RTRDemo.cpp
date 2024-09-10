int RTRDemo::init(const std::string& configFile)
{
    // Init log file
    std::string logFile = "log/" + createTimeStamp() + ".log";
    if (!CLogger::initLogFile(logFile))
    {
        LOG_WARNING("Failed to create log file at %s.", logFile.c_str());
    }

    m_debugInfo = std::make_shared<CDebugInfo>();
    CLogger::addListener(m_debugInfo.get());

    if (!m_config.load(configFile))
    {
        LOG_WARNING("Failed to load config file %s, starting with default settings.",
                    configFile.c_str());
    }

    // Create window for rendering
    if (!initWindow())
    {
        LOG_ERROR("Failed to initialize window.");
        return 1;
    }

	m_inputProvider = std::make_shared<CGlfwInputProvider>(m_window->getGlfwHandle());

    // Create resource manager
    m_resourceManager.reset(createResourceManager());
    if (m_resourceManager == nullptr)
    {
        LOG_ERROR("Failed to initialize resource manager.");
        return 1;
    }

	// Create animation world
	m_animationWorld = std::make_shared<CAnimationWorld>();

    // Graphics resource manager, listens to resource manager
    CGraphicsResourceManager* manager = new CGraphicsResourceManager;
    m_resourceManager->addResourceListener(manager);
    m_graphicsResourceManager.reset(manager);

    // Create renderer
    if (!initRenderer())
    {
        LOG_ERROR("Failed to initialize renderer.");
        return 1;
    }

    if (!initScene())
    {
        LOG_ERROR("Failed to initialize scene.");
        return 1;
    }

    m_camera = std::make_shared<CFirstPersonCamera>(
        glm::vec3(0.5f, 0.f, 0.5f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f), 45.f,
        4.f / 3.f, 0.01f, 1000.f);

    m_cameraController = std::make_shared<CCameraController>();
    m_cameraController->setCamera(m_camera);
    m_cameraController->setInputProvider(m_inputProvider.get());

    m_debugInfoDisplay = std::make_shared<CDebugInfoDisplay>(m_resourceManager);

    m_window->addListener(m_cameraController.get());

    return 0;
}