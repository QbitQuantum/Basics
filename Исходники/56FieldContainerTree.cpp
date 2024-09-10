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

            NodeRecPtr TorusNode = Node::create();
            TorusNode->setCore(Transform::create());
            TorusNode->addChild(TorusGeometryNode);

            NodeRecPtr SphereGeometryNode = makeSphere(2,1.0f);
            NodeRecPtr BoxGeometryNode = makeBox(1.0,1.0,1.0,1,1,1);

            // Make Main Scene Node and add the Torus
            Root = Node::create();
            Root->setCore(Group::create());
            Root->addChild(TorusNode);
            Root->addChild(SphereGeometryNode);
            Root->addChild(BoxGeometryNode);
        }

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        //Import InternalWindow(s) from XML file
        std::vector<InternalWindowRecPtr> StoreWindows;

        FCFileType::FCPtrStore NewContainers;
        NewContainers = FCFileHandler::the()->read(BoostPath("./Data/55ComponentTree.xml"));

        //Store each window found in the XML in the vector
        FCFileType::FCPtrStore::iterator Itor;
        for(Itor = NewContainers.begin(); Itor != NewContainers.end(); ++Itor)
        {
            if( (*Itor)->getType() == (InternalWindow::getClassType()))
            {
                StoreWindows.push_back(dynamic_pointer_cast<InternalWindow>(*Itor));
            }
        }
        //Tree Model
        FieldContainerTreeModelRecPtr TheTreeModel = FieldContainerTreeModel::create();
        TheTreeModel->setRoot(StoreWindows.front());
        //TheTreeModel->setShowPtrFields(false);
        //TheTreeModel->setShowDataFields(false);
        //TheTreeModel->setShowParentPtrFields(false);
        //TheTreeModel->setShowChildPtrFields(false);
        TheTreeModel->setShowAttachments(false);
        //TheTreeModel->setShowCallbackFunctors(false);

        //Tree Component Generator
        FieldContainerFieldPathComponentGeneratorRecPtr TheTreeComponentGenerator = FieldContainerFieldPathComponentGenerator::create();

        //Create the Tree
        TreeRecPtr TheTree = Tree::create();

        TheTree->setPreferredSize(Vec2f(100, 500));
        TheTree->setRootVisible(true);
        TheTree->setModel(TheTreeModel);
        TheTree->setCellGenerator(TheTreeComponentGenerator);
        setName(TheTree, std::string("TheTree"));

        // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
        ScrollPanelRecPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(350,500));
        //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        ExampleScrollPanel->setViewComponent(TheTree);
        setName(ExampleScrollPanel, std::string("ExampleScrollPanel"));

        //Show Buttons
        CheckboxButtonRecPtr ShowMultiFieldsButton = CheckboxButton::create();
        CheckboxButtonRecPtr ShowSingleFieldsButton = CheckboxButton::create();
        CheckboxButtonRecPtr ShowPtrFieldsButton = CheckboxButton::create();
        CheckboxButtonRecPtr ShowDataFieldsButton = CheckboxButton::create();
        CheckboxButtonRecPtr ShowParentPtrFieldsButton = CheckboxButton::create();
        CheckboxButtonRecPtr ShowChildPtrFieldsButton = CheckboxButton::create();
        CheckboxButtonRecPtr ShowAttachmentsButton = CheckboxButton::create();
        CheckboxButtonRecPtr ShowCallbackFunctorsButton = CheckboxButton::create();
        CheckboxButtonRecPtr ShowInternalFieldsButton = CheckboxButton::create();

        ShowMultiFieldsButton->setText("Multi Fields");
        ShowMultiFieldsButton->setPreferredSize(Vec2f(120.0f,ShowMultiFieldsButton->getPreferredSize().y()));
        ShowMultiFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
        ShowSingleFieldsButton->setText("Single Fields");
        ShowSingleFieldsButton->setPreferredSize(Vec2f(120.0f,ShowSingleFieldsButton->getPreferredSize().y()));
        ShowSingleFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
        ShowPtrFieldsButton->setText("Ptr Fields");
        ShowPtrFieldsButton->setPreferredSize(Vec2f(120.0f,ShowPtrFieldsButton->getPreferredSize().y()));
        ShowPtrFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
        ShowDataFieldsButton->setText("Data Fields");
        ShowDataFieldsButton->setPreferredSize(Vec2f(120.0f,ShowDataFieldsButton->getPreferredSize().y()));
        ShowDataFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
        ShowParentPtrFieldsButton->setText("ParentPtr Fields");
        ShowParentPtrFieldsButton->setPreferredSize(Vec2f(120.0f,ShowParentPtrFieldsButton->getPreferredSize().y()));
        ShowParentPtrFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
        ShowChildPtrFieldsButton->setText("ChildPtr Fields");
        ShowChildPtrFieldsButton->setPreferredSize(Vec2f(120.0f,ShowChildPtrFieldsButton->getPreferredSize().y()));
        ShowChildPtrFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
        ShowAttachmentsButton->setText("Attachments");
        ShowAttachmentsButton->setPreferredSize(Vec2f(120.0f,ShowAttachmentsButton->getPreferredSize().y()));
        ShowAttachmentsButton->setAlignment(Vec2f(0.0f,0.5f));
        ShowCallbackFunctorsButton->setText("Callback Functors");
        ShowCallbackFunctorsButton->setPreferredSize(Vec2f(120.0f,ShowCallbackFunctorsButton->getPreferredSize().y()));
        ShowCallbackFunctorsButton->setAlignment(Vec2f(0.0f,0.5f));
        ShowInternalFieldsButton->setText("Internal Fields");
        ShowInternalFieldsButton->setPreferredSize(Vec2f(120.0f,ShowInternalFieldsButton->getPreferredSize().y()));
        ShowInternalFieldsButton->setAlignment(Vec2f(0.0f,0.5f));

        ShowCheckboxesController CheckboxesController(TheTreeModel,
                                                      ShowMultiFieldsButton,
                                                      ShowSingleFieldsButton,
                                                      ShowPtrFieldsButton,
                                                      ShowDataFieldsButton,
                                                      ShowParentPtrFieldsButton,
                                                      ShowChildPtrFieldsButton,
                                                      ShowAttachmentsButton,
                                                      ShowCallbackFunctorsButton,
                                                      ShowInternalFieldsButton);

        PanelRecPtr OptionsPanel = Panel::create();
        FlowLayoutRecPtr OptionsPanelLayout = FlowLayout::create();
        OptionsPanel->setLayout(OptionsPanelLayout);
        OptionsPanel->setPreferredSize(Vec2f(250.0f, 300.0f));
        OptionsPanel->pushToChildren(ShowMultiFieldsButton);
        OptionsPanel->pushToChildren(ShowSingleFieldsButton);
        OptionsPanel->pushToChildren(ShowPtrFieldsButton);
        OptionsPanel->pushToChildren(ShowDataFieldsButton);
        OptionsPanel->pushToChildren(ShowInternalFieldsButton);
        OptionsPanel->pushToChildren(ShowParentPtrFieldsButton);
        OptionsPanel->pushToChildren(ShowChildPtrFieldsButton);
        OptionsPanel->pushToChildren(ShowAttachmentsButton);
        OptionsPanel->pushToChildren(ShowCallbackFunctorsButton);

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleScrollPanel);
        MainInternalWindow->pushToChildren(OptionsPanel);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);
        setName(MainInternalWindow, std::string("MainInternalWindow"));

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        TutorialDrawingSurface->openWindow(StoreWindows.back());

        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        // Tell the Manager what to manage
        sceneManager.setRoot(Root);

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
                                   "56FieldContainerTree");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}