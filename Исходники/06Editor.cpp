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


        // Make Torus Node (creates Torus in background of scene)
        NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRefPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

	    TextEditorRefPtr theTextEditor = TextEditor::create();
	    theTextEditor->setPreferredSize(Vec2f(1000,700));
        theTextEditor->setIsSplit(false);
        theTextEditor->setClipboardVisible(false);

        //Toggle Button for clipboard
        ToggleButtonRefPtr ClipboardButton = ToggleButton::create();
        ClipboardButton->setPreferredSize(Vec2f(80, 40));
        ClipboardButton->setText("Clipboard");
        ClipboardButton->connectButtonSelected(boost::bind(handleClipboardSelected,
                                                           _1,
                                                           theTextEditor.get()));
        ClipboardButton->connectButtonDeselected(boost::bind(handleClipboardDeselected,
                                                           _1,
                                                           theTextEditor.get()));
        
        //Toggle Button for split panel
        ToggleButtonRefPtr SplitButton = ToggleButton::create();
        SplitButton->setPreferredSize(Vec2f(80, 40));
        SplitButton->setText("Split");
        SplitButton->connectButtonSelected(boost::bind(handleSplitSelected,
                                                           _1,
                                                           theTextEditor.get()));
        SplitButton->connectButtonDeselected(boost::bind(handleSplitDeselected,
                                                           _1,
                                                           theTextEditor.get()));
        
        ButtonRefPtr LoadButton = Button::create();

	    LoadButton->setMinSize(Vec2f(50, 25));
        LoadButton->setMaxSize(Vec2f(200, 100));
        LoadButton->setPreferredSize(Vec2f(80, 40));
        LoadButton->setToolTipText("Click to open a file browser window");
        LoadButton->setText("Load File");

        LoadButton->connectActionPerformed(boost::bind(handleLoadButtonAction, _1, TutorialWindow.get(), theTextEditor.get()));

    	  
	    ButtonRefPtr SaveButton = Button::create();

	    SaveButton->setMinSize(Vec2f(50, 25));
        SaveButton->setMaxSize(Vec2f(200, 100));
        SaveButton->setPreferredSize(Vec2f(80, 40));
        SaveButton->setToolTipText("Click to save the currently opened file");
        SaveButton->setText("Save File");

        SaveButton->connectActionPerformed(boost::bind(handleSaveButtonAction, _1, TutorialWindow.get(),theTextEditor.get()));

        //Button Panel
        LayoutRefPtr ButtonPanelLayout = FlowLayout::create();

        PanelRecPtr ButtonPanel = Panel::createEmpty();
        ButtonPanel->setPreferredSize(Vec2f(300, 300));
        ButtonPanel->setLayout(ButtonPanelLayout);
        ButtonPanel->pushToChildren(LoadButton);
        ButtonPanel->pushToChildren(SaveButton);
        ButtonPanel->pushToChildren(SplitButton);
        ButtonPanel->pushToChildren(ClipboardButton);

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRefPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRefPtr MainInternalWindowLayout = FlowLayout::create();

        InternalWindowRefPtr MainInternalWindow = InternalWindow::create();
        //MainInternalWindow->pushToChildren(TextAreaScrollPanel);
        MainInternalWindow->pushToChildren(theTextEditor);
        MainInternalWindow->pushToChildren(ButtonPanel);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.95f,0.95f));
        //MainInternalWindow->setDrawTitlebar(true);
        //MainInternalWindow->setResizable(true);

        // Create the Drawing Surface
        UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
    	
	    TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRefPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);
    		

        // Show the whole Scene
        sceneManager.showAll();

    	
        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.95f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "06Editor");
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1, theTextEditor.get()));

        commitChanges();

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}