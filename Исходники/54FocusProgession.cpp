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

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

        // Make Torus Node (creates Torus in background of scene)
        NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        ButtonRefPtr ExampleButton = OSG::Button::create();
        ExampleButton->setMinSize(Vec2f(50, 25));
        ExampleButton->setMaxSize(Vec2f(200, 100));
        ExampleButton->setPreferredSize(Vec2f(100, 50));
        ExampleButton->setText("Button 1");

        // Create an ActionListener and assign it to ExampleButton
        // This Class is defined above, and will cause the output
        // window to display "Button 1 Action" when pressed
        ExampleButton->connectActionPerformed(boost::bind(actionPerformed, _1));

        //Toggle Button
        ToggleButtonRefPtr ExampleToggleButton = OSG::ToggleButton::create();
        ExampleToggleButton->setSelected(false);
        ExampleToggleButton->setText("ToggleMe");


        //Text Field
        TextFieldRefPtr ExampleTextField = OSG::TextField::create();
        
        //Password Field
        PasswordFieldRefPtr ExamplePasswordField = OSG::PasswordField::create();

        LayoutRefPtr MainLayout = OSG::FlowLayout::create();

        //Panel
        PanelRecPtr ExamplePanel = Panel::create();
        ExamplePanel->setPreferredSize(Vec2f(200.0f,200.0f));
        ExamplePanel->setLayout(MainLayout);
        ExamplePanel->pushToChildren(ExampleTextField);
        ExamplePanel->pushToChildren(ExamplePasswordField);

        //Text Field 2
        TextFieldRefPtr ExampleTextField2 = OSG::TextField::create();

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleButton);
        MainInternalWindow->pushToChildren(ExampleToggleButton);
        MainInternalWindow->pushToChildren(ExamplePanel);
        MainInternalWindow->pushToChildren(ExampleTextField2);

        MainInternalWindow->setLayout(MainLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);

        // Create the Drawing Surface
        UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        //Create the Documentation Foreground and add it to the viewport
        SimpleScreenDoc TheSimpleScreenDoc(&sceneManager, TutorialWindow);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5f);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "54FocusProgession");

        commitChanges();

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}