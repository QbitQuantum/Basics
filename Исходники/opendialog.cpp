OpenDialog::OpenDialog(QGraphicsWidget*, const QString &currentFileName)
{
    MWidget *centralWidget = new MWidget;
    MLayout *layout = new MLayout();
    layout->setContentsMargins(0,0,0,0);

    MLinearLayoutPolicy* landscapePolicy = new MLinearLayoutPolicy(layout, Qt::Vertical);
    MLinearLayoutPolicy* portraitPolicy = new MLinearLayoutPolicy(layout, Qt::Vertical);

  //  m_itemSize.setWidth(100);
  //  m_itemSize.setHeight(100);

    m_columnsPortrait = 4;
    m_columnsLandscape = 5;
    m_columnsLandscapeSlider = 0;
    m_columnsPortraitSlider = 0;


    list = new MList(this);
    list->setObjectName("list");
    landscapePolicy->addItem(list);
    portraitPolicy->addItem(list);

    landscapePolicy->setContentsMargins(20, 12, 20, 0);
    portraitPolicy->setContentsMargins(20, 24, 20, 0);

    layout->setLandscapePolicy(landscapePolicy);
    layout->setPortraitPolicy(portraitPolicy);


    //int initialWidth = MApplication::activeWindow()->visibleSceneSize().width();

  /*  if(MApplication::activeWindow()->orientation() == M::Portrait) {
        list->setColumns(m_columnsPortrait);
        m_itemSize.setWidth(initialWidth / m_columnsPortrait);
        m_itemSize.setHeight(m_itemSize.width());
    }
    else {
        list->setColumns(m_columnsLandscape);
        m_itemSize.setWidth(initialWidth / m_columnsLandscape);
        m_itemSize.setHeight(m_itemSize.width());
    }*/

    m_itemSize.setWidth(110);
    m_itemSize.setHeight(110);

    ContentItemCreator *cellCreator = new ContentItemCreator(this);
    list->setCellCreator(cellCreator);

    QStringList mediaDirs;
    mediaDirs << APP_CATALOG;

    model = new OpenDialogModel(this, m_itemSize.toSize(), mediaDirs, currentFileName);
    model->setObjectName("gridModel");
    list->setItemModel(model);

    connect(list, SIGNAL(itemClicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));
    connect(list, SIGNAL(panningStarted()), this, SLOT(pauseLoaders()));
    connect(list, SIGNAL(panningStopped()), this, SLOT(resumeLoaders()));

    centralWidget->setLayout(layout);
    this->setTitle("Choose an image");
    this->setModal(true);
    this->setCentralWidget(centralWidget);
}