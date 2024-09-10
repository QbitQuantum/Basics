// ****************************************************************************
// Constructor:  ELPipelineBuilder::ELPipelineBuilder
//
// Programmer:  Jeremy Meredith
// Creation:    August  2, 2012
//
// Modifications:
// ****************************************************************************
ELPipelineBuilder::ELPipelineBuilder(QWidget *parent)
    : QWidget(parent)
{
    currentPipeline = -1;

    // Top layout
    QGridLayout *topLayout = new QGridLayout(this);
    pipelineChooser = new QComboBox(this);
    connect(pipelineChooser, SIGNAL(activated(int)), 
            this, SLOT(activatePipeline(int)));
    topLayout->addWidget(new QLabel("Pipeline: ", this), 0,0, 1,1);
    topLayout->addWidget(pipelineChooser, 0,1, 1,1);

    QPushButton *newPipelineBtn = new QPushButton("New Pipeline", this);
    topLayout->addWidget(newPipelineBtn, 1,0, 1,2);
    connect(newPipelineBtn, SIGNAL(clicked()),
            this, SLOT(NewPipeline()));

    QSplitter *topSplitter = new QSplitter(Qt::Vertical, this);
    topLayout->addWidget(topSplitter, 3, 0, 1, 2);

    QGroupBox *pipelineGroup = new QGroupBox("Pipeline",
                                             topSplitter);

    QGridLayout *pipelineLayout = new QGridLayout(pipelineGroup);

    //
    // The pipeline tree
    //
    tree = new QTreeWidget(pipelineGroup);
    tree->setHeaderLabels(QStringList() << "Operation" << "Settings");
    //tree->setHeaderHidden(true);
    pipelineLayout->addWidget(tree, 0,0);
    connect(tree, SIGNAL(itemSelectionChanged()),
            this, SLOT(rowSelected()));

    //
    // The operator menu
    //
    QMenu *opMenu = new QMenu();
    ///\todo: these choice names must currently match the exact text in
    /// Operation::GetOperationName.  We should loosed this restriction.
    const char *operations[] = {
        "Isosurface",
        "Elevate",
        "ExternalFace",
        "Histogram",
        "SurfaceNormals",
        "Transform",
        NULL
    };
    for (int i=0; operations[i] != NULL; i++)
    {
        QAction *op= opMenu->addAction(operations[i]);
        op->setData(QString(operations[i]));
        connect(op, SIGNAL(triggered()), this, SLOT(newOperation()));
    }
    QPushButton *addOpButton = new QPushButton("Add Operation", pipelineGroup);
    addOpButton->setMenu(opMenu);
    pipelineLayout->addWidget(addOpButton, 1,0);

    //
    // add execute button (probably not the best place for it)
    //
    QPushButton *deleteOpButton = new QPushButton("Delete Operation", pipelineGroup);
    pipelineLayout->addWidget(deleteOpButton, 2, 0);
    connect(deleteOpButton, SIGNAL(clicked()),
            this, SLOT(deleteCurrentOp()));


    //
    // add execute button (probably not the best place for it)
    //
    QPushButton *executeButton = new QPushButton("Execute", pipelineGroup);
    pipelineLayout->addWidget(executeButton, 3, 0);
    connect(executeButton, SIGNAL(clicked()),
            this, SLOT(executePipeline()));

    //
    // Settings
    //
    settingsGroup = new QGroupBox("Settings", topSplitter);
    QGridLayout *settingsLayout = new QGridLayout(settingsGroup);

    //
    // sources widgets
    //
    sourceSettings = new ELSources(settingsGroup);
    connect(sourceSettings, SIGNAL(sourceChanged()),
            this, SLOT(sourceUpdated()));
    settingsLayout->addWidget(sourceSettings);

    topSplitter->setStretchFactor(0,30);
    topSplitter->setStretchFactor(1,50);

    // add one pipeline
    Pipeline::allPipelines.push_back(new Pipeline);
    activatePipeline(0);
    pipelineChooser->addItem("");
}