void TutorialLevel::setup(){
    INFO("Generating Tutorial Level...");
    readFile();
    initalizeGrid();
    createRenders();
    createLevel();
    waterSurfaceManager = WaterSurfaceManagerPtr(new WaterSurfaceManager());
    addGameObject(waterSurfaceManager);
    INFO("Removal String so less of make");
    INFO("Setting up the cameras for the Test Level...");
    CameraPtr cam3(new Camera(glm::vec3(25, 30, 0), glm::vec3(10, 20, 6),
                             glm::vec3(0, 1, 0)));
    cam3->setProjectionMatrix(
        glm::perspective(glm::radians(90.0f),
                        (float) Global::ScreenWidth/Global::ScreenHeight,
                        0.1f, 100.f));

    addCamera("CinematicCamera", cam3);
    setMainCamera("CinematicCamera");
    setCullingCamera("CinematicCamera");

    CameraPtr cam1(new Camera(glm::vec3(4, 10, -5), glm::vec3(4, 4, -10),
                              glm::vec3(0, 1, 0)));
    cam1->setProjectionMatrix(
        glm::perspective(glm::radians(90.0f),
                         (float) Global::ScreenWidth/Global::ScreenHeight,
                         0.1f, 100.f));
    addCamera("Camera1", cam1);
 
    CameraPtr cam2(new Camera(glm::vec3(0, 1, 0), glm::vec3(-6, -3, 6),
                              glm::vec3(0, 1, 0)));
    cam2->setProjectionMatrix(
        glm::perspective(glm::radians(90.0f),
                         (float) Global::ScreenWidth/Global::ScreenHeight,
                         0.1f, 100.f));
    l1 = LightPtr(new Light(glm::vec3(1), 30.0f, glm::vec3(0, 30, 0)));
    l1->setPosition(l1->getDirection());

    Uniform3DGridPtr<int> typeGrid = getTypeGrid();
    gridCenter = glm::vec3((typeGrid->getMaxX() - typeGrid->getMinX())/2.0f,
                           (typeGrid->getMaxY() - typeGrid->getMinY())/2.0f,
                           (typeGrid->getMinZ() - typeGrid->getMaxZ())/2.0f);
    l1->setViewMatrix(glm::lookAt(

        l1->getPosition(),
        gridCenter, glm::vec3(0, 1, 0)));
    l1->setProjectionMatrix(glm::ortho<float>(-30,30,-30,30,-70,70));

    addLight("Sun", l1);
    INFO("Setting up the player for the Test Level...");
    cinematicPlayer = CinematicPlayerPtr(new CinematicPlayer(cam3));
    cinematicPlayer->setup();
    addGameObject("cinematicPlayer", cinematicPlayer);

    player = PlayerPtr(new Player(cam1, 2));
    player->setup();
    addGameObject("player" , player);
    CollisionManager::addCollisionObjectToList(player);
    debugPlayer = DebugPlayerPtr(new DebugPlayer(cam2));
    debugPlayer->setup();
    addGameObject("debugPlayer" , debugPlayer);
    //Text
    addCamera("DebugCamera", cam2);

    sky = ObjectPtr(new Object(
        LoadManager::getMesh("sphere.obj"),
        MaterialManager::getMaterial("None")));

    sky->applyTexture(LoadManager::getTexture("Sky"));
    sky->enableTexture();
    sky->scale(glm::vec3(-90.0f,-90.0f,-90.0f));
    sky->translate(Director::getScene()->getCamera()->getEye());
    RenderEngine::getRenderElement("textured")->addObject(sky);

    ExclamationPtr exclamation = ExclamationPtr(new Exclamation(glm::vec3(30, 26, -48)));
    exclamation->setup();
    addGameObject("exclamation", exclamation);
}