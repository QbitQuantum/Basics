/** Constructor */
BlogsDialog::BlogsDialog(QWidget *parent)
: MainPage (parent)
{
  	/* Invoke the Qt Designer generated object setup routine */
  	setupUi(this);

  	connect(actionCreate_Blog, SIGNAL(triggered()), this, SLOT(createBlog()));
  	connect(postButton, SIGNAL(clicked()), this, SLOT(createMsg()));
  	connect(subscribeButton, SIGNAL( clicked( void ) ), this, SLOT( subscribeBlog ( void ) ) );
  	connect(unsubscribeButton, SIGNAL( clicked( void ) ), this, SLOT( unsubscribeBlog ( void ) ) );
  	
    connect(treeView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(selectBlog(const QModelIndex &)));
    connect(treeView, SIGNAL(activated(const QModelIndex &)), this, SLOT(toggleSelection(const QModelIndex &)));
    connect(treeView, SIGNAL(customContextMenuRequested( QPoint ) ), this, SLOT( blogListCustomPopupMenu( QPoint ) ) );

  	mBlogId = "";
  	mPeerId = rsPeers->getOwnId(); // add your id

    model = new QStandardItemModel(0, 2, this);
    model->setHeaderData(0, Qt::Horizontal, tr("Name"), Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, tr("ID"), Qt::DisplayRole);

    treeView->setModel(model);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    treeView->setItemDelegate(new ChanGroupDelegate());

    // hide header and id column
    treeView->setHeaderHidden(true);
    treeView->hideColumn(1);
    
    itemFont = QFont("ARIAL", 10);
    itemFont.setBold(true);
	
    QStandardItem *OwnBlogs = new QStandardItem(tr("My Blogs"));
    OwnBlogs->setForeground(QBrush(QColor(79, 79, 79)));
    OwnBlogs->setFont(itemFont);
    
    QStandardItem *SubscribedBlogs = new QStandardItem(tr("Subscribed Blogs"));
    SubscribedBlogs->setForeground(QBrush(QColor(79, 79, 79)));
    SubscribedBlogs->setFont(itemFont);

    QStandardItem *PopularBlogs = new QStandardItem(tr("Popular Blogs"));
    PopularBlogs->setForeground(QBrush(QColor(79, 79, 79)));
    PopularBlogs->setFont(itemFont);

    QStandardItem *OtherBlogs = new QStandardItem(tr("Other Blogs"));
    OtherBlogs->setForeground(QBrush(QColor(79, 79, 79)));        
    OtherBlogs->setFont(itemFont);

    model->appendRow(OwnBlogs);
    model->appendRow(SubscribedBlogs);
    model->appendRow(PopularBlogs);
    model->appendRow(OtherBlogs);

    //added from ahead
    updateBlogList();

    mBlogFont = QFont("MS SANS SERIF", 22);
    nameLabel->setFont(mBlogFont);    
    nameLabel->setMinimumWidth(20);
		   
    QMenu *blogmenu = new QMenu();
    blogmenu->addAction(actionCreate_Blog); 
    blogmenu->addSeparator();
    blogpushButton->setMenu(blogmenu);
	
    QTimer *timer = new QTimer(this);
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(checkUpdate()));
    timer->start(1000);
}