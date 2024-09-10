void
CrossfallEditorTool::initToolWidget()
{
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

    toolButton = new QPushButton(tr("Select"));
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TCF_SELECT); // button, id
    toolButton->setChecked(true);

    //	toolButton = new QPushButton(tr("Move Section"));
    //	toolButton->setCheckable(true);
    //	toolLayout->addWidget(toolButton, ++row, 0);
    //	toolGroup->addButton(toolButton, ODD::TCF_MOVE); // button, id

    toolButton = new QPushButton(tr("Add Section"));
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TCF_ADD); // button, id

    toolButton = new QPushButton(tr("Del Section"));
    toolButton->setCheckable(true);
    toolLayout->addWidget(toolButton, ++row, 0);
    toolGroup->addButton(toolButton, ODD::TCF_DEL); // button, id

    QLabel *radiusLabel = new QLabel("Smooth Radius:");
    radiusEdit_ = new QDoubleSpinBox();
    radiusEdit_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    radiusEdit_->setRange(0.01, 1000000.0);
    radiusEdit_->setValue(2000.0);
    radiusEdit_->setMinimumWidth(80.0);
    radiusEdit_->setMaximumWidth(80.0);

    toolLayout->addWidget(radiusLabel, ++row, 0);
    toolLayout->addWidget(radiusEdit_, ++row, 0);

    connect(radiusEdit_, SIGNAL(editingFinished()), this, SLOT(setRadius()));

    // Finish Layout //
    //
    toolLayout->setRowStretch(++row, 1); // row 3 fills the rest of the availlable space
    toolLayout->setColumnStretch(1, 1); // column 1 fills the rest of the availlable space

    // Widget/Layout //
    //
    ToolWidget *toolWidget = new ToolWidget();
    toolWidget->setLayout(toolLayout);
    toolManager_->addToolBoxWidget(toolWidget, tr("Crossfall Editor"));
    connect(toolWidget, SIGNAL(activated()), this, SLOT(activateEditor()));

    // Ribbon //
    //

    ToolWidget *ribbonWidget = new ToolWidget();
    //ribbonWidget->
    Ui::CrossfallRibbon *ui = new Ui::CrossfallRibbon();
    ui->setupUi(ribbonWidget);
    
    QButtonGroup *ribbonToolGroup = new QButtonGroup;
    connect(ribbonToolGroup, SIGNAL(buttonClicked(int)), this, SLOT(handleToolClick(int)));
    
    
    ribbonToolGroup->addButton(ui->crossfallSelect, ODD::TSE_SELECT);
    ribbonToolGroup->addButton(ui->crossfallAdd, ODD::TSE_ADD);
    ribbonToolGroup->addButton(ui->crossfallDelete, ODD::TSE_DEL);
    //ribbonToolGroup->addButton(ui->elevationSmooth, ODD::TSE_SMOOTH);
    
    connect(ui->radiusEdit, SIGNAL(editingFinished()), this, SLOT(setRadius()));

    toolManager_->addRibbonWidget(ribbonWidget, tr("Crossfall"));
    connect(ribbonWidget, SIGNAL(activated()), this, SLOT(activateEditor()));
}