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

    DefaultDialogComponentGeneratorPtr TutorialDialogGenerator = DefaultDialogComponentGenerator::create();

    ButtonFont = osg::UIFont::create();

    beginEditCP(ButtonFont, UIFont::SizeFieldMask);
        ButtonFont->setSize(16);
    endEditCP(ButtonFont, UIFont::SizeFieldMask);

    ButtonPtr Response = osg::Button::create();
    beginEditCP(Response, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );
            Response->setMinSize(Vec2f(50, 25));
            Response->setMaxSize(Vec2f(200, 100));
            Response->setPreferredSize(Vec2f(100, 50));
            Response->setToolTipText("These buttons are for selecting a response!");

            Response->setFont(ButtonFont);
            Response->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            Response->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            Response->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    endEditCP(Response, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );

    LabelPtr LabelPrototype = Label::create();
    LabelPrototype->setAlignment(Pnt2f(0.5f,0.5f));
    LabelPrototype->setPreferredSize(Pnt2f(250.0,30.0));

    DialogInterfacePtr TutorialDialogInterface = osg::DialogInterface::create();

    beginEditCP(TutorialDialogGenerator, DefaultDialogComponentGenerator::ResponseButtonPrototypeFieldMask | DefaultDialogComponentGenerator::QuestionPrototypeFieldMask);
        TutorialDialogGenerator->setResponseButtonPrototype(Response);
        TutorialDialogGenerator->setQuestionPrototype(LabelPrototype);
    endEditCP(TutorialDialogGenerator, DefaultDialogComponentGenerator::ResponseButtonPrototypeFieldMask | DefaultDialogComponentGenerator::QuestionPrototypeFieldMask);

    TutorialDialog = osg::DialogHierarchy::create();

    beginEditCP(TutorialDialog, DialogHierarchy::DualNodeStyleFieldMask);
        TutorialDialog->setDualNodeStyle(true);
    endEditCP(TutorialDialog, DialogHierarchy::DualNodeStyleFieldMask);

    DialogPtr rootDialog = TutorialDialog->addDialog("Which do you prefer?", 0.0, NullFC, true, NullFC);

    DialogPtr RootDialogChildA = TutorialDialog->addDialog("Foreground", 0.0, NullFC, false, rootDialog);
    DialogPtr RootDialogChildB = TutorialDialog->addDialog("Background", 0.0, NullFC, false, rootDialog);
    
    DialogPtr SelectableDialogChildA = TutorialDialog->addDialog("What color would you like the forground to be?", 0.0, NullFC, true, RootDialogChildA);
    DialogPtr SelectableDialogChildB = TutorialDialog->addDialog("What object do you want to be in the background?", 0.0, NullFC, true, RootDialogChildB);

    ADialogChildA = TutorialDialog->addDialog("Blue", 0.0, NullFC, false, SelectableDialogChildA);
    ADialogChildB = TutorialDialog->addDialog("Red", 0.0, NullFC, false, SelectableDialogChildA);

    BDialogChildA = TutorialDialog->addDialog("Square", 0.0, NullFC, false, SelectableDialogChildB);
    BDialogChildB = TutorialDialog->addDialog("Sphere", 0.0, NullFC, false, SelectableDialogChildB);

    DialogPtr RestartEnd1 = TutorialDialog->addDialog("What would you like to do?", 0.0, NullFC, true, ADialogChildA);
    DialogPtr RestartEnd2 = TutorialDialog->addDialog("What would you like to do?", 0.0, NullFC, true, ADialogChildB);
    DialogPtr RestartEnd3 = TutorialDialog->addDialog("What would you like to do?", 0.0, NullFC, true, BDialogChildA);
    DialogPtr RestartEnd4 = TutorialDialog->addDialog("What would you like to do?", 0.0, NullFC, true, BDialogChildB);

    Restart1 = TutorialDialog->addDialog("Restart", 0.0, NullFC, false, RestartEnd1);
    End1 = TutorialDialog->addDialog("End", 0.0, NullFC, false, RestartEnd1);
    Restart2 = TutorialDialog->addDialog("Restart", 0.0, NullFC, false, RestartEnd2);
    End2 = TutorialDialog->addDialog("End", 0.0, NullFC, false, RestartEnd2);
    Restart3 = TutorialDialog->addDialog("Restart", 0.0, NullFC, false, RestartEnd3);
    End3 = TutorialDialog->addDialog("End", 0.0, NullFC, false, RestartEnd3);
    Restart4 = TutorialDialog->addDialog("Restart", 0.0, NullFC, false, RestartEnd4);
    End4 = TutorialDialog->addDialog("End", 0.0, NullFC, false, RestartEnd4);

    TutorialDialogListener TheTutorialDialogListener;
    rootDialog->addDialogListener(&TheTutorialDialogListener);
    RootDialogChildA->addDialogListener(&TheTutorialDialogListener);
    RootDialogChildB->addDialogListener(&TheTutorialDialogListener);
    ADialogChildA->addDialogListener(&TheTutorialDialogListener);
    ADialogChildB->addDialogListener(&TheTutorialDialogListener);
    BDialogChildA->addDialogListener(&TheTutorialDialogListener);
    BDialogChildB->addDialogListener(&TheTutorialDialogListener);
    Restart1->addDialogListener(&TheTutorialDialogListener);
    End1->addDialogListener(&TheTutorialDialogListener);
    Restart2->addDialogListener(&TheTutorialDialogListener);
    End2->addDialogListener(&TheTutorialDialogListener);
    Restart3->addDialogListener(&TheTutorialDialogListener);
    End3->addDialogListener(&TheTutorialDialogListener);
    Restart4->addDialogListener(&TheTutorialDialogListener);
    End4->addDialogListener(&TheTutorialDialogListener);

    SelectableDialogChildA->addDialogListener(&TheTutorialDialogListener);
    SelectableDialogChildB->addDialogListener(&TheTutorialDialogListener);
    RestartEnd1->addDialogListener(&TheTutorialDialogListener);
    RestartEnd2->addDialogListener(&TheTutorialDialogListener);
    RestartEnd3->addDialogListener(&TheTutorialDialogListener);
    RestartEnd4->addDialogListener(&TheTutorialDialogListener);
    
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    MainInternalWindowBackground = osg::ColorLayer::create();
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
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    beginEditCP(TutorialDialogInterface, DialogInterface::ComponentGeneratorFieldMask | DialogInterface::ParentContainerFieldMask | DialogInterface::SourceDialogHierarchyFieldMask);
        TutorialDialogInterface->setComponentGenerator(TutorialDialogGenerator);
        TutorialDialogInterface->setParentContainer(MainInternalWindow);
        TutorialDialogInterface->setSourceDialogHierarchy(TutorialDialog);
    endEditCP(TutorialDialogInterface, DialogInterface::ComponentGeneratorFieldMask | DialogInterface::ParentContainerFieldMask | DialogInterface::SourceDialogHierarchyFieldMask);

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

    TutorialDialog->start();

    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "07DialogTypeTwo");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

    osgExit();

    return 0;
}