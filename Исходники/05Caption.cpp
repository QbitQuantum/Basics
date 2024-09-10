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
    TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);

    //Create Start and stop buttons for the caption
    ButtonPtr StartButton = osg::Button::create();
    ButtonPtr StopButton = osg::Button::create();
    ButtonPtr PauseButton = osg::Button::create();

    UIFontPtr ButtonFont = osg::UIFont::create();

    beginEditCP(ButtonFont, UIFont::SizeFieldMask);
        ButtonFont->setSize(16);
    endEditCP(ButtonFont, UIFont::SizeFieldMask);
    
    beginEditCP(StartButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);
            StartButton->setMinSize(Vec2f(50, 25));
            StartButton->setMaxSize(Vec2f(200, 100));
            StartButton->setPreferredSize(Vec2f(100, 50));
            StartButton->setToolTipText("This will start playing the caption!");

            StartButton->setText("START");
            StartButton->setFont(ButtonFont);
            StartButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            StartButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            StartButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            StartButton->setAlignment(Vec2f(0.25,0.5));
    endEditCP(StartButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);

    beginEditCP(StopButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);
            StopButton->setMinSize(Vec2f(50, 25));
            StopButton->setMaxSize(Vec2f(200, 100));
            StopButton->setPreferredSize(Vec2f(100, 50));
            StopButton->setToolTipText("This will stop the caption and reset it!");

            StopButton->setText("STOP");
            StopButton->setFont(ButtonFont);
            StopButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            StopButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            StopButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            StopButton->setAlignment(Vec2f(0.75,0.5));
    endEditCP(StopButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);

    beginEditCP(PauseButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);
            PauseButton->setMinSize(Vec2f(50, 25));
            PauseButton->setMaxSize(Vec2f(200, 100));
            PauseButton->setPreferredSize(Vec2f(100, 50));
            PauseButton->setToolTipText("This will Pause the caption!");

            PauseButton->setText("PAUSE");
            PauseButton->setFont(ButtonFont);
            PauseButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            PauseButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            PauseButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            PauseButton->setAlignment(Vec2f(0.5,0.5));
    endEditCP(PauseButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);


    StartButtonActionListener TheStartButtonActionListener;
    StartButton->addActionListener(&TheStartButtonActionListener);

    StopButtonActionListener TheStopButtonActionListener;
    StopButton->addActionListener(&TheStopButtonActionListener);

    PauseButtonActionListener ThePauseButtonActionListener;
    PauseButton->addActionListener(&ThePauseButtonActionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);


    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();



    PanelPtr CaptionContainer = osg::Panel::create();

    beginEditCP(CaptionContainer, Panel::PreferredSizeFieldMask | Panel::LayoutFieldMask);
        CaptionContainer->setPreferredSize(Pnt2f(250.0,30.0));
        CaptionContainer->setLayout(MainInternalWindowLayout);
    endEditCP(CaptionContainer, Panel::PreferredSizeFieldMask | Panel::LayoutFieldMask);

    //Initialize the Sound Manager
    SoundManager::the()->attachUpdateProducer(TutorialWindowEventProducer);

    TutorialSound = SoundManager::the()->createSound();
    beginEditCP(TutorialSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask);
        TutorialSound->setFile(Path("./Data/captionSoundFile.ogg"));
        TutorialSound->setVolume(1.0);
        TutorialSound->setStreaming(true);
        TutorialSound->setLooping(0);
    endEditCP(TutorialSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask);

    // Create the Caption
    TutorialCaption = osg::Caption::create();

    //Add the segments of text to be displayed
    TutorialCaption->captionSegment("Listeners can be used for a variety",1.7,3.4);
    TutorialCaption->captionSegment("of different applications.",3.4,4.7);
    TutorialCaption->captionSegment("In this tutorial we will",5.0,6.35);
    TutorialCaption->captionSegment("simply be changing the background though.",6.35,8.0);
    TutorialCaption->captionSegment("First we will change the",8.8,10.2);
    TutorialCaption->captionSegment("torus on screen to a sphere.",10.2,11.75);
    TutorialCaption->captionSegment("By timing things correctly we can make",12.7,14.6);
    TutorialCaption->captionSegment("the changes right as the word is spoken.",14.6,16.75);
    TutorialCaption->captionSegment("Such as changing the sphere to a cube",17.3,20.0);
    TutorialCaption->captionSegment("but personally I would prefer",20.33,21.65);
    TutorialCaption->captionSegment("the background to be blank.",21.65,22.8);
    TutorialCaption->captionSegment("Much better!",23.8,25.0);


    //Add the tutorial Caption Listener to the Caption that was set up for the tutorial
    TutorialCaptionListener TheCaptionListener;
    TutorialCaption->addCaptionListener(&TheCaptionListener);

    //Create the Caption component Generator
    TutorialCapGen = DefaultCaptionComponentGenerator::create();

    TutorialCaption->attachWindowEventProducer(TutorialWindowEventProducer);
    beginEditCP(TutorialCaption, Caption::ParentContainerFieldMask | Caption::ComponentGeneratorFieldMask | Caption::CaptionDialogSoundFieldMask);
        TutorialCaption->setParentContainer(CaptionContainer);
        TutorialCaption->setComponentGenerator(TutorialCapGen);
        TutorialCaption->setCaptionDialogSound(TutorialSound);
    endEditCP(TutorialCaption, Caption::ParentContainerFieldMask | Caption::ComponentGeneratorFieldMask | Caption::CaptionDialogSoundFieldMask);


    //Create and modify the Label prototype that will be used for the caption
    LabelPtr LabelPrototype = Label::create();
    LabelPrototype->setAlignment(Pnt2f(0.5f,0.5f));
    LabelPrototype->setPreferredSize(Pnt2f(250.0,30.0));

    //Add the prototype to the Generator for use
    beginEditCP(TutorialCapGen, DefaultCaptionComponentGenerator::CaptionSegmentPrototypeFieldMask);
        TutorialCapGen->setCaptionSegmentPrototype(LabelPrototype);
    endEditCP(TutorialCapGen, DefaultCaptionComponentGenerator::CaptionSegmentPrototypeFieldMask);
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    MainInternalWindow = osg::InternalWindow::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
	   MainInternalWindow->getChildren().push_back(CaptionContainer);
	   MainInternalWindow->getChildren().push_back(StartButton);
	   MainInternalWindow->getChildren().push_back(StopButton);
       MainInternalWindow->getChildren().push_back(PauseButton);
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
    SoundManager::the()->setCamera(mgr->getCamera());


    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "05Caption");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();


    osgExit();

    return 0;
}