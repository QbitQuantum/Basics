    ResourceExample(const string &dir) :
        GlutWindow(Window::Parameters().size(1024, 768).depth(true)), fov(80.0), alpha(135), theta(45), dist(15)
    {
        FileLogger::File *out = new FileLogger::File("log.html");
        Logger::INFO_LOGGER = new FileLogger("INFO", out, Logger::INFO_LOGGER);
        Logger::WARNING_LOGGER = new FileLogger("WARNING", out, Logger::WARNING_LOGGER);
        Logger::ERROR_LOGGER = new FileLogger("ERROR", out, Logger::ERROR_LOGGER);

        ptr<XMLResourceLoader> resLoader = new XMLResourceLoader();
        resLoader->addPath(dir + "/textures");
        resLoader->addPath(dir + "/shaders");
        resLoader->addPath(dir + "/meshes");

        resManager = new ResourceManager(resLoader);

        cube = resManager->loadResource("cube.mesh").cast<MeshBuffers>();
        plane = resManager->loadResource("plane.mesh").cast<MeshBuffers>();

        p1 = resManager->loadResource("camera;spotlight;plastic;").cast<Program>();
        p2 = resManager->loadResource("camera;spotlight;texturedPlastic;").cast<Program>();

        worldCamera = p1->getUniform3f("worldCameraPos");
        localToWorld1 = p1->getUniformMatrix4f("localToWorld");
        localToScreen1 = p1->getUniformMatrix4f("localToScreen");
        localToWorld2 = p2->getUniformMatrix4f("localToWorld");
        localToScreen2 = p2->getUniformMatrix4f("localToScreen");

        fb = FrameBuffer::getDefault();
        fb->setDepthTest(true, LESS);
    }