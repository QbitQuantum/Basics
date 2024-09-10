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

          Create BorderLayout and some
          BorderLayoutConstraints to be used 
          to set up CardLayout.

         ******************************************************/

        BorderLayoutRecPtr MainInternalWindowLayout = BorderLayout::create();
        BorderLayoutConstraintsRecPtr ExampleButton1Constraints = BorderLayoutConstraints::create();
        BorderLayoutConstraintsRecPtr ExampleButton2Constraints = BorderLayoutConstraints::create();
        BorderLayoutConstraintsRecPtr ExampleButton7Constraints = BorderLayoutConstraints::create();
        BorderLayoutConstraintsRecPtr ExampleButton8Constraints = BorderLayoutConstraints::create();
        BorderLayoutConstraintsRecPtr ExampleCardPanelConstraints = BorderLayoutConstraints::create();

        ExampleButton1Constraints->setRegion(BorderLayoutConstraints::BORDER_EAST);

        ExampleButton2Constraints->setRegion(BorderLayoutConstraints::BORDER_WEST);

        ExampleButton7Constraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);

        ExampleButton8Constraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);

        ExampleCardPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

        /******************************************************

          Create CardLayout.  CardLayout shows 
          a single Component at a time, meaning
          it is not exactly practical to use it
          alone for a Layout.  This tutorial uses
          the BorderLayout to include a Panel in
          the Center Region, and within that Panel
          using a CardLayout.  A single card is 
          displayed at one time within a 
          ComponentContainer using CardLayout.

          CardLayout has four functions:
          next, previous, first, and last.

          ->next(CardContainerName): Causes 
          CardLayout to display the next card.
          ->previous(CardContainerName): Causes
          CardLayout to display the 
          previous card.
          ->first(CardContainerName): Causes
          CardLayout to display the
          first card.
          ->last(CardContainerName): Causes
          CardLayout to display the
          last card.

          These are most useful when combined with 
          Action, as shown at the top of 
          this Tutorial, to assign actions to the 
          Buttons or Components to allow the user 
          to cycle through the Card Layout and 
          view different ExampleCards.

          Note that CardContainerName is the name
          of the ComponentContainer which is using the
          CardLayout, while the begin/endEditCP
          is performed on the CardLayout itself.

         ******************************************************/

        CardLayoutRecPtr ExampleCardLayout = CardLayout::create();
        PanelRecPtr ExampleCardPanel = Panel::create();

        /******************************************************

          Create Button Components to be used with 
          CardLayout to allow for interactivity.

         ******************************************************/
        ButtonRecPtr ExampleButton1 = Button::create();
        ButtonRecPtr ExampleButton2 = Button::create();
        ButtonRecPtr ExampleButton3 = Button::create();
        ButtonRecPtr ExampleButton4 = Button::create();
        ButtonRecPtr ExampleButton5 = Button::create();
        ButtonRecPtr ExampleButton6 = Button::create();    
        ButtonRecPtr ExampleButton7 = Button::create();
        ButtonRecPtr ExampleButton8 = Button::create();

        ExampleButton1->setText("Next Card");
        ExampleButton1->setConstraints(ExampleButton1Constraints);

        // Add Action
        ExampleButton1->connectActionPerformed(boost::bind(handleNextCardAction, _1,
                                                           ExampleCardLayout.get(),
                                                           ExampleCardPanel.get()));

        ExampleButton2->setText("Previous Card");
        ExampleButton2->setConstraints(ExampleButton2Constraints);

        // Add Action
        ExampleButton2->connectActionPerformed(boost::bind(handleBackCardAction, _1,
                                                           ExampleCardLayout.get(),
                                                           ExampleCardPanel.get()));

        ExampleButton3->setText("This");

        ExampleButton4->setText("is");

        ExampleButton5->setText("Card");

        ExampleButton6->setText("Layout");

        ExampleButton7->setText("First Card");
        ExampleButton7->setConstraints(ExampleButton7Constraints);

        // Add Action
        ExampleButton7->connectActionPerformed(boost::bind(handleFirstCardAction, _1,
                                                           ExampleCardLayout.get(),
                                                           ExampleCardPanel.get()));

        ExampleButton8->setText("Last Card");
        ExampleButton8->setConstraints(ExampleButton8Constraints);

        // Add Action
        ExampleButton8->connectActionPerformed(boost::bind(handleLastCardAction, _1,
                                                           ExampleCardLayout.get(),
                                                           ExampleCardPanel.get()));

        ExampleCardPanel->setLayout(ExampleCardLayout);
        ExampleCardPanel->pushToChildren(ExampleButton3);
        ExampleCardPanel->pushToChildren(ExampleButton4);
        ExampleCardPanel->pushToChildren(ExampleButton5);
        ExampleCardPanel->pushToChildren(ExampleButton6);
        ExampleCardPanel->setConstraints(ExampleCardPanelConstraints);




        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleButton1);
        MainInternalWindow->pushToChildren(ExampleButton2);
        MainInternalWindow->pushToChildren(ExampleButton7);
        MainInternalWindow->pushToChildren(ExampleButton8);
        MainInternalWindow->pushToChildren(ExampleCardPanel);
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

        //Create the Documentation Foreground and add it to the viewport
        SimpleScreenDoc TheSimpleScreenDoc(&sceneManager, TutorialWindow);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "11CardLayout");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}