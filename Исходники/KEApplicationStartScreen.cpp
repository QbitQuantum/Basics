ForegroundRefPtr ApplicationStartScreen::createInterface(void)
{
    // Create the Graphics
    GraphicsRefPtr StartScreenUIGraphics = OSG::Graphics2D::create();



    UIFontRefPtr ButtonFont = OSG::UIFont::create();
    ButtonFont->setSize(32);

    ButtonRefPtr BuilderButton = ::OSG::Button::create();
    BuilderButton->setPreferredSize(Vec2f(200, 75));
    BuilderButton->setText("Builder");
    BuilderButton->setFont(ButtonFont);
    BuilderButton->addActionListener(&_BuilderButtonActionListener); 

    ButtonRefPtr PlayerButton = ::OSG::Button::create();
    PlayerButton->setPreferredSize(Vec2f(200, 75));
    PlayerButton->setText("Player");
    PlayerButton->setFont(ButtonFont);
    PlayerButton->addActionListener(&_PlayerButtonActionListener); 

    ButtonRefPtr ExitButton = ::OSG::Button::create();
    ExitButton->setPreferredSize(Vec2f(200, 75));
    ExitButton->setText("Exit");
    ExitButton->setFont(ButtonFont);
    ExitButton->addActionListener(&_ExitButtonActionListener); 

    //ButtonPanel
    PanelRefPtr ButtonPanel = Panel::createEmpty();
    LayoutRefPtr ButtonPanelLayout = OSG::FlowLayout::create();
    ButtonPanel->pushToChildren(BuilderButton);
    ButtonPanel->pushToChildren(PlayerButton);
    ButtonPanel->pushToChildren(ExitButton);
    ButtonPanel->setLayout(ButtonPanelLayout);

    //Font
    UIFontRefPtr LabelFont = UIFont::create();
    LabelFont->setSize(16);

    //Version Label
    LabelRefPtr VersionLabel = OSG::Label::create();
    VersionLabel->setText("Version:");
    VersionLabel->setAlignment(Vec2f(1.0f,0.5f));
    VersionLabel->setPreferredSize(Vec2f(100,20));
    VersionLabel->setTextColors(Color4f(1.0f,1.0f,1.0f,1.0f));
    VersionLabel->setBackgrounds(NULL);
    VersionLabel->setBorders(NULL);
    VersionLabel->setFont(LabelFont);

    //Version Value Label
    LabelRefPtr VersionValueLabel = OSG::Label::create();
    VersionValueLabel->setText(getKabalaEngineVersion() + " - " + getKabalaEngineBuildType());
    VersionValueLabel->setPreferredSize(Vec2f(110,20));
    VersionValueLabel->setTextColors(Color4f(1.0f,1.0f,1.0f,1.0f));
    VersionValueLabel->setBackgrounds(NULL);
    VersionValueLabel->setBorders(NULL);
    VersionValueLabel->setFont(LabelFont);

    //Author Value Label
    LabelRefPtr AuthorValueLabel = OSG::Label::create();
    AuthorValueLabel->setText(getKabalaEngineAuthors());
    AuthorValueLabel->setPreferredSize(Vec2f(300,20));
    AuthorValueLabel->setTextColors(Color4f(1.0f,1.0f,1.0f,1.0f));
    AuthorValueLabel->setBackgrounds(NULL);
    AuthorValueLabel->setBorders(NULL);
    AuthorValueLabel->setFont(LabelFont);

    // Create The Main InternalWindow
    InternalWindowRefPtr StartScreenInternalWindow = OSG::InternalWindow::create();

    //Layout
    SpringLayoutRefPtr StartScreenInternalWindowLayout = OSG::SpringLayout::create();
    //::OSG::Button Panel
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ButtonPanel, 0, SpringLayoutConstraints::NORTH_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ButtonPanel, 0, SpringLayoutConstraints::SOUTH_EDGE, StartScreenInternalWindow);

    //Version Label
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, VersionLabel, 0, SpringLayoutConstraints::WEST_EDGE, VersionValueLabel);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, VersionLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, VersionLabel, LayoutSpring::height(VersionLabel));
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, VersionLabel, LayoutSpring::width(VersionLabel));

    //Version Value Label
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, VersionValueLabel, 0, SpringLayoutConstraints::EAST_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, VersionValueLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, VersionValueLabel, LayoutSpring::height(VersionValueLabel));
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, VersionValueLabel, LayoutSpring::width(VersionValueLabel));

    //Author Value Label
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, AuthorValueLabel, 0, SpringLayoutConstraints::WEST_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, AuthorValueLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, AuthorValueLabel, LayoutSpring::height(AuthorValueLabel));
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, AuthorValueLabel, LayoutSpring::width(AuthorValueLabel));

    StartScreenInternalWindow->pushToChildren(ButtonPanel);
    StartScreenInternalWindow->pushToChildren(AuthorValueLabel);
    StartScreenInternalWindow->pushToChildren(VersionLabel);
    StartScreenInternalWindow->pushToChildren(VersionValueLabel);
    StartScreenInternalWindow->setLayout(StartScreenInternalWindowLayout);
    StartScreenInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    StartScreenInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
    StartScreenInternalWindow->setDrawTitlebar(false);
    StartScreenInternalWindow->setDrawDecorations(false);
    StartScreenInternalWindow->setResizable(false);

    // Create the Drawing Surface
    _TheUIDrawingSurface = UIDrawingSurface::create();
    _TheUIDrawingSurface->setGraphics(StartScreenUIGraphics);

    _TheUIDrawingSurface->openWindow(StartScreenInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr StartScreenUIForeground = OSG::UIForeground::create();

    StartScreenUIForeground->setDrawingSurface(_TheUIDrawingSurface);

    return StartScreenUIForeground;
}