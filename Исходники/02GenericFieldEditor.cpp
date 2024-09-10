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

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

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

        //Background
        SolidBackgroundRefPtr TutorialBackground = SolidBackground::create();
        TutorialBackground->setColor(Color3f(1.0,0.0,0.0));
    		    
        UndoManagerPtr TheUndoManager = UndoManager::create();
        CommandManagerPtr TheCommandManager = CommandManager::create(TheUndoManager);

        //UndoList
	    DefaultListModelRecPtr UndoRedoListModel = DefaultListModel::create();
        UndoRedoListModel->pushBack(boost::any(std::string("Top")));

	    ListRecPtr UndoRedoList = List::create();
        UndoRedoList->setPreferredSize(Vec2f(250, 300));
        UndoRedoList->setOrientation(List::VERTICAL_ORIENTATION);
	    UndoRedoList->setModel(UndoRedoListModel);

        UndoRedoList->getSelectionModel()->connectSelectionChanged(boost::bind(&handleUndoRedoListSelectionChanged, _1, TheUndoManager));

        ButtonRecPtr UndoButton = OSG::Button::create();
        UndoButton->setText("Undo");
	    UndoButton->setEnabled(false);
        UndoButton->connectActionPerformed(boost::bind(&handleUndoButtonAction, _1, TheUndoManager));
    	

        ButtonRecPtr RedoButton = OSG::Button::create();
        RedoButton->setText("Redo");
	    RedoButton->setEnabled(false);
        RedoButton->connectActionPerformed(boost::bind(&handleRedoButtonActionPerformed, _1, TheUndoManager));

        TheUndoManager->connectStateChanged(boost::bind(&handleUndoManagerStateChanged, _1, UndoButton.get(), RedoButton.get(), UndoRedoListModel.get(), TheUndoManager));

        // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
        ScrollPanelRefPtr UndoRedoScrollPanel = ScrollPanel::create();
        UndoRedoScrollPanel->setPreferredSize(Vec2f(200,200));
        UndoRedoScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        UndoRedoScrollPanel->setViewComponent(UndoRedoList);


        //Edited Label
        LabelRecPtr EditedLabel = Label::create();
        EditedLabel->setText("Can be edited");
        EditedLabel->setPreferredSize(Vec2f(100.0f,18.0f));

        //Editor Field
        LabelRecPtr TheTextEditorLabel = Label::create();
        TheTextEditorLabel->setText("Text");
        TheTextEditorLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        FieldEditorComponentRefPtr TheTextEditor = FieldEditorFactory::the()->createDefaultEditor(EditedLabel,
                                                                                                  Label::TextFieldId,
                                                                                                  TheCommandManager);
        TheTextEditor->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr ThePreferredSizeEditorLabel = Label::create();
        ThePreferredSizeEditorLabel->setText("PreferredSize");
        ThePreferredSizeEditorLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        FieldEditorComponentRefPtr ThePreferredSizeEditor =
            FieldEditorFactory::the()->createDefaultEditor(EditedLabel,
                                                           Label::PreferredSizeFieldId,
                                                           TheCommandManager);
        ThePreferredSizeEditor->setPreferredSize(Vec2f(150.0f, 20.0f));

        //Editing Panel
        LayoutRefPtr EditorPanelLayout = OSG::FlowLayout::create();
        PanelRecPtr EditorPanel = Panel::create();
        EditorPanel->setPreferredSize(Vec2f(200.0f,200.0f));
        EditorPanel->pushToChildren(TheTextEditorLabel);
        EditorPanel->pushToChildren(TheTextEditor);
        EditorPanel->pushToChildren(ThePreferredSizeEditorLabel);
        EditorPanel->pushToChildren(ThePreferredSizeEditor);
        EditorPanel->setLayout(EditorPanelLayout);

        //Undo Panel
        LabelRecPtr UndoPanelLabel = Label::create();
        UndoPanelLabel->setText("Undo Panel");
        UndoPanelLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LayoutRefPtr UndoPanelLayout = OSG::FlowLayout::create();
        PanelRecPtr UndoPanel = Panel::create();
        UndoPanel->setPreferredSize(Vec2f(300.0f,300.0f));
        UndoPanel->pushToChildren(UndoPanelLabel);
        UndoPanel->pushToChildren(UndoRedoScrollPanel);
        UndoPanel->pushToChildren(UndoButton);
        UndoPanel->pushToChildren(RedoButton);
        UndoPanel->setLayout(UndoPanelLayout);

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
        InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
        LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
        MainInternalWindow->pushToChildren(EditedLabel);
        MainInternalWindow->pushToChildren(EditorPanel);
        MainInternalWindow->pushToChildren(UndoPanel);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.95f,0.95f));
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

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);
        TutorialViewport->setBackground(TutorialBackground);

        // Show the whole Scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                    WinSize,
                                    "02GenericFieldEditor");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}