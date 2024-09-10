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


        // Create a simple Font to be used with the PasswordField
        UIFontRecPtr ExampleFont = UIFont::create();
        ExampleFont->setSize(16);

        /******************************************************


          Create and edit a PasswordField.

          A PasswordField is a TextField 
          which allows for text to be
          entered secretly.

          -setEchoCar("char"): Determine
          which character replaces text in the 
          PasswordField.

          See 16TextField for more information.

         ******************************************************/

        TextFieldRecPtr ExampleTextField = TextField::create();
        ExampleTextField->setText("");
        ExampleTextField->setEmptyDescText("username");
        ExampleTextField->setPreferredSize(Vec2f(130.0f,ExampleTextField->getPreferredSize().y()));

        PasswordFieldRecPtr ExamplePasswordField = PasswordField::create();

        ExamplePasswordField->setPreferredSize(Vec2f(130, ExamplePasswordField->getPreferredSize().y()));
        ExamplePasswordField->setTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
        ExamplePasswordField->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
        ExamplePasswordField->setSelectionTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        //ExamplePasswordField->setText("Text");
        // "Text" will be replaced by "####" in the PasswordField
        ExamplePasswordField->setEchoChar("#");
        ExamplePasswordField->setEditable(true);
        ExamplePasswordField->setFont(ExampleFont);
        ExamplePasswordField->setSelectionStart(2);
        ExamplePasswordField->setSelectionEnd(3);
        ExamplePasswordField->setAlignment(Vec2f(0.0,0.5));

        ExamplePasswordField->setEmptyDescText("password");

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        FlowLayoutRecPtr MainInternalWindowLayout = FlowLayout::create();
        MainInternalWindowLayout->setOrientation(FlowLayout::VERTICAL_ORIENTATION);

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleTextField);
        MainInternalWindow->pushToChildren(ExamplePasswordField);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
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
                                   "24PasswordField");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}