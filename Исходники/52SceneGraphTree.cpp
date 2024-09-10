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

        NodeRecPtr Root(NULL);
        if(argc == 2)
        {
            Root = SceneFileHandler::the()->read(argv[1]);
        }

        if(Root == NULL)
        {
            // Make Torus Node (creates Torus in background of Root)
            NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
            setName(TorusGeometryNode, std::string("Torus"));

            NodeRecPtr TorusNode = Node::create();
            TorusNode->setCore(Transform::create());
            TorusNode->addChild(TorusGeometryNode);
            setName(TorusNode, std::string("Torus Transform"));

            NodeRecPtr SphereGeometryNode = makeSphere(2,1.0f);
            setName(SphereGeometryNode, std::string("Sphere"));
            NodeRecPtr BoxGeometryNode = makeBox(1.0,1.0,1.0,1,1,1);
            setName(BoxGeometryNode, std::string("Box"));

            // Make Main Scene Node and add the Torus
            Root = Node::create();
            Root->setCore(Group::create());
            Root->addChild(TorusNode);
            Root->addChild(SphereGeometryNode);
            Root->addChild(BoxGeometryNode);
            setName(Root, std::string("Root"));
        }

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        //Tree Model
        SceneGraphTreeModelRecPtr TheTreeModel = SceneGraphTreeModel::create();
        TheTreeModel->setRoot(Root);

        //Create the Tree
        TreeRecPtr TheTree = Tree::create();

        TheTree->setPreferredSize(Vec2f(100, 500));
        TheTree->setModel(TheTreeModel);


        // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
        BorderLayoutConstraintsRecPtr SceneTreeConstraints = BorderLayoutConstraints::create();
        SceneTreeConstraints->setRegion(BorderLayoutConstraints::BORDER_WEST);

        ScrollPanelRecPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(350,300));
        ExampleScrollPanel->setConstraints(SceneTreeConstraints);
        //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        ExampleScrollPanel->setViewComponent(TheTree);

        //Details Panel Labels
        LabelRecPtr NodeNameLabel = Label::create();
        NodeNameLabel->setText("Name");
        NodeNameLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeNameValueLabel = Label::create();
        NodeNameValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeCoreTypeLabel = Label::create();
        NodeCoreTypeLabel->setText("Core Type");
        NodeCoreTypeLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeCoreTypeValueLabel = Label::create();
        NodeCoreTypeValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeMinLabel = Label::create();
        NodeMinLabel->setText("Min");
        NodeMinLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeMinValueLabel = Label::create();
        NodeMinValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeMaxLabel = Label::create();
        NodeMaxLabel->setText("Max");
        NodeMaxLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeMaxValueLabel = Label::create();
        NodeMaxValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeCenterLabel = Label::create();
        NodeCenterLabel->setText("Center");
        NodeCenterLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeCenterValueLabel = Label::create();
        NodeCenterValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeTriCountLabel = Label::create();
        NodeTriCountLabel->setText("TriCount");
        NodeTriCountLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeTriCountValueLabel = Label::create();
        NodeTriCountValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeTravMaskLabel = Label::create();
        NodeTravMaskLabel->setText("Traversal Mask");
        NodeTravMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeTravMaskValueLabel = Label::create();
        NodeTravMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
        //Details Panel
        BorderLayoutConstraintsRecPtr NodeDetailPanelConstraints = BorderLayoutConstraints::create();
        NodeDetailPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);

        GridLayoutRecPtr NodeDetailPanelLayout = GridLayout::create();

        NodeDetailPanelLayout->setRows(7);
        NodeDetailPanelLayout->setColumns(2);
        NodeDetailPanelLayout->setHorizontalGap(2);
        NodeDetailPanelLayout->setVerticalGap(2);

        PanelRecPtr NodeDetailPanel = Panel::create();
        NodeDetailPanel->setConstraints(NodeDetailPanelConstraints);
        NodeDetailPanel->setPreferredSize(Vec2f(100.0f, 200.0f));
        NodeDetailPanel->setLayout(NodeDetailPanelLayout);
        NodeDetailPanel->pushToChildren(NodeNameLabel);
        NodeDetailPanel->pushToChildren(NodeNameValueLabel);
        NodeDetailPanel->pushToChildren(NodeCoreTypeLabel);
        NodeDetailPanel->pushToChildren(NodeCoreTypeValueLabel);
        NodeDetailPanel->pushToChildren(NodeMinLabel);
        NodeDetailPanel->pushToChildren(NodeMinValueLabel);
        NodeDetailPanel->pushToChildren(NodeMaxLabel);
        NodeDetailPanel->pushToChildren(NodeMaxValueLabel);
        NodeDetailPanel->pushToChildren(NodeCenterLabel);
        NodeDetailPanel->pushToChildren(NodeCenterValueLabel);
        NodeDetailPanel->pushToChildren(NodeTriCountLabel);
        NodeDetailPanel->pushToChildren(NodeTriCountValueLabel);
        NodeDetailPanel->pushToChildren(NodeTravMaskLabel);
        NodeDetailPanel->pushToChildren(NodeTravMaskValueLabel);

        SelectionHandler TheTreeSelectionHandler(TheTree,
                                                 &sceneManager,
                                                 NodeNameValueLabel,
                                                 NodeCoreTypeValueLabel,
                                                 NodeMinValueLabel,
                                                 NodeMaxValueLabel,
                                                 NodeCenterValueLabel,
                                                 NodeTriCountValueLabel,
                                                 NodeTravMaskValueLabel);
        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = BorderLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleScrollPanel);
        MainInternalWindow->pushToChildren(NodeDetailPanel);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(NULL);
        MainInternalWindow->setBorders(NULL);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.0f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0,1.0));
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
        sceneManager.setRoot(Root);

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
                                   "52SceneGraphTree");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}