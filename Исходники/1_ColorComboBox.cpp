// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    //TutorialKeyListener TheKeyListener;
    //TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr graphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************

      Create the DefaultMutableComboBoxModel and
      add Elements to it (several Colors
      in this case).  These will be the data
      values shown in the ComboBox.

     ******************************************************/   

    DefaultMutableComboBoxModelRefPtr ExampleComboBoxModel = DefaultMutableComboBoxModel::create();
    ExampleComboBoxModel->addElement(boost::any(Color4f(1.0,0.0,0.0,1.0)));
    ExampleComboBoxModel->addElement(boost::any(Color4f(0.0,1.0,0.0,1.0)));
    ExampleComboBoxModel->addElement(boost::any(Color4f(0.0,0.0,1.0,1.0)));
    ExampleComboBoxModel->addElement(boost::any(Color4f(0.0,0.0,0.0,1.0)));
	ExampleComboBoxModel->addElement(boost::any(Color4f(1.0,1.0,1.0,1.0)));
	ExampleComboBoxModel->addElement(boost::any(std::string("More Colors")));


    /******************************************************

      Create an editable ComboBox.  A ComboBox 
      has a Model just like various other 
      Components.  

     ******************************************************/   

	ColorChooserComboBoxComponentGeneratorRefPtr TheColorChooserComboBoxComponentGenerator = ColorChooserComboBoxComponentGenerator::create();
	
    //Create the ComboBox
    ComboBoxRefPtr ExampleComboBox = ComboBox::create();

    // Set the Model created above to the ComboBox
    ExampleComboBox->setModel(ExampleComboBoxModel);
	ExampleComboBox->setCellGenerator(TheColorChooserComboBoxComponentGenerator);
	ExampleComboBox->setEditable(false);


    // Determine where the ComboBox starts
    ExampleComboBox->setSelectedIndex(0);


	// Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleComboBox);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);

    //Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
    TutorialDrawingSurface->setGraphics(graphics);
    TutorialDrawingSurface->setEventProducer(TutorialWindow);

    TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr foreground = OSG::UIForeground::create();

    foreground->setDrawingSurface(TutorialDrawingSurface);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr viewport = mgr->getWindow()->getPort(0);
    viewport->addForeground(foreground);

    // Show the whole scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "33_2_ColorComboBox");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}