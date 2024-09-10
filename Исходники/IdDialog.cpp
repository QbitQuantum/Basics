/** Constructor */
IdDialog::IdDialog(QWidget *parent)
: MainPage(parent)
{
	ui.setupUi(this);

	mEditDialog = NULL;
	//mPulseSelected = NULL;

	ui.radioButton_ListAll->setChecked(true);
	connect( ui.pushButton_NewId, SIGNAL(clicked()), this, SLOT(OpenOrShowAddDialog()));
	connect( ui.pushButton_EditId, SIGNAL(clicked()), this, SLOT(OpenOrShowEditDialog()));
	connect( ui.treeWidget_IdList, SIGNAL(itemSelectionChanged()), this, SLOT(updateSelection()));

	connect( ui.radioButton_ListYourself, SIGNAL(toggled( bool ) ), this, SLOT(ListTypeToggled( bool ) ) );
	connect( ui.radioButton_ListFriends, SIGNAL(toggled( bool ) ), this, SLOT(ListTypeToggled( bool ) ) );
	connect( ui.radioButton_ListOthers, SIGNAL(toggled( bool ) ), this, SLOT(ListTypeToggled( bool ) ) );
	connect( ui.radioButton_ListPseudo, SIGNAL(toggled( bool ) ), this, SLOT(ListTypeToggled( bool ) ) );
	connect( ui.radioButton_ListAll, SIGNAL(toggled( bool ) ), this, SLOT(ListTypeToggled( bool ) ) );

	QTimer *timer = new QTimer(this);
	timer->connect(timer, SIGNAL(timeout()), this, SLOT(checkUpdate()));
	timer->start(1000);

	rsIdentity->generateDummyData();

	mIdQueue = new TokenQueue(rsIdentity, this);

}