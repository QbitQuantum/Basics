void MaterialEditDialog::createControls()
{    
    lstProperties = new QListWidget(this);
    lstProperties->setMouseTracking(true);
    lstProperties->setMaximumWidth(200);

    connect(lstProperties, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(doPropertyChanged(QListWidgetItem *, QListWidgetItem *)));

    txtName = new QLineEdit();
    txtDescription = new QLineEdit();

    QGridLayout *layoutNameAndDescription = new QGridLayout();
    layoutNameAndDescription->addWidget(new QLabel(tr("Name:")), 0, 0);
    layoutNameAndDescription->addWidget(txtName, 0, 1);
    layoutNameAndDescription->addWidget(new QLabel(tr("Description:")), 1, 0);
    layoutNameAndDescription->addWidget(txtDescription, 2, 0, 1, 3);

    QPushButton *btnAddProperty = new QPushButton(tr("Add..."));
    btnAddProperty->setDefault(false);

    QAction *actAddCustom = new QAction(tr("Custom property"), this);
    connect(actAddCustom, SIGNAL(triggered()), this, SLOT(addProperty()));

    // TODO: more general
    QAction *actAddThermalConductivity = new QAction(tr("Thermal conductivity"), this);
    connect(actAddThermalConductivity, SIGNAL(triggered()), this, SLOT(addPropertyThermalConductivity()));
    QAction *actAddSpecificHeat = new QAction(tr("Specific heat"), this);
    connect(actAddSpecificHeat, SIGNAL(triggered()), this, SLOT(addPropertySpecificHeat()));
    QAction *actAddDensity = new QAction(tr("Density"), this);
    connect(actAddDensity, SIGNAL(triggered()), this, SLOT(addPropertyDensity()));
    QAction *actAddMagneticPermeability = new QAction(tr("Magnetic permeability"), this);
    connect(actAddMagneticPermeability, SIGNAL(triggered()), this, SLOT(addPropertyMagneticPermeability()));

    QMenu *menu = new QMenu();
    menu->addAction(actAddCustom);
    menu->addSeparator();
    menu->addAction(actAddThermalConductivity);
    menu->addAction(actAddSpecificHeat);
    menu->addAction(actAddDensity);
    menu->addSeparator();
    menu->addAction(actAddMagneticPermeability);

    btnAddProperty->setMenu(menu);

    btnDeleteProperty = new QPushButton(tr("Delete"));
    btnDeleteProperty->setDefault(false);
    connect(btnDeleteProperty, SIGNAL(clicked()), this, SLOT(deleteProperty()));

    QGridLayout *layoutList = new QGridLayout();
    layoutList->addWidget(lstProperties, 0, 0, 1, 2);
    layoutList->addWidget(btnAddProperty, 1, 0);
    layoutList->addWidget(btnDeleteProperty, 1, 1);

    propertyGUI = createPropertyGUI();

    QHBoxLayout *layoutNonlinearProperties = new QHBoxLayout();
    layoutNonlinearProperties->addLayout(layoutList);
    layoutNonlinearProperties->addWidget(propertyGUI, 1);

    // table
    txtPropertyTableKeys = new QPlainTextEdit();
    txtPropertyTableValues = new QPlainTextEdit();

    QGridLayout *layoutTable = new QGridLayout();
    layoutTable->addWidget(new QLabel(tr("Keys:")), 0, 0);
    layoutTable->addWidget(txtPropertyTableKeys, 1, 0);
    layoutTable->addWidget(new QLabel(tr("Values:")), 0, 1);
    layoutTable->addWidget(txtPropertyTableValues, 1, 1);

    widNonlinearTable = new QGroupBox(tr("Table"));
    widNonlinearTable->setLayout(layoutTable);

    // function
    txtPropertyFunction = new ScriptEditor(currentPythonEngine(), this);
    txtPropertyFunctionFrom = new LineEditDouble(0.0);
    txtPropertyFunctionTo = new LineEditDouble(0.0);

    QGridLayout *layoutFunction = new QGridLayout();
    layoutFunction->addWidget(txtPropertyFunction, 0, 0, 1, 4);
    layoutFunction->addWidget(new QLabel(tr("From:")), 1, 0);
    layoutFunction->addWidget(txtPropertyFunctionFrom, 1, 1);
    layoutFunction->addWidget(new QLabel(tr("To:")), 1, 2);
    layoutFunction->addWidget(txtPropertyFunctionTo, 1, 3);
    layoutFunction->setRowStretch(0, 1);

    widNonlinearFunction = new QGroupBox(tr("Nonlinear function"));
    widNonlinearFunction->setLayout(layoutFunction);

    chartNonlinear = new QCustomPlot();
    chartNonlinear->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    chartNonlinear->setMinimumHeight(120);
    chartNonlinear->addGraph();
    chartNonlinear->graph(0)->setLineStyle(QCPGraph::lsLine);

    QHBoxLayout *layoutChartNonlinear = new QHBoxLayout();
    layoutChartNonlinear->addWidget(chartNonlinear);

    widChartNonlinear = new QGroupBox(tr("Chart"));
    widChartNonlinear->setLayout(layoutChartNonlinear);

    layoutNonlinearType = new QStackedLayout();
    layoutNonlinearType->addWidget(widNonlinearFunction);
    layoutNonlinearType->addWidget(widNonlinearTable);

    QHBoxLayout *layoutNonlinearChart = new QHBoxLayout();
    layoutNonlinearChart->addLayout(layoutNonlinearType, 2);
    layoutNonlinearChart->addWidget(widChartNonlinear, 1);

    QVBoxLayout *layoutNonlinear = new QVBoxLayout();
    layoutNonlinear->addLayout(layoutNonlinearProperties);
    layoutNonlinear->addLayout(layoutNonlinearChart, 1);

    // dialog buttons
    QPushButton *btnPlot = new QPushButton(tr("Plot"));
    connect(btnPlot, SIGNAL(clicked()), this, SLOT(drawChart()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->addButton(btnPlot, QDialogButtonBox::ActionRole);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(doAccept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layoutNameAndDescription);
    layout->addLayout(layoutNonlinear, 1);
    layout->addStretch();
    layout->addWidget(buttonBox);

    setLayout(layout);
}