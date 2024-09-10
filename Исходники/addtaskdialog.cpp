AddTaskDialog::AddTaskDialog(SharedData * pSharedData) : QDialog(NULL, Qt::Dialog|Qt::WindowSystemMenuHint){
    int currentRobot;
    QString name;
    bool bAdd;

    setModal(true);
    m_pSharedData = pSharedData;

    m_pAddButton = new QPushButton(tr("Add Task"));
    m_pCancelButton = new QPushButton(tr("Cancel"));

    connect(m_pAddButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_pCancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    m_pRobotLabel = new QLabel(tr("Robot:"));
    m_pRobotList = new QComboBox();
    m_pRobotList->setEditable(false);
    connect(m_pRobotList, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateWaypointList(int)));

    m_pWaypointList = new QListWidget;

    m_pUp = new QPushButton(QIcon("images/up.png"), "");
    m_pDown = new QPushButton(QIcon("images/down.png"), "");
    connect(m_pUp, SIGNAL(clicked()), this, SLOT(MoveUp()));
    connect(m_pDown, SIGNAL(clicked()), this, SLOT(MoveDown()));

    // Add robots to list    
    for(int iter = 0; iter < MAX_NUM_ROBOTS; iter++){
	
	bAdd = false;
	m_pSharedData->Lock();
	if(m_pSharedData->DoesRobotExist(iter)){
	    bAdd = true;
	    name.clear();
	    name.append(m_pSharedData->GetRobotData(iter)->configuration.name);
	}
	m_pSharedData->Unlock();

	if(bAdd){
	    m_pRobotList->addItem(name, QVariant(iter));
	}
    }

    // Set the current robot as the active list item
    m_pSharedData->Lock();
    currentRobot = (int)m_pSharedData->GetCurrentRobot();
    m_pSharedData->Unlock();
    m_pRobotList->setCurrentIndex(m_pRobotList->findData(currentRobot));

    UpdateWaypointList(m_pRobotList->currentIndex());

    m_pTaskLabel = new QLabel(tr("Task:"));
    m_pTaskList = new QComboBox;
    connect(m_pTaskList, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateSelectedTask(int)));
    m_pTaskList->addItem(tr("Waypoint"), QVariant((int)TASK_WAYPOINT));
    m_pTaskList->addItem(tr("Take chemical sample"), QVariant((int)TASK_CHEMICAL_SAMPLE));
    m_pTaskList->addItem(tr("Take dirt sample"), QVariant((int)TASK_DIRT_SAMPLE));
    m_pTaskList->setCurrentIndex(TASK_WAYPOINT);
    m_lSelectedTask = TASK_WAYPOINT;

    QHBoxLayout * pRobotLayout = new QHBoxLayout;
    pRobotLayout->addStretch();
    pRobotLayout->addWidget(m_pRobotLabel);
    pRobotLayout->addWidget(m_pRobotList);
    pRobotLayout->addStretch();

    QHBoxLayout * pWaypointLayout = new QHBoxLayout;
    pWaypointLayout->addWidget(m_pWaypointList);
    QVBoxLayout * pUpDownLayout = new QVBoxLayout;
    pUpDownLayout->addStretch();
    pUpDownLayout->addWidget(m_pUp);
    pUpDownLayout->addWidget(m_pDown);
    pUpDownLayout->addStretch();
    pWaypointLayout->addLayout(pUpDownLayout);

    QHBoxLayout * pAddCancelLayout = new QHBoxLayout;
    pAddCancelLayout->addWidget(m_pAddButton);
    pAddCancelLayout->addWidget(m_pCancelButton);

    QHBoxLayout * pTaskLayout = new QHBoxLayout;
    pTaskLayout->addWidget(m_pTaskLabel);
    pTaskLayout->addWidget(m_pTaskList);

    QVBoxLayout * pMainLayout = new QVBoxLayout;
    pMainLayout->addLayout(pRobotLayout);
    pMainLayout->addLayout(pWaypointLayout);
    pMainLayout->addLayout(pTaskLayout);
    pMainLayout->addLayout(pAddCancelLayout);

    setLayout(pMainLayout);
}