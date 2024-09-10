// Initialize WIN32 & OpenSG and set up the scene
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
        GraphicsRecPtr graphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        /******************************************************

          Create the DefaultMutableComboBoxModel and
          add Elements to it (several Colors
          in this case).  These will be the data
          values shown in the ComboBox.

         ******************************************************/   

        DefaultMutableComboBoxModelRecPtr ExampleComboBoxModel = DefaultMutableComboBoxModel::create();
        ExampleComboBoxModel->addElement(boost::any(std::string("Red")));
        ExampleComboBoxModel->addElement(boost::any(std::string("Green")));
        ExampleComboBoxModel->addElement(boost::any(std::string("Blue")));
        ExampleComboBoxModel->addElement(boost::any(std::string("Brown")));
        ExampleComboBoxModel->addElement(boost::any(std::string("Yellow")));
        ExampleComboBoxModel->addElement(boost::any(std::string("Orange")));
        ExampleComboBoxModel->addElement(boost::any(std::string("Violet")));
        ExampleComboBoxModel->addElement(boost::any(std::string("Black")));

        /******************************************************

          Create an editable ComboBox.  A ComboBox 
          has a Model just like various other 
          Components.  

         ******************************************************/   

        //Create the ComboBox
        ComboBoxRecPtr ExampleComboBox = ComboBox::create();

        // Set the Model created above to the ComboBox
        ExampleComboBox->setModel(ExampleComboBoxModel);

        // Determine where the ComboBox starts
        ExampleComboBox->setSelectedIndex(0);

        /******************************************************

          Create a non-editable ComboBox.  

          -setEditable(bool): Determine whether
          the user can type in the ComboBox
          or if it is uneditable.  In this
          case, it is set to false.

          When creating a non-editable ComboBox,
          a Renderer must also be assigned.  For
          editable ComboBoxes, the ComboBox
          automatically shows its text due to the
          nature of the ComboBox.  However, when
          uneditable, this aspect of the ComboBox
          is disabled, and so to display the 
          selection, a renderer must be created and
          assigned to the ComboBox.

Note: as with Sliders and ScrollBars,
having the same Model assigned causes
the ComboBoxes to be tied together.

         ******************************************************/   
        // Create another ComboBox
        ComboBoxRecPtr ExampleUneditableComboBox = ComboBox::create();

        // Set it to be uneditable
        ExampleUneditableComboBox->setEditable(false);
        ExampleUneditableComboBox->setModel(ExampleComboBoxModel);

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleComboBox);
        MainInternalWindow->pushToChildren(ExampleUneditableComboBox);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);

        //Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(graphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRecPtr foreground = UIForeground::create();

        foreground->setDrawingSurface(TutorialDrawingSurface);



        // Tell the manager what to manage
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr viewport = sceneManager.getWindow()->getPort(0);
        viewport->addForeground(foreground);

        //Create the Documentation Foreground and add it to the viewport
        SimpleScreenDoc TheSimpleScreenDoc(&sceneManager, TutorialWindow);

        // Show the whole scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "33ComboBox");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}