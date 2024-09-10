PanelTransitPtr VideoFieldContainerEditor::createVideoPreviewPanel(void)
{
    ChunkMaterialUnrecPtr VideoMaterial = ChunkMaterial::create();

    //Video MaterialLayer
    _VideoMaterialLayer = MaterialLayer::create();
    _VideoMaterialLayer->setMaterial(VideoMaterial);

    //Video Panel
    _VideoPanel = Panel::createEmpty();
    _VideoPanel->setBackgrounds(_VideoMaterialLayer);

    //Filename Label
    _FileNameLabel = Label::create();
    _FileNameLabel->setAlignment(Vec2f(0.5f, 0.5f));

    //Total time Label
    _TotalTimeLabel = Label::create();
    _TotalTimeLabel->setAlignment(Vec2f(0.0f, 1.0f));
    _TotalTimeLabel->setBorders(NULL);
    _TotalTimeLabel->setBackgrounds(NULL);
    _TotalTimeLabel->setPreferredSize(Vec2f(50.0f,_TotalTimeLabel->getPreferredSize().y()));

    //Playback time Label
    _PlaybackTimeLabel = Label::create();
    _PlaybackTimeLabel->setAlignment(Vec2f(1.0f, 1.0f));
    _PlaybackTimeLabel->setPreferredSize(Vec2f(50.0f,_TotalTimeLabel->getPreferredSize().y()));
    _PlaybackTimeLabel->setBorders(NULL);
    _PlaybackTimeLabel->setBackgrounds(NULL);

    LabelRecPtr TimeSeparatorLabel = Label::create();
    TimeSeparatorLabel->setAlignment(Vec2f(0.5f, 1.0f));
    TimeSeparatorLabel->setPreferredSize(Vec2f(8.0f,_TotalTimeLabel->getPreferredSize().y()));
    TimeSeparatorLabel->setBorders(NULL);
    TimeSeparatorLabel->setBackgrounds(NULL);
    TimeSeparatorLabel->setText("/");

    //PlayPause Button
    _PlayPauseButton = Button::create();
    _PlayPauseButton->setText("Play");
    _PlayPauseButton->setPreferredSize(Vec2f(40.0f,40.0f));
    _PlayPauseButton->connectActionPerformed(boost::bind(&VideoFieldContainerEditor::handlePlayPauseAction, this,   _1));

    //Stop Button
    _StopButton = Button::create();
    _StopButton->setText("Stop");
    _StopButton->setPreferredSize(Vec2f(40.0f,40.0f));
    _StopButton->connectActionPerformed(boost::bind(&VideoFieldContainerEditor::handleStopAction, this,   _1));

    //Load Button
    ButtonRecPtr LoadButton = Button::create();
    LoadButton->setText("Load");
    LoadButton->setPreferredSize(Vec2f(40.0f,40.0f));
    LoadButton->connectActionPerformed(boost::bind(&VideoFieldContainerEditor::handleLoadAction, this,   _1));

    //Playback position slider
    _LocationSlider = Slider::create();
    _LocationSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
    _LocationSlider->setDrawLabels(false);
    _LocationSlider->setDrawMajorTicks(false);
    _LocationSlider->setDrawMinorTicks(false);
    _LocationSlider->setBorders(NULL);
    _LocationSlider->setBackgrounds(NULL);
    //_LocationSlider->getKnobButton()->setPreferredSize(Vec2f(15.0f, 8.0f));
    _LocationSlider->getRangeModel()->connectStateChanged(boost::bind(&VideoFieldContainerEditor::handlePlaybackLocationStateChanged, this,   _1));


    //Layout
    PanelRecPtr VideoPanel = Panel::createEmpty();
    SpringLayoutRecPtr MainLayout = SpringLayout::create();


    //Video Panel
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _VideoPanel, 0,
                              SpringLayoutConstraints::EAST_EDGE, VideoPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _VideoPanel, 0,
                              SpringLayoutConstraints::WEST_EDGE, VideoPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _VideoPanel, 0,
                              SpringLayoutConstraints::NORTH_EDGE, VideoPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _VideoPanel, -1,
                              SpringLayoutConstraints::NORTH_EDGE, _PlayPauseButton);

    //Filename Label
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _FileNameLabel, 0,
                              SpringLayoutConstraints::EAST_EDGE, VideoPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _FileNameLabel, 0,
                              SpringLayoutConstraints::WEST_EDGE, VideoPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _FileNameLabel, 0,
                              SpringLayoutConstraints::NORTH_EDGE, VideoPanel);

    //Play/pause Button
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _PlayPauseButton, -3,
                              SpringLayoutConstraints::WEST_EDGE, _StopButton);
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _PlayPauseButton, 0,
                              SpringLayoutConstraints::SOUTH_EDGE, VideoPanel);

    //Stop Button
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _StopButton, -3,
                              SpringLayoutConstraints::WEST_EDGE, _LocationSlider);
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _StopButton, 0,
                              SpringLayoutConstraints::SOUTH_EDGE, VideoPanel);

    //Playback Slider
    MainLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _LocationSlider, 0,
                              SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, VideoPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _LocationSlider, 0,
                              SpringLayoutConstraints::SOUTH_EDGE, VideoPanel);

    //Total video length label
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _TotalTimeLabel, 0,
                              SpringLayoutConstraints::SOUTH_EDGE, LoadButton);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _TotalTimeLabel, 0,
                              SpringLayoutConstraints::EAST_EDGE, _LocationSlider);

    //Separator label
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TimeSeparatorLabel, 0,
                              SpringLayoutConstraints::SOUTH_EDGE, LoadButton);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TimeSeparatorLabel, -2,
                              SpringLayoutConstraints::WEST_EDGE, _TotalTimeLabel);

    //Playback time label
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _PlaybackTimeLabel, 0,
                              SpringLayoutConstraints::SOUTH_EDGE, LoadButton);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _PlaybackTimeLabel, -2,
                              SpringLayoutConstraints::WEST_EDGE, TimeSeparatorLabel);

    //Load Button
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, LoadButton, 3,
                              SpringLayoutConstraints::EAST_EDGE, _LocationSlider);
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, LoadButton, 0,
                              SpringLayoutConstraints::SOUTH_EDGE, VideoPanel);

    //Main Video Panel
    VideoPanel->setLayout(MainLayout);

    VideoPanel->pushToChildren(_VideoPanel);
    VideoPanel->pushToChildren(_FileNameLabel);
    VideoPanel->pushToChildren(_PlayPauseButton);
    VideoPanel->pushToChildren(_StopButton);
    VideoPanel->pushToChildren(LoadButton);
    VideoPanel->pushToChildren(_PlaybackTimeLabel);
    VideoPanel->pushToChildren(TimeSeparatorLabel);
    VideoPanel->pushToChildren(_TotalTimeLabel);
    VideoPanel->pushToChildren(_LocationSlider);

    return PanelTransitPtr(VideoPanel);
}