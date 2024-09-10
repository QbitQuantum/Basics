int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        TutorialWindow->connectKeyTyped(boost::bind(keyPressed, _1));

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        //Create the nessicary parts for a viewport
        Matrix TransformMatrix;
        TransformMatrix.setTranslate(0.0f,0.0f, 0.0f);
        TransformRecPtr CameraBeaconTransform = Transform::create();
        CameraBeaconTransform->setMatrix(TransformMatrix);

        NodeRecPtr CameraBeaconNode = Node::create();
        CameraBeaconNode->setCore(CameraBeaconTransform);

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr GeometryNode = makeTorus(.5, 2, 32, 32);

        //Make a light Node
        NodeRecPtr LightBeaconNode = makeCoredNode<Transform>();

        DirectionalLightRecPtr SceneLight = DirectionalLight::create();
        SceneLight->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
        SceneLight->setDiffuse(Color4f(0.8f,0.8f,0.8f,1.0f));
        SceneLight->setSpecular(Color4f(1.0f,1.0f,1.0f,1.0f));
        SceneLight->setOn(true);
        SceneLight->setBeacon(LightBeaconNode);

        NodeRecPtr LightNode = makeNodeFor(SceneLight);
        LightNode->addChild(GeometryNode);

        // Make Main Scene Node and add the Torus
        NodeRecPtr DefaultRootNode = Node::create();
        DefaultRootNode->setCore(Group::create());
        DefaultRootNode->addChild(LightNode);
        DefaultRootNode->addChild(LightBeaconNode);
        DefaultRootNode->addChild(CameraBeaconNode);

        //Camera
        PerspectiveCameraRecPtr DefaultCamera = PerspectiveCamera::create();
        DefaultCamera->setBeacon(CameraBeaconNode);
        DefaultCamera->setFov   (osgDegree2Rad(60.f));
        DefaultCamera->setNear  (0.1f);
        DefaultCamera->setFar   (100.f);

        //Background
        GradientBackgroundRecPtr DefaultBackground = GradientBackground::create();
        DefaultBackground->addLine(Color3f(0.0f,0.0f,0.0f), 0.0f);
        DefaultBackground->addLine(Color3f(0.0f,0.0f,1.0f), 1.0f);

        //Viewport
        ViewportRecPtr DefaultViewport = Viewport::create();
        DefaultViewport->setCamera                  (DefaultCamera);
        DefaultViewport->setRoot                    (DefaultRootNode);
        DefaultViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
        DefaultViewport->setBackground              (DefaultBackground);

        //GL Viewport Component
        LineBorderRecPtr TheGLViewportBorder = LineBorder::create();
        TheGLViewportBorder->setColor(Color4f(1.0,0.0,0.0,1.0));
        TheGLViewportBorder->setWidth(3.0);

        GLViewportRecPtr TheGLViewport = GLViewport::create();
        TheGLViewport->setPort(DefaultViewport);
        TheGLViewport->setPreferredSize(Vec2f(400.0f,400.0f));
        TheGLViewport->setBorders(TheGLViewportBorder);
        TheGLViewport->lookAt(Pnt3f(0.0f,0.0f,10.0f), //From
                              Pnt3f(0.0f,0.0f,0.0f), //At
                              Vec3f(0.0f,1.0f,0.0f)); //Up

        ButtonRecPtr ExampleButton = Button::create();

        ExampleButton->setText("Example");

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();
        MainInternalWindow->pushToChildren(TheGLViewport);
        MainInternalWindow->pushToChildren(ExampleButton);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.95f,0.95f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        // Tell the Manager what to manage
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        //Create the Documentation Foreground and add it to the viewport
        SimpleScreenDoc TheSimpleScreenDoc(&sceneManager, TutorialWindow);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "41GLViewportComponent");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}