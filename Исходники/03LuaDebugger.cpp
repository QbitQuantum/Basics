int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        TheLuaManager->init();

        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Setup the Lua Manager

        BoostPath ModulePath("./Data/");
        std::string PackagePath = std::string("?;")
            + (ModulePath / "?.lua" ).file_string() + ";"
            + (ModulePath / "?" /  "init.lua").file_string();
        TheLuaManager->setPackagePath(PackagePath);

        // Make Torus Node (creates Torus in background of scene)
        GeometryRefPtr TorusGeometry = makeTorusGeo(.5, 2, 16, 16);
        setName(TorusGeometry,"Torus Geometry");
        //calcVertexTangents(TorusGeometry,0,Geometry::TexCoords7FieldId, Geometry::TexCoords6FieldId);


        NodeRefPtr TorusGeometryNode = Node::create();
        setName(TorusGeometryNode,"Torus Geometry Node");
        TorusGeometryNode->setCore(TorusGeometry);

        //Torus Transformation Node
        TransformRefPtr TheTorusNodeTransform = Transform::create();

        NodeRefPtr TheTorusTransfromNode = Node::create();
        TheTorusTransfromNode->setCore(TheTorusNodeTransform);
        TheTorusTransfromNode->addChild(TorusGeometryNode);
        setName(TheTorusTransfromNode,"Torus Transform Node");

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TheTorusTransfromNode);
        setName(scene,"Scene Node");

        //Light Beacon Node
        TransformRefPtr TheLightBeaconNodeTransform = Transform::create();

        NodeRefPtr TheLightBeaconNode = Node::create();
        TheLightBeaconNode->setCore(TheLightBeaconNodeTransform);
        setName(TheLightBeaconNode,"Light Beacon Node");


        //Light Node
        DirectionalLightRefPtr TheLightCore = DirectionalLight::create();
        TheLightCore->setDirection(Vec3f(1.0,0.0,0.0));
        TheLightCore->setAmbient(Color4f(1.0,1.0,1.0,1.0));
        TheLightCore->setDiffuse(Color4f(1.0,1.0,1.0,1.0));
        TheLightCore->setSpecular(Color4f(1.0,1.0,1.0,1.0));
        TheLightCore->setBeacon(TheLightBeaconNode);

        NodeRefPtr TheLightNode = Node::create();
        TheLightNode->setCore(TheLightCore);
        TheLightNode->addChild(scene);
        setName(TheLightNode,"Light Node");

        NodeRefPtr RootNode = Node::create();
        RootNode->setCore(Group::create());
        RootNode->addChild(TheLightNode);
        RootNode->addChild(TheLightBeaconNode);
        setName(RootNode,"Root Node");

        // Create the Graphics
        GraphicsRefPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        //Create the Main interface
        LuaDebuggerInterface TheLuaDebuggerInterface;

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRefPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        BorderLayoutRefPtr MainInternalWindowLayout = BorderLayout::create();

        //Split Panel
        BorderLayoutConstraintsRefPtr SplitPanelConstraints = BorderLayoutConstraints::create();
        SplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
        TheLuaDebuggerInterface.getMainSplitPanel()->setConstraints(SplitPanelConstraints);

        BorderLayoutConstraintsRefPtr ButtonPanelConstraints = BorderLayoutConstraints::create();
        ButtonPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
        TheLuaDebuggerInterface.getButtonPanel()->setConstraints(ButtonPanelConstraints);

        BorderLayoutConstraintsRefPtr CodeAreaInfoPanelConstraints = BorderLayoutConstraints::create();
        CodeAreaInfoPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
        TheLuaDebuggerInterface.getCodeAreaInfoPanel()->setConstraints(CodeAreaInfoPanelConstraints);

        InternalWindowRefPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(TheLuaDebuggerInterface.getButtonPanel());
        MainInternalWindow->pushToChildren(TheLuaDebuggerInterface.getMainSplitPanel());
        MainInternalWindow->pushToChildren(TheLuaDebuggerInterface.getCodeAreaInfoPanel());
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setTitle("Lua Debugger");
        setName(MainInternalWindow,"Internal Window");

        // Create the Drawing Surface
        UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRefPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

        //Scene Background
        GradientBackgroundRefPtr SceneBackground = GradientBackground::create();
        SceneBackground->addLine(Color3f(0.0,0.0,0.0),0.0);
        setName(SceneBackground,"Scene Background");

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);
        sceneManager.setRoot(RootNode);
        //sceneManager.setHeadlight(false);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);
        TutorialViewport->setBackground(SceneBackground);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped,
                                                    _1,
                                                    &TheLuaDebuggerInterface));

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "03LuaDebugger");

        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setPreferredSize(WinSize * 0.85);

        //Enter main Loop
        TutorialWindow->mainLoop();

        TheLuaManager->uninit();
    }

    osgExit();

    return 0;
}