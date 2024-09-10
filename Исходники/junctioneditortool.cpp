void
JunctionEditorTool::initToolWidget()
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

    //	toolButton = new QPushButton("Select");
    //	toolButton->setCheckable(true);
    //	toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    //	toolGroup->addButton(toolButton, ODD::TTE_SELECT); // button, id

    toolButton = new QPushButton("Select");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TJE_SELECT); // button, id

    QLabel *junctionLabel = new QLabel(tr("Prepare Roads"));
    toolLayout->addWidget(junctionLabel, ++row, 0, 1, ColumnCount);

    toolButton = new QPushButton("Split");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TJE_SPLIT); // button, id

    toolButton = new QPushButton("Adjust");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, row, 1);
    toolGroup->addButton(toolButton, ODD::TJE_MOVE); // button, id

    toolButton = new QPushButton("Create Connecting Lane");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TJE_CREATE_LANE); // button, id

    toolButton = new QPushButton("Create Connecting Road");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TJE_CREATE_ROAD); // button, id

    QFrame *line = new QFrame();
    line->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line->setLineWidth(1);
    toolLayout->addWidget(line, ++row, 0, 1, ColumnCount);

    toolButton = new QPushButton("Create Junction from selected elements");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TJE_CREATE_JUNCTION); // button, id
    //	toolButton->setChecked(true);

    junctionLabel = new QLabel(tr("Junction"));
    toolLayout->addWidget(junctionLabel, ++row, 0, 1, ColumnCount);

    toolButton = new QPushButton("Select");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TJE_SELECT_JUNCTION); // button, id

    toolButton = new QPushButton("Add Selected Roads");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TJE_ADD_TO_JUNCTION); // button, id

    toolButton = new QPushButton("Remove Selected Roads");
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, row, 1);
    toolGroup->addButton(toolButton, ODD::TJE_REMOVE_FROM_JUNCTION); // button, id

    line = new QFrame();
    line->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line->setLineWidth(1);
    toolLayout->addWidget(line, ++row, 0, 1, ColumnCount);

    toolButton = new QPushButton("Link Selected Roads");
    toolButton->setCheckable(false);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TJE_LINK_ROADS); // button, id

    toolButton = new QPushButton("Unlink Selected Roads");
    toolButton->setCheckable(false);
    toolLayout->addWidget(toolButton, ++row, 0, 1, ColumnCount);
    toolGroup->addButton(toolButton, ODD::TJE_UNLINK_ROADS); // button, id

    line = new QFrame();
    line->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line->setLineWidth(1);
    toolLayout->addWidget(line, ++row, 0, 1, ColumnCount);

    // Circular cutting tool //
    //
    cuttingCircleButton_ = new QPushButton(tr("Circular Cut"));
    cuttingCircleButton_->setCheckable(false);
    toolLayout->addWidget(cuttingCircleButton_, ++row, 0);
    toolGroup->addButton(cuttingCircleButton_, ODD::TJE_CIRCLE); // button, id

    connect(cuttingCircleButton_, SIGNAL(toggled(bool)), this, SLOT(cuttingCircle(bool)));

    // Threshold //
    //
    QLabel *thresholdLabel = new QLabel("Threshold:");
    thresholdEdit_ = new QDoubleSpinBox();
    thresholdEdit_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    thresholdEdit_->setRange(0.0, 1000.0);
    thresholdEdit_->setValue(10.0);
    thresholdEdit_->setMinimumWidth(80.0);
    thresholdEdit_->setMaximumWidth(80.0);

    toolLayout->addWidget(thresholdLabel, row, 1);
    toolLayout->addWidget(thresholdEdit_, row, 2);

    connect(thresholdEdit_, SIGNAL(editingFinished()), this, SLOT(setThreshold()));

    // Finish Layout //
    //
    toolLayout->setRowStretch(++row, 1); // row x fills the rest of the availlable space
    toolLayout->setColumnStretch(ColumnCount, 1); // column 2 fills the rest of the availlable space

    // Widget/Layout //
    //
    ToolWidget *toolWidget = new ToolWidget();
    toolWidget->setLayout(toolLayout);
    toolManager_->addToolBoxWidget(toolWidget, tr("Junction Editor"));
    connect(toolWidget, SIGNAL(activated()), this, SLOT(activateEditor()));
}