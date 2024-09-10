/** Constructor */
WikiDialog::WikiDialog(QWidget *parent)
: MainPage(parent)
{
	/* Invoke the Qt Designer generated object setup routine */
	ui.setupUi(this);

	mAddPageDialog = NULL;
	mAddGroupDialog = NULL;
	mEditDialog = NULL;

	connect( ui.toolButton_NewGroup, SIGNAL(clicked()), this, SLOT(OpenOrShowAddGroupDialog()));
	connect( ui.toolButton_NewPage, SIGNAL(clicked()), this, SLOT(OpenOrShowAddPageDialog()));
	connect( ui.toolButton_Edit, SIGNAL(clicked()), this, SLOT(OpenOrShowEditDialog()));
	connect( ui.toolButton_Republish, SIGNAL(clicked()), this, SLOT(OpenOrShowRepublishDialog()));

	// Usurped until Refresh works normally
	connect( ui.toolButton_Delete, SIGNAL(clicked()), this, SLOT(insertWikiGroups()));
	connect( ui.pushButton, SIGNAL(clicked()), this, SLOT(todo()));

	connect( ui.treeWidget_Pages, SIGNAL(itemSelectionChanged()), this, SLOT(groupTreeChanged()));


	// GroupTreeWidget.
	connect(ui.groupTreeWidget, SIGNAL(treeCustomContextMenuRequested(QPoint)), this, SLOT(groupListCustomPopupMenu(QPoint)));
	connect(ui.groupTreeWidget, SIGNAL(treeItemActivated(QString)), this, SLOT(wikiGroupChanged(QString)));


	QTimer *timer = new QTimer(this);
	timer->connect(timer, SIGNAL(timeout()), this, SLOT(checkUpdate()));
	timer->start(1000);

	/* setup TokenQueue */
	mWikiQueue = new TokenQueue(rsWiki->getTokenService(), this);


	/* Setup Group Tree */
	mYourGroups = ui.groupTreeWidget->addCategoryItem(tr("My Groups"), QIcon(IMAGE_FOLDER), true);
	mSubscribedGroups = ui.groupTreeWidget->addCategoryItem(tr("Subscribed Groups"), QIcon(IMAGE_FOLDERRED), true);
	mPopularGroups = ui.groupTreeWidget->addCategoryItem(tr("Popular Groups"), QIcon(IMAGE_FOLDERGREEN), false);
	mOtherGroups = ui.groupTreeWidget->addCategoryItem(tr("Other Groups"), QIcon(IMAGE_FOLDERYELLOW), false);

  //Auto refresh seems not to work, temporary solution at start
  insertWikiGroups();

}