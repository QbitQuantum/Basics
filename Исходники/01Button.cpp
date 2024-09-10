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
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);


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

        /******************************************************

          Create an Button Component and
          a simple Font.
          See 17Label_Font for more
          information about Fonts.

         ******************************************************/
        ButtonRefPtr ExampleButton = OSG::Button::create();

        UIFontRefPtr ExampleFont = OSG::UIFont::create();
        ExampleFont->setSize(16);

        /******************************************************

          Edit the Button's characteristics.
            Note: the first 4 functions can
            be used with any Component and 
            are not specific to Button.

            -setMinSize(Vec2f): Determine the 
            Minimum Size of the Component.
            Some Layouts will automatically
            resize Components; this prevents
            the Size from going below a
            certain value.
            -setMaxSize(Vec2f): Determine the 
            Maximum Size of the Component.
            -setPreferredSize(Vec2f): Determine
            the Preferred Size of the Component.
            This is what the Component will
            be displayed at unless changed by
            another Component (such as a 
            Layout).
            -setToolTipText("Text"): Determine
            what text is displayed while
            Mouse is hovering above Component.
            The word Text will be displayed
            in this case.

            Functions specfic to Button:
            -setText("DesiredText"): Determine 
            the Button's text.  It will read
            DesiredText in this case.
            -setFont(FontName): Determine the 
            Font to be used on the Button.
            -setTextColor(Color4f): Determine the
            Color for the text.
            -setRolloverTextColor(Color4f): Determine
            what the text Color will be when
            the Mouse Cursor is above the 
            Button.
            -setActiveTextColor(Color4f): Determine
            what the text Color will be when
            the Button is pressed (denoted by
            Active).
            -setAlignment(Vec2f):
            Determine the Vertical Alignment
            of the text.  The value is 
            in [0.0, 1.0].

         ******************************************************/
        ExampleButton->setMinSize(Vec2f(50, 25));
        ExampleButton->setMaxSize(Vec2f(200, 100));
        ExampleButton->setPreferredSize(Vec2f(100, 50));
        ExampleButton->setToolTipText("Button 1 ToolTip");

        ExampleButton->setText("Button 1");
        ExampleButton->setFont(ExampleFont);
        ExampleButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
        ExampleButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
        ExampleButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
        ExampleButton->setAlignment(Vec2f(1.0,0.0));

        // Create an Action and assign it to ExampleButton
        // This Class is defined above, and will cause the output
        // window to display "Button 1 Action" when pressed
        ExampleButton->connectActionPerformed(boost::bind(actionPerformed, _1));

        /******************************************************

          Create a ToggleButton and determine its 
          characteristics.  ToggleButton inherits
          off of Button, so all characteristsics
          used above can be used with ToggleButtons
          as well.

          The only difference is that when pressed,
          ToggleButton remains pressed until pressed 
          again.

          -setSelected(bool): Determine whether the 
          ToggleButton is Selected (true) or
          deselected (false).  

         ******************************************************/
        ToggleButtonRefPtr ExampleToggleButton = OSG::ToggleButton::create();

        ExampleToggleButton->setSelected(false);
        ExampleToggleButton->setText("ToggleMe");
        ExampleToggleButton->setToolTipText("Toggle Button ToolTip");

        //Button with Image
        ButtonRefPtr ExampleDrawObjectButton = OSG::Button::create();
        ExampleDrawObjectButton->setDrawObjectToTextAlignment(Button::ALIGN_DRAW_OBJECT_RIGHT_OF_TEXT);
        ExampleDrawObjectButton->setText("Icon");

        ExampleDrawObjectButton->setImage(std::string("./Data/Icon.png"));
        ExampleDrawObjectButton->setActiveImage(std::string("./Data/Icon.png"));
        ExampleDrawObjectButton->setFocusedImage(std::string("./Data/Icon.png"));
        ExampleDrawObjectButton->setRolloverImage(std::string("./Data/Icon.png"));
        ExampleDrawObjectButton->setDisabledImage(std::string("./Data/Icon.png"));

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
        InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
        LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
        MainInternalWindow->pushToChildren(ExampleButton);
        MainInternalWindow->pushToChildren(ExampleToggleButton);
        MainInternalWindow->pushToChildren(ExampleDrawObjectButton);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
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

        //Attach key controls

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "01Button");

        commitChanges();

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}