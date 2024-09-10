GlobalScoresWindow::GlobalScoresWindow(QWidget *parent)
    : QDialog(parent){
    // Creates the 3 buttons that will be used in the dialog window
    searchButton = new QPushButton(tr("Search"));
    stopButton = new QPushButton(tr("Stop"));
    quitButton = new QPushButton(tr("Quit"));
    stopButton->setEnabled(false);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(establishConnection()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    // Sets up a table widget for the global scoreboard
    table = new QTableWidget(this);
    table->setColumnCount(3);
    tableHeader << "Rank" << "Name" << "Score";
    table->setHorizontalHeaderLabels(tableHeader);
    table->verticalHeader()->setVisible(false);
    table->setFixedHeight(342);

    // Creates the layout for the Global Scores window
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addSpacing(6);
    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addSpacing(250);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addSpacing(20);
    mainLayout->addWidget(table, 0, Qt::AlignVCenter);
    mainLayout->addSpacing(6);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(20);
    setLayout(mainLayout);

    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(updateScoreTable()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(connectionError()));

    // Sets the title and size of the window
    setWindowTitle("Global High Scores");
    setFixedSize(450, 400);
}