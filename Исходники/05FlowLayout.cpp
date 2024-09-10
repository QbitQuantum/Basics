int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

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
            
            Create and edit a few Button Components. 

    ******************************************************/
    ButtonRefPtr ExampleButton1 = OSG::Button::create();
    ButtonRefPtr ExampleButton2 = OSG::Button::create();
    ButtonRefPtr ExampleButton3 = OSG::Button::create();
    ButtonRefPtr ExampleButton4 = OSG::Button::create();
    ButtonRefPtr ExampleButton5 = OSG::Button::create();
    ButtonRefPtr ExampleButton6 = OSG::Button::create();

        ExampleButton1->setPreferredSize(Vec2f(200, 50));

        ExampleButton4->setPreferredSize(Vec2f(50, 50));

    /******************************************************

        Create Flow Layout.  Flow Layout arranges objects
        automatically within the Frame, so that depending 
        on Frame size, the objects may appear in a vertical
        line, horizontal line, or multiple lines.  Objects 
        fill from the upper left hand corner of the Frame
        across, then down (when the line becomes full) while
        arranged Horizontally, or from the upper left hand
        corner across when arranged Vertically, starting a 
        new column when necessary.

        You can experiment with this by changing the window 
        size, changing the orientation, changing the 
        PreferredSize of the Buttons, or adding more 
		Buttons to the view.

        Note that if the Frame is too small or resized
		too much, the FlowLayout will become slightly
		distorted.  For Layouts which will often
		be dynamically changed, FlowLayout is not
		the best choice.
	
		-setHorizontalGap(int): Determine the Horizontal
			gap in pixels between Components in 
			FlowLayout.
		-setVerticalGap(int): Determine the Vertical
			gap in pixels between Components in 
			FlowLayout.
		-setOrientation(ENUM): Determine whether the
			Layout is arranged Vertically or
			Horizontally.  Takes HORIZONTAL_ORIENTATION
			or VERTICAL_ORIENTATION arguments.
		-setMajorAxisAlignment(ENUM): Determines
			the alignment of the entire Layout 
			within its ComponentContainer.  See below.
		-setMinorAxistAlignment(ENUM): Determines
			the alignment of Components within
			the Layout.  See below.

		Both of the last two functions take the
		following arguments: AXIS_MAX_ALIGNMENT, 
		AXIS_CENTER_ALIGNMENT, and AXIS_MIN_ALIGNMENT.
		MAX puts it to the bottom/right, CENTER
		centers it, and MIN puts it to the
		top/left (for Vertical/Horizontal as
		set above, respectively).

    ******************************************************/
    FlowLayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
        MainInternalWindowLayout->setHorizontalGap(3.0f);
        MainInternalWindowLayout->setVerticalGap(3.0f);
		MainInternalWindowLayout->setOrientation(FlowLayout::VERTICAL_ORIENTATION);
        MainInternalWindowLayout->setMajorAxisAlignment(0.5f);
        MainInternalWindowLayout->setMinorAxisAlignment(1.0f);
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(ExampleButton1);
       MainInternalWindow->pushToChildren(ExampleButton2);
       MainInternalWindow->pushToChildren(ExampleButton3);
       MainInternalWindow->pushToChildren(ExampleButton4);
       MainInternalWindow->pushToChildren(ExampleButton5);
       MainInternalWindow->pushToChildren(ExampleButton6);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
	   // Add a 10 pixel "padding" inside the MainFrame
       MainInternalWindow->setAllInsets(10);

    //Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "05FlowLayout");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}