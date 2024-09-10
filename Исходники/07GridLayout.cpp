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

        Create Grid Layout.  Grid Layout arranges the 
        objects in a grid, with user specified rows, 
        columns, and gap size (conceptually imagine that
        an invisible grid is drawn, and components are 
        placed into that grid one per "box").

        Objects within the Grid Layout fill from left
        to right, and top to bottom, filling in each space
        sequentially.  The Grid Layout "boxes" are each the 
        same size as the largest object within the Layout. 
        
        Smaller objects are automatically resized to fit 
        this size unless they have Max/Min sizes assigned
        (similar to Box Layout).

        You can experiment with this by changing the size of 
        the Buttons as shown in 01Button, editing the Max/Min
        size of the Buttons, or adding more Buttons to the 
        scene.

        Note that if the Frame is too small, the objects will 
        appear out of the Frame background.

		-setRows(int): Determine the number of rows
			in the Layout.
		-setColumns(int): Determine the number of
			columns in the Layout.
		-setHorizontalGap(int): Determine the number
			of pixels between each column.
		setVerticalGap(int): Determine the number
			of pixels between each row.


    ******************************************************/

    GridLayoutRefPtr MainInternalWindowLayout = OSG::GridLayout::create();

        MainInternalWindowLayout->setRows(3);
        MainInternalWindowLayout->setColumns(2);
        MainInternalWindowLayout->setHorizontalGap(4);
        MainInternalWindowLayout->setVerticalGap(4);


    /******************************************************
            
             Create and edit some Button Components.

			 Note that as with BoxLayout, Components
			 are resized to fit their respective
			 grid boxes.  Unless a MaxSize is set,
			 this will be the case.  This will
			 override even PreferredSizes (see
			 ExampleButton3).

    ******************************************************/

    ButtonRefPtr ExampleButton1 = OSG::Button::create();
    ButtonRefPtr ExampleButton2 = OSG::Button::create();
    ButtonRefPtr ExampleButton3 = OSG::Button::create();
    ButtonRefPtr ExampleButton4 = OSG::Button::create();
    ButtonRefPtr ExampleButton5 = OSG::Button::create();
    ButtonRefPtr ExampleButton6 = OSG::Button::create();

        ExampleButton1->setPreferredSize(Vec2f(50,50));
        ExampleButton1->setMaxSize(Vec2f(50,50));			//if MaxSize is commented out, this button then will revert to being the same size as the others in the grid.

         ExampleButton2->setPreferredSize(Vec2f(200,100));	//<----
															//    |
         ExampleButton3->setPreferredSize(Vec2f(50,100));		//Notice that even though these two differ in size they appear the same on the grid


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
      
    // Create the Drawing Surface
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
            "07GridLayout");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}