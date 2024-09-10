CCustomer::CCustomer(QWidget *parent) :
    QWidget(parent)
  , actualRecords(false)
  , ui(new Ui::CCustomer)
  , customerDialog(new CCustomerDialog(this)), customer_gDialog(new CCustomer_gDialog(this))
  , discountDialog(new CDiscountDialog(this))
  , addItem(new CAddItem(this))
  , focusedWidget(nullptr)
{
    ui->setupUi(this);

// model
    modelFaces    = new QStandardItemModel(this);
    modelPartner  = new QStandardItemModel(this);
    modelHuman    = new QStandardItemModel(this);

    modelSelectionFaces   = new QItemSelectionModel(modelFaces);
    modelSelectionPartner = new QItemSelectionModel(modelPartner);
    modelSelectionHuman   = new QItemSelectionModel(modelHuman);

// create #temporary table
    QString query ("SELECT * INTO #GroupCustomerDiscounts FROM ViewGroupCustomerDiscounts"
                   "SELECT * INTO #CustomerSubdiller FROM ViewCustomerSubdiller");
    QSqlQuery temporary(currentDatabase());
    temporary.exec(query);

    QSplitter *hSplitter = new QSplitter(Qt::Horizontal);
    QSplitter *vSplitter = new QSplitter(Qt::Vertical);

    QWidget *w1 = new QWidget(this);
    QWidget *w2 = new QWidget(this);

    treeFaces          = new QTreeView (this);
    treePartner        = new CCustomerTreeView (this);
    textEditPartnerComment = new QTextEdit (this);
    textEditPartnerComment->setMaximumWidth(100);
    textEditPartnerComment->setReadOnly(true);
    treeHuman          = new CCustomerTreeView (this);
    textEditHumanComment   = new QTextEdit (this);
    textEditHumanComment->setMaximumWidth(100);
    textEditHumanComment->setReadOnly(true);

    QHBoxLayout *hboxPartner = new QHBoxLayout(w1);
                 hboxPartner->setMargin(0);
                 hboxPartner->addWidget(treePartner);
                 hboxPartner->addWidget(textEditPartnerComment);

    QHBoxLayout *hboxHuman = new QHBoxLayout(w2);
                 hboxHuman->setMargin(0);
                 hboxHuman->addWidget(treeHuman);
                 hboxHuman->addWidget(textEditHumanComment);

    vSplitter->addWidget(w1);
    vSplitter->addWidget(w2);
    vSplitter->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    ui->vLayoutUnionPartnerHuman->addWidget(vSplitter);

    hSplitter->addWidget(treeFaces);
    hSplitter->addWidget(vSplitter);
    hSplitter->setStretchFactor(1, 3);
    hSplitter->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    ui->hLayoutUnionViews->addWidget(hSplitter);

    treeFaces->setObjectName("treeViewFaces");
    treeFaces->setModel(modelFaces);
    treeFaces->setSelectionModel(modelSelectionFaces);
    treeFaces->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treeFaces->installEventFilter(this);

    treePartner->setObjectName("treeViewPartner");
    treePartner->setRootIsDecorated(false);
    treePartner->setAlternatingRowColors(true);
    treePartner->setModel(modelPartner);
    treePartner->setSelectionModel(modelSelectionPartner);
    treePartner->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treePartner->installEventFilter(this);

    treeHuman->setObjectName("treeViewHuman");
    treeHuman->setRootIsDecorated(false);
    treeHuman->setAlternatingRowColors(true);
    treeHuman->setModel(modelHuman);
    treeHuman->setSelectionModel(modelSelectionHuman);
    treeHuman->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treeHuman->installEventFilter(this);

    filter = new CFilter(this);
    filter->setObjectName("filter");
    filter->setPlaceholderText("Введите наименование");
    filter->installEventFilter(this);
    filter->setValidator(new QRegExpValidator(QRegExp(trUtf8("[а-яА-Яa-zA-Z0-9_]+")), this));
    ui->hLayoutSearchToItem->addWidget(filter);

    QToolButton *telephone = new QToolButton(this);
    QPixmap pixmapTelephone("data/picture/additionally/telephone.png");

    telephone->setIcon(QIcon(pixmapTelephone));
    telephone->setIconSize(QSize(24, 24));
    telephone->setCursor(Qt::PointingHandCursor);
    telephone->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    ui->hLayoutSearchToItem->addWidget(telephone);

    QToolButton *meeting = new QToolButton(this);
    QPixmap pixmapMeeting("data/picture/additionally/meeting.png");

    meeting->setIcon(QIcon(pixmapMeeting));
    meeting->setIconSize(QSize(24, 24));
    meeting->setCursor(Qt::PointingHandCursor);
    meeting->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    ui->hLayoutSearchToItem->addWidget(meeting);

    QToolButton *event = new QToolButton(this);
    QPixmap pixmapEvent("data/picture/additionally/event.png");

    event->setIcon(QIcon(pixmapEvent));
    event->setIconSize(QSize(24, 24));
    event->setCursor(Qt::PointingHandCursor);
    event->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    ui->hLayoutSearchToItem->addWidget(event);

    QToolButton *task = new QToolButton(this);
    QPixmap pixmapTask("data/picture/additionally/task.png");

    task->setIcon(QIcon(pixmapTask));
    task->setIconSize(QSize(24, 24));
    task->setCursor(Qt::PointingHandCursor);
    task->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    ui->hLayoutSearchToItem->addWidget(task);

    ui->labelCurrentUser->setText(QString("Пользователь: <b><u>" + currentUser() + "</u></b>"));

    mc.idCustomer      = -1;
    mc.nameCustomer    = QString("");

    root = new QStandardItem(QString("Заказчики"));
    root->setIcon(QIcon("data/picture/additionally/root.png"));
    modelFaces->insertColumns(0, FACES_MODEL_COLUMN_COUNT);
    modelFaces->setItem(0, 0, root);

    QFont font(treeFaces->font());
          font.setBold (true);
    modelFaces->setData(modelFaces->index(0, 0), font, Qt::FontRole);
    modelFaces->setHeaderData(0, Qt::Horizontal, QObject::tr("Наименование"));

    QVector<int> storage;
                 storage.append(1);
                 storage.append(2);
                 storage.append(3);
    CDictionaryCore::columnHidden(treeFaces, modelFaces, storage);
                 storage.clear();

    root->setChild(modelFaces->rowCount(root->index()), new QStandardItem("Загрузка..."));

    modelPartner->insertColumns(0, PARTNER_MODEL_COLUMN_COUNT);

    modelPartner->setHeaderData(0, Qt::Horizontal, "Контрагенты");
    modelPartner->setHeaderData(1, Qt::Horizontal, "Клиентский №");
    modelPartner->setHeaderData(2, Qt::Horizontal, "Телефон");
    modelPartner->setHeaderData(3, Qt::Horizontal, "Город");
    modelPartner->setHeaderData(4, Qt::Horizontal, "Web");
    modelPartner->setHeaderData(5, Qt::Horizontal, "Руководитель");

    modelHuman->insertColumns(0, HUMAN_MODEL_COLUMN_COUNT);

    modelHuman->setHeaderData(0, Qt::Horizontal, "ФИО");
    modelHuman->setHeaderData(1, Qt::Horizontal, "Отдел");
    modelHuman->setHeaderData(2, Qt::Horizontal, "Должность");
    modelHuman->setHeaderData(3, Qt::Horizontal, "Телефон");
    modelHuman->setHeaderData(4, Qt::Horizontal, "Приоритет");

//    connect(filter, SIGNAL(textChanged(QString)), SLOT(slotFindCities(QString)));
    connect(treeFaces, SIGNAL(expanded(QModelIndex)),  SLOT(slotFillGroup(QModelIndex)));
    connect(treeFaces, SIGNAL(collapsed(QModelIndex)), SLOT(slotClearGroup(QModelIndex)));
    connect(treeFaces, SIGNAL(clicked(QModelIndex)),   SLOT(slotFillPartner(QModelIndex)));

//    connect(treeViewCountry, SIGNAL(clicked(QModelIndex)),
//            this, SLOT(slotDataChanged(QModelIndex)));
//    connect(editDialogCountry, SIGNAL(saveDataChanged()), this, SLOT(slotInsertOrUpdateRecords()));
//    connect(editDialogCity, SIGNAL(saveDataChanged()), this, SLOT(slotInsertOrUpdateRecords()));
//    connect(addItem->ui->buttonSave, SIGNAL(clicked()), countryDialog, SLOT(show()));

    connect(addItem->ui->buttonSave, SIGNAL(clicked()), SLOT(slotShowEditDialog()));
    connect(addItem->ui->buttonSave, SIGNAL(clicked()), addItem, SLOT(close()));

    actualRecords
             ? ui->labelViewState->setText(QString(tr("Отображаются записи: <b><u>Актуальные</u></b>")))
             :
               ui->labelViewState->setText(QString(tr("Отображаются записи: <b><u>Все</u></b>")));
}