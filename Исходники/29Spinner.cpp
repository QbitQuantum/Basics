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

          Create a Spinner Model.  This dictates 
          how the Spinner functions.
          -setMaximum(int): Determine the Maximum 
          value the Spinner can have.
          -setMinimum(int): Determine the Minimum 
          value the Spinner can have.
          -setStepSize(int): Determine the 
          incremental step size.
          -setValue(SharedFieldRecPtr(new SFInt32(int)):
          Determine initial starting value
          of the Spinner.

          Note: the StepSize can be changed 
          dynamically as done in this 
          Tutorial with ButtonSelectedListeners.

         ******************************************************/    

        //Int32SpinnerModelPtr TheModel(new Int32SpinnerModel());
        Int32SpinnerModelPtr TheModel(new Int32SpinnerModel());
        TheModel->setMaximum(100);
        TheModel->setMinimum(-100);
        TheModel->setStepSize(1);
        TheModel->setValue(boost::any(Int32(0)));

        /******************************************************

          Create a Spinner and and assign it a 
          Model.

         ******************************************************/    

        SpinnerRecPtr ExampleSpinner = Spinner::create();
        ExampleSpinner->setModel(TheModel);

        /******************************************************

          Create a RadioButtonPanel to allow
          for certain characteristics of the
          Spinner to be changed dynamically.
          See 14RadioButton for more 
          information about RadioButtons.

         ******************************************************/    

        RadioButtonRecPtr SingleIncrementButton = RadioButton::create();
        RadioButtonRecPtr DoubleIncrementButton = RadioButton::create();
        SingleIncrementButton->setText("Increment by 1");
        SingleIncrementButton->setPreferredSize(Vec2f(100, 50));
        SingleIncrementButton->connectButtonSelected(boost::bind(handleSingleIncbuttonSelected, _1,
                                                                 TheModel));

        DoubleIncrementButton->setText("Increment by 2");
        DoubleIncrementButton->setPreferredSize(Vec2f(100, 50));
        DoubleIncrementButton->connectButtonSelected(boost::bind(handleDoubleIncbuttonSelected, _1,
                                                                 TheModel));

        RadioButtonGroupRecPtr SelectionRadioButtonGroup = RadioButtonGroup::create();
        SelectionRadioButtonGroup->addButton(SingleIncrementButton);
        SelectionRadioButtonGroup->addButton(DoubleIncrementButton);
        SingleIncrementButton->setSelected(true);

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(SingleIncrementButton);
        MainInternalWindow->pushToChildren(DoubleIncrementButton);
        MainInternalWindow->pushToChildren(ExampleSpinner);
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
                                   "29Spinner");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}