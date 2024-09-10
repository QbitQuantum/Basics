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

        // Create a simple Font to be used with the ExampleTextArea
        UIFontRecPtr ExampleFont = UIFont::create();
        ExampleFont->setSize(16);

        /******************************************************


          Create and edit the TextArea and determine its 
          characteristics.  A TextArea is a component 
          that allows you to enter text into the box via 
          keyboard input.  You can select text by    using 
          your mouse or pressing shift and the left and 
          right arrow keys.

          The only difference between a TextArea and
          TextField is that a TextArea can have 
          multiple lines of text 
          within it.

          -setTextColor(Color4f): Determine color of 
          text within TextArea.
          -setSelectionBoxColor(Color4f): Determine the
          color that highlighting around the 
          selected text appears.
          -setSelectionTextColor(Color4f): Determine the 
          color the selected text appears.
          -setText("TextToBeDisplayed"): Determine  
          initial text within TextArea.
          -setFont(FontName): Determine the Font 
          used within TextArea
          -setSelectionStart(StartCharacterNumber):
          Determine the character which the 
          selection will initially start after.
          -setSelectionEnd(EndCharacterNumber): 
          Determine the character which the 
          selection will end before.
          -setCaretPosition(Location): Determine the 
          location of the Caret within the TextArea.
Note: this does not do too much
currently because the only way 
to cause the TextArea to gain focus is
to click within it, causing the 
Caret to move.

         ******************************************************/

        // Create a TextArea component
        TextAreaRecPtr ExampleTextArea = TextArea::create();

        ExampleTextArea->setPreferredSize(Vec2f(300, 200));
        ExampleTextArea->setMinSize(Vec2f(300, 200));
        ExampleTextArea->setTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
        ExampleTextArea->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
        ExampleTextArea->setSelectionTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        // Determine the font and initial text
        ExampleTextArea->setText("What");
        ExampleTextArea->setFont(ExampleFont);
        // This will select the "a" from above
        ExampleTextArea->setSelectionStart(2);
        ExampleTextArea->setSelectionEnd(3);
        ExampleTextArea->setCaretPosition(2);
        //ExampleTextArea->setLineWrap(false);

        // Create a ScrollPanel
        ScrollPanelRecPtr TextAreaScrollPanel = ScrollPanel::create();
        TextAreaScrollPanel->setPreferredSize(Vec2f(200,200));
        TextAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        // Add the TextArea to the ScrollPanel so it is displayed
        TextAreaScrollPanel->setViewComponent(ExampleTextArea);


        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(TextAreaScrollPanel);
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

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "22TextArea");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}