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

        /******************************************************

          Create a RotatedComponent.
          -setAngle(Angle, in radians): Determine
          the angle the Component initially
          is rotated.
          -setInternalComponent(Component): 
          Determine what Component will
          be rotated.
          -setResizePolicy(RotatedComponent::ENUM):
          Takes NO_RESIZING, RESIZE_TO_MIN, or
          RESIZE_TO_MAX arguments.

         ******************************************************/    

        RotatedComponentRecPtr TheRotatedComponent = RotatedComponent::create();
        // Define PI
        Real32 PI(3.14159);
        TheRotatedComponent->setAngle(PI/4);
        ComponentRecPtr InnerPanel = createPanel();
        TheRotatedComponent->setInternalComponent(InnerPanel);
        TheRotatedComponent->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);

        /******************************************************

          Create a ToggleButton which can 
          be used to start and stop the 
          Button from rotating.

            Note: due to the way FlowLayout works
            you will notice that this ToggleButton
            will move as well.  In cases where
            a Rotating Component is used, an 
            alternate Layout may be preferred
            to prevent other Components from 
            moving as well.  This is 
            intentionally left this way to 
            illustrate why this might be the case.
            A SplitPanel with fixed divider for 
            example would prevent the ToggleButton
            from moving, while still allowing the 
            Panel to move freely.

         ******************************************************/    
        ToggleButtonRecPtr RotateControlButton = ToggleButton::create();
        RotateControlButton->setText("Start Rotating");
        RotateControlButton->setPreferredSize(Vec2f(100.0f, 29.0f));

        RotateControlButton->connectButtonSelected(boost::bind(handleButtonSelected, _1,
                                                               TutorialWindow.get(),
                                                               TheRotatedComponent.get()));
        RotateControlButton->connectButtonDeselected(boost::bind(handleButtonDeselected, _1,
                                                                 TutorialWindow.get(),
                                                                 TheRotatedComponent.get()));

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(TheRotatedComponent);
        MainInternalWindow->pushToChildren(RotateControlButton);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.8f,0.8f));
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
                                   "30RotatedComponent");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}