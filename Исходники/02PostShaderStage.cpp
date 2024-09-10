// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();

        //Initialize Window
        TutorialWindow->initWindow();

        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));

        BoostPath FilePath("../Animation/Data/Nanobot.dae");
        if(argc >= 2)
        {
            FilePath = BoostPath(argv[1]);
            if(!boost::filesystem::exists(FilePath))
            {
                std::cerr << "Could not load file: "<< FilePath.string()
                          << ", because no such files exists."<< std::endl;
                FilePath = BoostPath("../Animation/Data/Nanobot.dae");
            }
        }

        NodeRefPtr LoadedRoot;
        std::vector<AnimationRecPtr> LoadedAnimations;

        FCFileType::FCPtrStore ObjStore;
        try
        {
            ObjStore = FCFileHandler::the()->read(FilePath);
        }
        catch(std::exception &ex)
        {
            std::cerr << "Failed to load file: " << FilePath.string() << ", error:"
                     << ex.what()                        << std::endl;
            return -1;
        }
        for(FCFileType::FCPtrStore::iterator StorItor(ObjStore.begin());
            StorItor != ObjStore.end();
            ++StorItor)
        {
            //Animations
            if((*StorItor)->getType().isDerivedFrom(Animation::getClassType()))
            {
                LoadedAnimations.push_back(dynamic_pointer_cast<Animation>(*StorItor));
                LoadedAnimations.back()->attachUpdateProducer(TutorialWindow);
                LoadedAnimations.back()->start();
            }
            //Root Node
            if((*StorItor)->getType() == Node::getClassType() &&
                    dynamic_pointer_cast<Node>(*StorItor)->getParent() == NULL)
            {
                LoadedRoot = dynamic_pointer_cast<Node>(*StorItor);
            }
        }

        if(LoadedRoot == NULL)
        {
            LoadedRoot = SceneFileHandler::the()->read(FilePath.string().c_str());
        }

        if(LoadedRoot == NULL)
        {
            LoadedRoot= makeTorus(.5, 2, 32, 32);
        }

        //Make the fog node
        PostShaderStageRecPtr PostShaderStageCore = PostShaderStage::create();
        PostShaderStageCore->clearPasses();
        PostShaderStageCore->addPass("", generateNoEffectProg());


        DirectionalLightRecPtr SceneLightCore = DirectionalLight::create();
        SceneLightCore->setAmbient(Color4f(0.2f, 0.2f, 0.2f, 1.0f));
        SceneLightCore->setDiffuse(Color4f(0.8f, 0.8f, 0.8f, 1.0f));
        SceneLightCore->setSpecular(Color4f(1.0f, 1.0f, 1.0f, 1.0f));

        NodeRefPtr SceneLight = makeNodeFor(SceneLightCore);
        SceneLight->addChild(LoadedRoot);

        NodeRefPtr PostShaderStageNode = makeNodeFor(PostShaderStageCore);
        PostShaderStageNode->addChild(SceneLight);

        //Make Main Scene Node
        NodeRefPtr scene = makeCoredNode<Group>();

        scene->addChild(PostShaderStageNode);

        // tell the manager what to manage
        sceneManager.setRoot  (scene);
        SceneLightCore->setBeacon(sceneManager.getCamera()->getBeacon());

        //Create the Documentation Foreground and add it to the viewport
        SimpleScreenDoc TheSimpleScreenDoc(&sceneManager, TutorialWindow);

        // show the whole scene
        sceneManager.showAll();

        sceneManager.getWindow()->getPort(0)->setTravMask(1);
        RenderOptionsRecPtr ViewportRenderOptions = RenderOptions::create();
        ViewportRenderOptions->setRenderProperties(0x0);
        ViewportRenderOptions->setRenderProperties(RenderPropertiesPool::the()->getFrom1("Default"));
        ViewportRenderOptions->setRenderProperties(0x01);

        sceneManager.getWindow()->getPort(0)->setRenderOptions(ViewportRenderOptions);

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "Collada Loader");

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                      TutorialWindow.get(),
                                                      PostShaderStageCore.get()));

        //Enter main Loop
        TutorialWindow->mainLoop();

    }

    osgExit();

    return 0;
}