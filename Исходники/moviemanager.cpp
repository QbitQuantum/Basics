void moviemanager::setupUserInterface()
{
    mainWindow = new QWidget(this);
    mainHLayout = new QHBoxLayout(mainWindow);

    firstVLayout = new QVBoxLayout(mainWindow);
    secondVLayout = new QVBoxLayout(mainWindow);
    thirdVLayout = new QVBoxLayout(mainWindow);
    mainHLayout->addItem(firstVLayout);
    mainHLayout->addItem(secondVLayout);
    mainHLayout->addItem(thirdVLayout);
    //add layouting information here

    //adding widgets into the firstVLayout
    //adding searchbar
    QHBoxLayout* searchHLayout = new QHBoxLayout(mainWindow);
    firstVLayout->addItem(searchHLayout);
    searchHLayout->addWidget(new QLabel("Search:", mainWindow));
    searchBar = new KLineEdit("", mainWindow);
    searchHLayout->addWidget(searchBar);
    searchHLayout->setAlignment(Qt::AlignTop); //searchbar alignment
    //connecting searchbar return pressed to a slot
    if(connect(searchBar,
               SIGNAL(returnPressed(QString)),
               this,
               SLOT(slotSearchBarReturnPressed(QString))) == false)
    {
        qDebug() << "searchBar connect is not successful";
    }

    //adding klistwidget for displaying movies
    mainMovieList = new KListWidget(mainWindow);
    mainMovieList->setSortingEnabled(true);
    fetchAllMovieList(mainMovieList);
    firstVLayout->addWidget(mainMovieList);
    //connecting the mainMovieList signal to a slot
    if(connect(mainMovieList,
               SIGNAL(activated(QModelIndex)),
               this,
               SLOT(slotMovieClicked(QModelIndex))) == false)
    {
        qDebug() << "mainMovieList connect is not successful";
    }

    //adding widgets into secondVLayout
    secondVLayout->addWidget(new QLabel("<span style='font-size: 20px;'>Movie Details</span>", mainWindow));
    QScrollArea * scrollArea = new QScrollArea(mainWindow);
    //scrollArea->setLayout();
    //scrollArea->setAlignment(Qt::AlignBottom);
    secondVLayout->addWidget(scrollArea);
    scrollArea->setWidgetResizable(false);
    //scrollArea->setVerticalScrollBar(new QScrollBar());
    middleInnerWidget = new QWidget(mainWindow);
    //middleInnerWidget->setMaximumHeight(50);
    scrollArea->setWidget(middleInnerWidget);
    //secondVLayout->addWidget(middleInnerWidget);
    middleInnerVLayout = new QVBoxLayout(middleInnerWidget);
    scrollArea->setLayout(middleInnerVLayout);
    QLabel* tempTitle = new QLabel("<span style='font-size: 20px;'>Title</span>", middleInnerWidget);
    tempTitle->setAlignment(Qt::AlignTop);
    middleInnerVLayout->addWidget(tempTitle);

    artwork = new QWebView(middleInnerWidget);
    artwork->load(QUrl("file:///home/sandeep/.moviemanager/tt0000000.jpg"));
    artwork->setMinimumSize(320,474);
    artwork->setMaximumSize(320,474);
    middleInnerVLayout->addWidget(artwork);


    //adding widgets into thirdVLayout
    thirdVLayout->addWidget(new QLabel("<span style='font-size: 20px;'>Recommended Movies</span>", mainWindow));
    recoMovieList = new KListWidget(mainWindow);
    recoMovieList->setSortingEnabled(true);
    fetchRecoMovieList(recoMovieList);
    thirdVLayout->addWidget(recoMovieList);
    //connecting the mainMovieList signal to a slot
    if(connect(recoMovieList,
               SIGNAL(activated(QModelIndex)),
               this,
               SLOT(slotMovieClicked(QModelIndex))) == false)
    {
        qDebug() << "recoMovieList connect is not successful";
    }



    setCentralWidget(mainWindow);
}