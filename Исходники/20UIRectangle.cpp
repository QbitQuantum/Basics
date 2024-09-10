InternalWindowTransitPtr createMainInternalWindow(void)
{
    /******************************************************

      Create Button Components to be used with 
      TabPanel and specify their characteristics.

        Note: Buttons are used for simplicity,
        any Component can be used as Tab content
        or as a Tab.  A Panel with several
        Buttons within it is also added.

     ******************************************************/

    ButtonRecPtr ExampleTabButton1 = Button::create();
    ButtonRecPtr ExampleTabButton2 = Button::create();
    ButtonRecPtr ExampleTabButton3 = Button::create();
    ButtonRecPtr ExampleTabButton4 = Button::create();
    ButtonRecPtr ExampleTabButton5 = Button::create();
    ButtonRecPtr ExampleTabButton6 = Button::create();
    ButtonRecPtr ExampleTabContentA = Button::create();
    ButtonRecPtr ExampleTabContentB = Button::create();
    ButtonRecPtr ExampleTabContentC = Button::create();
    ButtonRecPtr ExampleTabContentD = Button::create();
    ButtonRecPtr ExampleTabContentE = Button::create();
    ButtonRecPtr ExampleTabContentF = Button::create();

    ExampleTabButton1->setText("Tab1");

    ExampleTabButton2->setText("Tab2");

    ExampleTabButton3->setText("To Rotate");

    ExampleTabButton4->setText("Tab4");

    ExampleTabButton5->setText("To Zoom");

    ExampleTabButton6->setText("To Move");

    ExampleTabContentA->setText("Add another Tab");

    ExampleTabContentB->setText("Add a Tab in Tab1!");

    ExampleTabContentC->setText("Enable CapsLock, then rotate scene using left Mouse button!");

    ExampleTabContentD->setText("Enable CapsLock, then zoom in and out with right Mouse button and dragging");

    ExampleTabContentE->setText("Enable CapsLock, then move using center Mouse button");

    /******************************************************

      Create a Panel to add to the TabPanel

     ******************************************************/

    // Create and edit the Panel Buttons
    ButtonRecPtr ExampleTabPanelButton1 = Button::create();
    ButtonRecPtr ExampleTabPanelButton2 = Button::create();
    ButtonRecPtr ExampleTabPanelButton3 = Button::create();
    ButtonRecPtr ExampleTabPanelButton4 = Button::create();
    ButtonRecPtr ExampleTabPanelButton5 = Button::create();
    ButtonRecPtr ExampleTabPanelButton6 = Button::create();

    ExampleTabPanelButton1->setText("This is a");

    ExampleTabPanelButton2->setText("sample");

    ExampleTabPanelButton3->setText("UIRectangle");

    ExampleTabPanelButton4->setText("containing");

    ExampleTabPanelButton5->setText("interactive");

    ExampleTabPanelButton6->setText("components");

    // Create and edit Panel Layout
    BoxLayoutRecPtr TabPanelLayout = BoxLayout::create();
    TabPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

    // Create and edit Panel
    PanelRecPtr ExampleTabPanelPanel = Panel::create();
    ExampleTabPanelPanel->setPreferredSize(Vec2f(180, 500));
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton1);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton2);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton3);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton4);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton5);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton6);
    ExampleTabPanelPanel->setLayout(TabPanelLayout);

    TabPanelRecPtr ExampleTabPanel = TabPanel::create();
    ExampleTabPanel->setPreferredSize(Vec2f(350,350));
    ExampleTabPanel->addTab(ExampleTabButton1, ExampleTabContentA);
    ExampleTabPanel->addTab(ExampleTabButton2, ExampleTabContentB);
    ExampleTabPanel->addTab(ExampleTabButton3, ExampleTabContentC);
    ExampleTabPanel->addTab(ExampleTabButton4, ExampleTabPanelPanel);
    ExampleTabPanel->addTab(ExampleTabButton5, ExampleTabContentD);
    ExampleTabPanel->addTab(ExampleTabButton6, ExampleTabContentE);
    ExampleTabPanel->setTabAlignment(0.5f);
    ExampleTabPanel->setTabPlacement(TabPanel::PLACEMENT_SOUTH);
    ExampleTabPanel->setSelectedIndex(3);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    CardLayoutRecPtr MainInternalWindowLayout = CardLayout::create();

    InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleTabPanel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);

    ExampleTabContentB->connectActionPerformed(boost::bind(handleRemoveTabAction, _1,
                                                           ExampleTabPanel.get(),
                                                           ExampleTabContentA.get(),
                                                           ExampleTabContentB.get()));
    ExampleTabContentA->connectActionPerformed(boost::bind(handleAddTabAction, _1,
                                                           ExampleTabPanel.get(),
                                                           ExampleTabContentA.get(),
                                                           ExampleTabContentB.get()));

    return InternalWindowTransitPtr(MainInternalWindow);
}