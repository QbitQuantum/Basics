/** Constructor */
LinksDialog::LinksDialog(RsPeers *peers, RsFiles *files, QWidget *parent)
: MainPage(parent), mPeers(peers), mFiles(files)
{
  /* Invoke the Qt Designer generated object setup routine */
  ui.setupUi(this);

  connect( ui.linkTreeWidget, SIGNAL( customContextMenuRequested( QPoint ) ), this, SLOT( linkTreeWidgetCostumPopupMenu( QPoint ) ) );


  /* link combos */
  connect( ui.rankComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( changedSortRank( int ) ) );
  connect( ui.periodComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( changedSortPeriod( int ) ) );
  connect( ui.fromComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( changedSortFrom( int ) ) );
  connect( ui.topComboBox, SIGNAL( currentIndexChanged( int ) ), this, SLOT( changedSortTop( int ) ) );

  /* add button */
  connect( ui.addButton, SIGNAL( clicked( void ) ), this, SLOT( addLinkComment( void ) ) );
  connect( ui.expandButton, SIGNAL( clicked( void ) ), this, SLOT( toggleWindows( void ) ) );
  
  connect( ui.addToolButton, SIGNAL( clicked( ) ), this, SLOT( addNewLink( ) ) );

  connect( ui.linkTreeWidget, SIGNAL( currentItemChanged ( QTreeWidgetItem *, QTreeWidgetItem * ) ),
  		this, SLOT( changedItem ( QTreeWidgetItem *, QTreeWidgetItem * ) ) );

  connect( ui.linkTreeWidget, SIGNAL( itemDoubleClicked ( QTreeWidgetItem *, int ) ),
  		this, SLOT( openLink ( QTreeWidgetItem *, int ) ) );

  connect( ui.anonBox, SIGNAL( stateChanged ( int ) ), this, SLOT( checkAnon ( void  ) ) );

  mStart = 0;


    /* Set header resize modes and initial section sizes */
	QHeaderView * _header = ui.linkTreeWidget->header () ;
  _header->setResizeMode (0, QHeaderView::Interactive);
	_header->setResizeMode (1, QHeaderView::Interactive);
	_header->setResizeMode (2, QHeaderView::Interactive);

	_header->resizeSection ( 0, 400 );
	_header->resizeSection ( 1, 60 );
	_header->resizeSection ( 2, 150 );

	ui.linkTreeWidget->setSortingEnabled(true);
	
	ui.linklabel->setMinimumWidth(20);


	/* Set a GUI update timer - much cleaner than
	 * doing everything through the notify agent
	 */

  QTimer *timer = new QTimer(this);
  timer->connect(timer, SIGNAL(timeout()), this, SLOT(checkUpdate()));
  timer->start(1000);

  /* Hide platform specific features */
#ifdef Q_WS_WIN

#endif

}