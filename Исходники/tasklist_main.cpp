//Sets up layout that combines left and right panes
TaskList_Main::TaskList_Main(QWidget *parent) :
    QMainWindow(parent)
{
    listPane = new tasklist_lists(this);
    listPane->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    notePane = new tasklist_notes(this);
    notePane->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    optionPane = new tasklist_options(this);
    optionPane->setHidden(true);
    expButton = new QPushButton("");

    expButton->setAutoFillBackground(true);
    expButton->setIcon(QIcon(":img/icon/right_arrow.png"));
    expButton->setIconSize(QSize(15,300));
    expButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);

    QHBoxLayout *paneLayout = new QHBoxLayout;
    paneLayout->addWidget(listPane);
    paneLayout->addWidget(notePane);
    paneLayout->addWidget(expButton);
    paneLayout->addWidget(optionPane);

    //Set the central widget (work-around)
    QWidget *central = new QWidget();
    central->setLayout(paneLayout);
    this->setCentralWidget(central);
    createMenu();
    setMenuBar(menuBar);

    //Connect signals between different panes
    connect(expButton, SIGNAL(clicked()), this, SLOT(expClick()));
    connect(optionPane, SIGNAL(noteInfoSent(QListWidgetItem&)), notePane, SLOT(applyClicked(QListWidgetItem&)));
    connect(notePane, SIGNAL(itemSelectEmit(QListWidgetItem&)), optionPane, SLOT(itemSelectDataIn(QListWidgetItem&)));
    connect(optionPane, SIGNAL(cancelPane()), this, SLOT(expClick()));
    connect(this, SIGNAL(createList(QString)), listPane, SLOT(newList(const QString &)));
    connect(listPane, SIGNAL(listSelectEmit(QListWidgetItem*)), notePane, SLOT(listChanged(QListWidgetItem*)));
}