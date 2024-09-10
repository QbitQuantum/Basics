int doMain (int argc, char **argv)
{
    osx_AllowForeground();

    // OSG init

    OSG::osgInit(argc, argv);

    // create the graph

    // beacon for camera and light
    OSG::NodeUnrecPtr b1n = OSG::Node::create();
    OSG::GroupUnrecPtr b1 = OSG::Group::create();
    b1n->setCore( b1 );

    // transformation
    OSG::NodeUnrecPtr t1n = OSG::Node::create();
    OSG::TransformUnrecPtr t1 = OSG::Transform::create();
    t1n->setCore( t1 );
    t1n->addChild( b1n );

    cam_trans = t1;

    // light

    OSG::NodeUnrecPtr dlight = OSG::Node::create();
    OSG::DirectionalLightUnrecPtr dl = OSG::DirectionalLight::create();

    dlight->setCore( dl );

    dl->setAmbient( .0, .0, .0, 1 );
    dl->setDiffuse( .8, .8, .8, .8 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);

    // root
    root = OSG::Node::create();
    OSG::GroupUnrecPtr gr1 = OSG::Group::create();

    root->setCore( gr1 );
    root->addChild( t1n );
    root->addChild( dlight );

    // Load the file

    OSG::NodeUnrecPtr file = NULL;

    if ( argc > 1 )
        file = OSG::SceneFileHandler::the()->read(argv[1]);

    if ( file == NULL )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = OSG::makeTorus( .5, 2, 16, 16 );
    }

    OSG::Thread::getCurrentChangeList()->commitChanges();
    file->updateVolume();

    OSG::Vec3f min,max;
    file->getVolume().getBounds( min, max );

    std::cout << "Volume: from " << min << " to " << max << std::endl;

    dlight->addChild( file );

    std::cerr << "Tree: " << std::endl;
    //root->dump();

    // Camera
    cam = OSG::PerspectiveCamera::create();

    cam->setBeacon( b1n );
    cam->setFov( OSG::osgDegree2Rad( 90 ) );
    cam->setNear( 0.1 );
    cam->setFar( 100000 );

    // Background
    OSG::SolidBackgroundUnrecPtr bkgnd = OSG::SolidBackground::create();

    bkgnd->setColor(OSG::Color3f(0,0,1));

    // Viewport

    vp = OSG::Viewport::create();
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

    // Action

    ract = OSG::RenderAction::create();

    // tball

    OSG::Vec3f pos;
    pos.setValues(min[0] + ((max[0] - min[0]) * 0.5), 
                  min[1] + ((max[1] - min[1]) * 0.5), 
                  max[2] + ( max[2] - min[2] ) * 1.5 );
    
    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

    OSG::Pnt3f tCenter(min[0] + (max[0] - min[0]) / 2,
                       min[1] + (max[1] - min[1]) / 2,
                       min[2] + (max[2] - min[2]) / 2);

    tball.setMode( OSG::Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( OSG::Trackball::OSGFree );
    tball.setTranslationScale(scale);
    tball.setRotationCenter(tCenter);

    // Carbon init

    // Create window
    WindowAttributes windowAttrs =
        kWindowStandardDocumentAttributes |
        kWindowLiveResizeAttribute |
        kWindowStandardHandlerAttribute;
    Rect contentRect;
    SetRect(&contentRect, 0,  0, 300, 300);
    WindowRef window;
    CreateNewWindow(kDocumentWindowClass, windowAttrs, &contentRect, &window);
    SetWindowTitleWithCFString(window, CFSTR("testWindowCarbon"));

    // Install event handler
    EventHandlerUPP eventHandlerUPP = NewEventHandlerUPP(eventHandler);
    EventTypeSpec eventList[] =
    {
        { kEventClassTextInput, kEventTextInputUnicodeForKeyEvent },
        { kEventClassMouse, kEventMouseDown },
        { kEventClassMouse, kEventMouseUp },
        { kEventClassMouse, kEventMouseDragged },
        { kEventClassWindow, kEventWindowClose },
        { kEventClassWindow, kEventWindowDrawContent },
        { kEventClassWindow, kEventWindowBoundsChanged }
    };
    InstallWindowEventHandler(window, eventHandlerUPP, GetEventTypeCount(eventList), eventList, /*this*/0, 0);

    // Initialize OpenGL
    GLint attribs[] = { AGL_RGBA, AGL_DOUBLEBUFFER, AGL_DEPTH_SIZE, 16, AGL_NONE };
    AGLPixelFormat pixelFormat = aglChoosePixelFormat(0, 0, attribs);
    if (pixelFormat == 0)
        std::cerr << "Cannot choose pixel format" << std::endl;
    AGLContext context = aglCreateContext(pixelFormat, 0);
    aglDestroyPixelFormat(pixelFormat);
    if (context == 0)
        std::cerr << "Cannot create context" << std::endl;
    aglSetDrawable(context, GetWindowPort(window));

    // Create OpenSG window
    win = OSG::CarbonWindow::create();
    win->addPort( vp );             
    win->setContext ( context );
    win->init();
    win->resize( 300, 300 );

    // Show window
    RepositionWindow(window, 0, kWindowCascadeOnMainScreen);
    ShowWindow(window);

    win->activate();

    // do some OpenGL init. Will move into State Chunks later.

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );


    // Main loop ( event dispatching )
    RunApplicationEventLoop();

    // Cleanup
    aglDestroyContext(context);
    DisposeWindow(window);
    DisposeEventHandlerUPP(eventHandlerUPP);

    ract      = NULL;
    win       = NULL;
    root      = NULL;
    file      = NULL;
    vp        = NULL;
    cam_trans = NULL;
    cam       = NULL;

    return 0;
}