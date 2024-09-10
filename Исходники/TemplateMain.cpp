int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
										
    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();
    /******************************************************

                 Create an Button Component and
                 a simple Font.
                 See 17Label_Font for more
                 information about Fonts.

    ******************************************************/
    ButtonPtr ExampleButton = osg::Button::create();

    UIFontPtr ExampleFont = osg::UIFont::create();
    beginEditCP(ExampleFont, UIFont::SizeFieldMask);
        ExampleFont->setSize(16);
    endEditCP(ExampleFont, UIFont::SizeFieldMask);

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
    beginEditCP(ExampleButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);
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
    endEditCP(ExampleButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);
            
    // Create an ActionListener and assign it to ExampleButton
    // This Class is defined above, and will cause the output
    // window to display "Button 1 Action" when pressed
    ExampleButtonActionListener TheExampleButtonActionListener;
    ExampleButton->addActionListener(&TheExampleButtonActionListener);

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
    ToggleButtonPtr ExampleToggleButton = osg::ToggleButton::create();
    
    beginEditCP(ExampleToggleButton, ToggleButton::SelectedFieldMask | ToggleButton::TextFieldMask | ToggleButton::ToolTipTextFieldMask);
        ExampleToggleButton->setSelected(false);
        ExampleToggleButton->setText("ToggleMe");
        ExampleToggleButton->setToolTipText("Toggle Button ToolTip");
    endEditCP(ExampleToggleButton, ToggleButton::SelectedFieldMask | ToggleButton::TextFieldMask | ToggleButton::ToolTipTextFieldMask);

    //Button with Image
    ButtonPtr ExampleDrawObjectButton = osg::Button::create();
    beginEditCP(ExampleDrawObjectButton, Button::DrawObjectToTextAlignmentFieldMask | Button::TextFieldMask);
	    ExampleDrawObjectButton->setDrawObjectToTextAlignment(Button::ALIGN_DRAW_OBJECT_RIGHT_OF_TEXT);
        ExampleDrawObjectButton->setText("Icon");
    endEditCP(ExampleDrawObjectButton, Button::DrawObjectToTextAlignmentFieldMask | Button::TextFieldMask);

    ExampleDrawObjectButton->setImage(std::string("Data/Icon.png"));
    ExampleDrawObjectButton->setActiveImage(std::string("Data/Icon.png"));
    ExampleDrawObjectButton->setFocusedImage(std::string("Data/Icon.png"));
    ExampleDrawObjectButton->setRolloverImage(std::string("Data/Icon.png"));
    ExampleDrawObjectButton->setDisabledImage(std::string("Data/Icon.png"));

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleButton);
       MainInternalWindow->getChildren().push_back(ExampleToggleButton);
       MainInternalWindow->getChildren().push_back(ExampleDrawObjectButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);
	
	// Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);

    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "01RubberBandCamera");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

    osgExit();

    return 0;
}