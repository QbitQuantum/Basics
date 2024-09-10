int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    /******************************************************

             Add MouseListeners and WindowListeners
             to the WindowEvent.

    ******************************************************/

    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseListener1 BasicListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(90, 270, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();


    LoadButton = Button::create();

    LoadButton->setMinSize(Vec2f(50, 25));
    LoadButton->setMaxSize(Vec2f(200, 100));
    LoadButton->setPreferredSize(Vec2f(100, 50));
    LoadButton->setToolTipText("Click to open a file browser window");
    LoadButton->setText("Load File");

    LoadButton->addActionListener(&BasicListener);

    SaveButton = Button::create();

    SaveButton->setMinSize(Vec2f(50, 25));
    SaveButton->setMaxSize(Vec2f(200, 100));
    SaveButton->setPreferredSize(Vec2f(100, 50));
    SaveButton->setToolTipText("Click to save the currently opened file");
    SaveButton->setText("Save File");

    SaveButton->addActionListener(&BasicListener);

    theTextEditor = TextEditor::create();
    theTextEditor->setPreferredSize(Vec2f(600,400));

    /*

    UIFontRefPtr _Font = UIFont::create();
    _Font->setFamily("SANS");
    _Font->setGap(3);
    _Font->setGlyphPixelSize(46);
    _Font->setSize(15);
    _Font->setTextureWidth(0);
    _Font->setStyle(TextFace::STYLE_PLAIN);

    ExampleTextDomArea->setPreferredSize(Vec2f(600, 400));
    ExampleTextDomArea->setWrapStyleWord(false);
    ExampleTextDomArea->setMinSize(Vec2f(600,400));
    ExampleTextDomArea->setFont(_Font);

    ExampleAdvancedTextDomArea = OSG::AdvancedTextDomArea::create();
    ExampleAdvancedTextDomArea->setPreferredSize(Vec2f(600,400));
    ExampleAdvancedTextDomArea->setMinSize(Vec2f(600,400));
    ExampleAdvancedTextDomArea->setGutterVisible(true);
    ExampleAdvancedTextDomArea->pushToChildren(ExampleTextDomArea);
    ExampleAdvancedTextDomArea->setLayout(LayoutRefPtr(OSG::FlowLayout::create()));
    ExampleAdvancedTextDomArea->setPreferredSize(Vec2f(600,400));
    ExampleAdvancedTextDomArea->setMinSize(Vec2f(600,400));

    ScrollPanelRefPtr TextAreaScrollPanel = ScrollPanel::create();
    TextAreaScrollPanel->setPreferredSize(Vec2f(600,400));
    TextAreaScrollPanel->setMinSize(Vec2f(600,400));
    TextAreaScrollPanel->setViewComponent(ExampleAdvancedTextDomArea);

    */

    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(theTextEditor);
    MainInternalWindow->pushToChildren(LoadButton);
    MainInternalWindow->pushToChildren(SaveButton);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
    MainInternalWindow->setDrawTitlebar(true);
    MainInternalWindow->setResizable(false);


    /******************************************************

             The Drawing Surface is created the
             same as with previous Tutorials
             (however the MainInternalWindow is created
             in a function below).

    ******************************************************/

    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
    TutorialDrawingSurface->setGraphics(TutorialGraphics);
    TutorialDrawingSurface->setEventProducer(TutorialWindow);

    TutorialDrawingSurface->openWindow(MainInternalWindow);

    /******************************************************

            Create the 3D UIRectangle.  This allows
            the DrawingSurface to be rotated relative
            to the screen, allowing a 3D aspect to
            the DrawingSurface.  The Surface
            can still be interacted with, so Buttons,
            Menus, etc. all will still function
            normally.

            -setPoint(Pnt3f): Determine the location
                of the UIRectangle in 3D space.  Keep
                in mind that (0,0,0) is located
                directly in the center of the sceen.
                (For our purposes it is the center
                of the tori.) The point is located
                on the lower left corner of the
                rectangle.
            -setWidth(float): Determine the Width
                of the UIRectangle.  This may
                physically appear different depending
                on where the UIRectangle is placed
                as above (due to it being located
                further away, etc).
            -setHeight(float): Determine the Height
                of the UIRectangle.  This may
                physically appear different depending
                on where the UIRectangle is placed
                as above (due to it being located
                further away, etc).
            -setDrawingSurface(DrawingSurface):
                Determine what DrawingSurface is
                drawn on the UIRectangle.  This
                will typically be the main
                DrawingSurface, however, multiple
                DrawingSurfaces can be used with
                multiple UIRectangles.


    ******************************************************/

    //Make A 3D Rectangle to draw the UI on
    UIRectangleRefPtr ExampleUIRectangle = UIRectangle::create();
    ExampleUIRectangle->setPoint(Pnt3f(-400,-400,200));
    ExampleUIRectangle->setWidth(800.0);
    ExampleUIRectangle->setHeight(800.0);
    ExampleUIRectangle->setDrawingSurface(TutorialDrawingSurface);

    /******************************************************

            Because the previous Tutorials used a
            Viewport to view the scene, which is
            no longer being used, the UIRectangle
            must be added to the scene for it to
            be displayed (identical to how the
            Torus is added).

            First, create a Node, and set its
            core to be the UIRectangle.  Then,
            add that to the scene Node which
            is created above.  This scene is
            then set as the Root for the view.
            It is possible to change this Root
            to be just the UIRectangle (as
            commented out below).

    ******************************************************/
    NodeRefPtr ExampleUIRectangleNode = OSG::Node::create();
    ExampleUIRectangleNode->setCore(ExampleUIRectangle);

    // Add the UIRectangle as a child to the scene
    scene->addChild(ExampleUIRectangleNode);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);
    //mgr->setRoot(ExampleUIRectangleNode);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "3DNotepad!!");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}