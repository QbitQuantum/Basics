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
        /******************************************************

          Create an Button Component and
          a simple Font.
          See 17Label_Font for more
          information about Fonts.

         ******************************************************/

        LineBorderRecPtr ChangableBorder = LineBorder::create();
        ChangableBorder->setColor(Color4f(0.0,0.0,0.0,1.0));

        ColorLayerRecPtr ChangableBackground = ColorLayer::create();
        ChangableBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

        LabelRecPtr ChangableLabel = Label::create();

        ChangableLabel->setText("Changable");
        ChangableLabel->setBorders(ChangableBorder);
        ChangableLabel->setBackgrounds(ChangableBackground);

        //Command Buttons
        UndoManagerPtr TheUndoManager = UndoManager::create();

        CommandManagerPtr TheCommandManager = CommandManager::create(TheUndoManager);
        ButtonRecPtr BorderRedButton = Button::create();
        BorderRedButton->setText("Border Red");
        BorderRedButton->setPreferredSize(Vec2f(85, 20));
        BorderRedButton->connectActionPerformed(boost::bind(handleSetBorderColorAction,
                                                            _1,
                                                            TheCommandManager,
                                                            ChangableBorder.get(),
                                                            Color4f(1.0,0.0,0.0,1.0)));

        ButtonRecPtr BorderGreenButton = Button::create();
        BorderGreenButton->setText("Border Green");
        BorderGreenButton->setPreferredSize(Vec2f(85, 20));
        BorderGreenButton->connectActionPerformed(boost::bind(handleSetBorderColorAction,
                                                            _1,
                                                            TheCommandManager,
                                                            ChangableBorder.get(),
                                                            Color4f(0.0,1.0,0.0,1.0)));

        ButtonRecPtr BorderBlueButton = Button::create();
        BorderBlueButton->setText("Border Blue");
        BorderBlueButton->setPreferredSize(Vec2f(85, 20));
        BorderBlueButton->connectActionPerformed(boost::bind(handleSetBorderColorAction,
                                                            _1,
                                                            TheCommandManager,
                                                            ChangableBorder.get(),
                                                            Color4f(0.0,0.0,1.0,1.0)));

        //Background
        ButtonRecPtr BackgroundRedButton = Button::create();
        BackgroundRedButton->setText("Background Red");
        BackgroundRedButton->setPreferredSize(Vec2f(105, 20));
        BackgroundRedButton->connectActionPerformed(boost::bind(handleSetBackgroundColorAction,
                                                                _1,
                                                                TheCommandManager,
                                                                ChangableBackground.get(),
                                                                Color4f(1.0,0.0,0.0,1.0)));

        ButtonRecPtr BackgroundGreenButton = Button::create();
        BackgroundGreenButton->setText("Background Green");
        BackgroundGreenButton->setPreferredSize(Vec2f(105, 20));
        BackgroundGreenButton->connectActionPerformed(boost::bind(handleSetBackgroundColorAction,
                                                                _1,
                                                                TheCommandManager,
                                                                ChangableBackground.get(),
                                                                Color4f(0.0,1.0,0.0,1.0)));

        ButtonRecPtr BackgroundBlueButton = Button::create();
        BackgroundBlueButton->setText("Background Blue");
        BackgroundBlueButton->setPreferredSize(Vec2f(105, 20));
        BackgroundBlueButton->connectActionPerformed(boost::bind(handleSetBackgroundColorAction,
                                                                _1,
                                                                TheCommandManager,
                                                                ChangableBackground.get(),
                                                                Color4f(0.0,0.0,1.0,1.0)));

        //UndoList
        DefaultListModelRecPtr UndoRedoListModel = DefaultListModel::create();
        UndoRedoListModel->pushBack(boost::any(std::string("Top")));

        ListRecPtr UndoRedoList = List::create();
        UndoRedoList->setPreferredSize(Vec2f(200, 300));
        UndoRedoList->setOrientation(List::VERTICAL_ORIENTATION);
        UndoRedoList->setModel(UndoRedoListModel);

        UndoRedoList->getSelectionModel()->connectSelectionChanged(boost::bind(handleUndoRedoListSelectionChanged,
                                                                               _1,
                                                                               UndoRedoList.get(),
                                                                               TheUndoManager));

        ButtonRecPtr UndoButton = Button::create();
        UndoButton->setText("Undo");
        UndoButton->setEnabled(TheUndoManager->numberOfUndos() != 0);
        UndoButton->connectActionPerformed(boost::bind(handleUndoButtonAction,
                                                       _1,
                                                       TheUndoManager));


        ButtonRecPtr RedoButton = Button::create();
        RedoButton->setText("Redo");
        RedoButton->setEnabled(TheUndoManager->numberOfRedos() != 0);
        RedoButton->connectActionPerformed(boost::bind(handleRedoButtonAction,
                                                       _1,
                                                       TheUndoManager));

        // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
        ScrollPanelRecPtr UndoRedoScrollPanel = ScrollPanel::create();
        UndoRedoScrollPanel->setPreferredSize(Vec2f(200,200));
        UndoRedoScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        UndoRedoScrollPanel->setViewComponent(UndoRedoList);

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();
        MainInternalWindow->pushToChildren(BorderRedButton);
        MainInternalWindow->pushToChildren(BorderGreenButton);
        MainInternalWindow->pushToChildren(BorderBlueButton);
        MainInternalWindow->pushToChildren(BackgroundRedButton);
        MainInternalWindow->pushToChildren(BackgroundGreenButton);
        MainInternalWindow->pushToChildren(BackgroundBlueButton);
        MainInternalWindow->pushToChildren(ChangableLabel);
        MainInternalWindow->pushToChildren(UndoRedoScrollPanel);
        MainInternalWindow->pushToChildren(UndoButton);
        MainInternalWindow->pushToChildren(RedoButton);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.95f,0.95f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);


        TheUndoManager->connectStateChanged(boost::bind(handleUndoManagerStateChanged,
                                                        _1,
                                                        UndoRedoListModel.get(),
                                                        TheUndoManager,
                                                        UndoButton.get(),
                                                        RedoButton.get()));

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

        //Create the Documentation Foreground and add it to the viewport
        SimpleScreenDoc TheSimpleScreenDoc(&sceneManager, TutorialWindow);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "40UndoableCommand");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}