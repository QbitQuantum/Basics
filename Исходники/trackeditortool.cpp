void
TrackEditorTool::initToolWidget()
{
    //	prototypeListWidget->setMaximumWidth(156);

    QGridLayout *toolLayout = new QGridLayout;

    // ButtonGroup //
    //
    // A button group so only one button can be checked at a time
    QButtonGroup *toolGroup = new QButtonGroup;
    connect(toolGroup, SIGNAL(buttonClicked(int)), this, SLOT(handleToolClick(int)));

    // Tools //
    //
    QPushButton *toolButton;
    int row = -1; // button row

    QLabel *trackLabel = new QLabel(tr("Track Tools"));
    toolLayout->addWidget(trackLabel, ++row, 0, 1, ColumnCount);

    //	toolButton = new QPushButton("Select");
    //	toolButton->setCheckable(true);
    //	toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    //	toolGroup->addButton(toolButton, ODD::TTE_SELECT); // button, id

    toolButton = new QPushButton("Move Rotate");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TTE_MOVE_ROTATE); // button, id

    toolButton = new QPushButton("Add Line");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TTE_ADD_LINE); // button, id

    toolButton = new QPushButton("Add Curve");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, row, 1);
    toolGroup->addButton(toolButton, ODD::TTE_ADD_CURVE); // button, id
    //	toolButton->setChecked(true);

    toolButton = new QPushButton("Add Prototype");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TTE_ADD); // button, id

    toolButton = new QPushButton("Delete Tracks");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TTE_DELETE); // button, id

    toolButton = new QPushButton("Split Track");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TTE_TRACK_SPLIT); // button, id

    QFrame *line = new QFrame();
    line->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line->setLineWidth(1);
    toolLayout->addWidget(line, ++row, 0, 1, ColumnCount);

    QLabel *roadLabel = new QLabel(tr("Road Tools"));
    toolLayout->addWidget(roadLabel, ++row, 0, 1, ColumnCount);

    toolButton = new QPushButton("Move Rotate");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TTE_ROAD_MOVE_ROTATE); // button, id

    toolButton = new QPushButton("New Road");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TTE_ROAD_NEW); // button, id

    toolButton = new QPushButton("Add Prototype");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TTE_ROADSYSTEM_ADD); // button, id

    toolButton = new QPushButton("Delete Road");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TTE_ROAD_DELETE); // button, id

    toolButton = new QPushButton("Split Road");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TTE_ROAD_SPLIT); // button, id

    toolButton = new QPushButton("Merge");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TTE_ROAD_MERGE); // button, id

    toolButton = new QPushButton("Snap to");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, row, 1);
    toolGroup->addButton(toolButton, ODD::TTE_ROAD_SNAP); // button, id

    line = new QFrame();
    line->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line->setLineWidth(1);
    toolLayout->addWidget(line, ++row, 0, 1, ColumnCount);

    toolButton = new QPushButton("Split Track and Road");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TTE_TRACK_ROAD_SPLIT); // button, id

    // Tiles
    //

    line = new QFrame();
    line->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line->setLineWidth(1);
    toolLayout->addWidget(line, ++row, 0, 1, ColumnCount);

    roadLabel = new QLabel(tr("Tile Tools"));
    toolLayout->addWidget(roadLabel, ++row, 0, 1, ColumnCount);

    toolButton = new QPushButton("Move Tile");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TTE_TILE_MOVE); // button, id

    toolButton = new QPushButton("New Tile");
    toolButton->setCheckable(false);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TTE_TILE_NEW); // button, id

    toolButton = new QPushButton("Delete Tile");
    toolButton->setCheckable(false);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TTE_TILE_DELETE); // button, id

    // Prototypes //
    //
    //
    QGridLayout *groupBoxLayout;
    QLabel *label;
    QComboBox *comboBox;

    // Track Prototypes //
    //
    //
    groupBoxLayout = new QGridLayout;

    trackPrototypesGroupBox_ = new QGroupBox(tr("Track Settings"));
    trackPrototypesGroupBox_->setLayout(groupBoxLayout);
    trackPrototypesGroupBox_->setEnabled(false);
    toolLayout->addWidget(trackPrototypesGroupBox_, ++row, 0, 1, ColumnCount);

    label = new QLabel(tr("Track Prototype"));
    comboBox = new QComboBox;
    foreach (const PrototypeContainer<RSystemElementRoad *> *container, prototypeManager_->getRoadPrototypes(PrototypeManager::PTP_TrackPrototype))
    {
        comboBox->addItem(container->getPrototypeIcon(), container->getPrototypeName());
    }
    comboBox->setIconSize(QSize(16, 16));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleTrackSelection(int)));
    comboBox->setCurrentIndex(0); // this doesn't trigger an event...
    handleTrackSelection(0); // ... so do it yourself
    groupBoxLayout->addWidget(label, 0, 0);
    groupBoxLayout->addWidget(comboBox, 1, 0);

    // Section Prototypes //
    //
    //
    groupBoxLayout = new QGridLayout;

    sectionPrototypesGroupBox_ = new QGroupBox(tr("Section Settings"));
    sectionPrototypesGroupBox_->setLayout(groupBoxLayout);
    sectionPrototypesGroupBox_->setEnabled(false);
    toolLayout->addWidget(sectionPrototypesGroupBox_, ++row, 0, 1, ColumnCount);

    int groupBoxLayoutRow = 0;

    // LaneSection Prototype //
    //
    label = new QLabel(tr("LaneSection Prototype"));
    comboBox = new QComboBox;
    foreach (const PrototypeContainer<RSystemElementRoad *> *container, prototypeManager_->getRoadPrototypes(PrototypeManager::PTP_LaneSectionPrototype))
    {
        comboBox->addItem(container->getPrototypeIcon(), container->getPrototypeName());
    }
    comboBox->setIconSize(QSize(16, 16));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleLaneSectionSelection(int)));
    comboBox->setCurrentIndex(0);
    handleLaneSectionSelection(0);
    groupBoxLayout->addWidget(label, groupBoxLayoutRow++, 0);
    groupBoxLayout->addWidget(comboBox, groupBoxLayoutRow++, 0);

    // RoadType Prototype //
    //
    label = new QLabel(tr("RoadType Prototype"));
    comboBox = new QComboBox;
    foreach (const PrototypeContainer<RSystemElementRoad *> *container, prototypeManager_->getRoadPrototypes(PrototypeManager::PTP_RoadTypePrototype))
    {
        comboBox->addItem(container->getPrototypeIcon(), container->getPrototypeName());
    }
    comboBox->setIconSize(QSize(16, 16));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleRoadTypeSelection(int)));
    comboBox->setCurrentIndex(0);
    handleRoadTypeSelection(0);
    groupBoxLayout->addWidget(label, groupBoxLayoutRow++, 0);
    groupBoxLayout->addWidget(comboBox, groupBoxLayoutRow++, 0);

    // Elevation Prototype //
    //
    label = new QLabel(tr("Elevation Prototype"));
    comboBox = new QComboBox;
    foreach (const PrototypeContainer<RSystemElementRoad *> *container, prototypeManager_->getRoadPrototypes(PrototypeManager::PTP_ElevationPrototype))
    {
        comboBox->addItem(container->getPrototypeIcon(), container->getPrototypeName());
    }
    comboBox->setIconSize(QSize(16, 16));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleElevationSelection(int)));
    comboBox->setCurrentIndex(0);
    handleElevationSelection(0);
    groupBoxLayout->addWidget(label, groupBoxLayoutRow++, 0);
    groupBoxLayout->addWidget(comboBox, groupBoxLayoutRow++, 0);

    // Superelevation Prototype //
    //
    label = new QLabel(tr("Superelevation Prototype"));
    comboBox = new QComboBox;
    foreach (const PrototypeContainer<RSystemElementRoad *> *container, prototypeManager_->getRoadPrototypes(PrototypeManager::PTP_SuperelevationPrototype))
    {
        comboBox->addItem(container->getPrototypeIcon(), container->getPrototypeName());
    }
    comboBox->setIconSize(QSize(16, 16));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSuperelevationSelection(int)));
    comboBox->setCurrentIndex(0);
    handleSuperelevationSelection(0);
    groupBoxLayout->addWidget(label, groupBoxLayoutRow++, 0);
    groupBoxLayout->addWidget(comboBox, groupBoxLayoutRow++, 0);

    // Crossfall Prototype //
    //
    label = new QLabel(tr("Crossfall Prototype"));
    comboBox = new QComboBox;
    foreach (const PrototypeContainer<RSystemElementRoad *> *container, prototypeManager_->getRoadPrototypes(PrototypeManager::PTP_CrossfallPrototype))
    {
        comboBox->addItem(container->getPrototypeIcon(), container->getPrototypeName());
    }
    comboBox->setIconSize(QSize(16, 16));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleCrossfallSelection(int)));
    comboBox->setCurrentIndex(0);
    handleCrossfallSelection(0);
    groupBoxLayout->addWidget(label, groupBoxLayoutRow++, 0);
    groupBoxLayout->addWidget(comboBox, groupBoxLayoutRow++, 0);

    // RoadSystem Prototypes //
    //
    //
    groupBoxLayout = new QGridLayout;

    roadSystemPrototypesGroupBox_ = new QGroupBox(tr("RoadSystem Settings"));
    roadSystemPrototypesGroupBox_->setLayout(groupBoxLayout);
    roadSystemPrototypesGroupBox_->setEnabled(false);
    toolLayout->addWidget(roadSystemPrototypesGroupBox_, ++row, 0, 1, ColumnCount);

    label = new QLabel(tr("RoadSystem Prototype"));
    comboBox = new QComboBox;
    foreach (const PrototypeContainer<RoadSystem *> *container, prototypeManager_->getRoadSystemPrototypes())
    {
        comboBox->addItem(container->getPrototypeIcon(), container->getPrototypeName());
    }
    comboBox->setIconSize(QSize(16, 16));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleRoadSystemSelection(int)));
    comboBox->setCurrentIndex(0);
    handleRoadSystemSelection(0);
    groupBoxLayout->addWidget(label, 0, 0);
    groupBoxLayout->addWidget(comboBox, 1, 0);

    // Finish Layout //
    //
    toolLayout->setRowStretch(++row, 1); // row x fills the rest of the availlable space
    toolLayout->setColumnStretch(ColumnCount, 1); // column 2 fills the rest of the availlable space

    // Widget/Layout //
    //
    ToolWidget *toolWidget = new ToolWidget();
    toolWidget->setLayout(toolLayout);
    toolManager_->addToolBoxWidget(toolWidget, tr("Track Editor"));
    connect(toolWidget, SIGNAL(activated()), this, SLOT(activateEditor()));

    // Default Settings //
    //
    sectionPrototypesGroupBox_->setVisible(false);
    trackPrototypesGroupBox_->setVisible(false);
    roadSystemPrototypesGroupBox_->setVisible(false);
}