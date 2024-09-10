LatexLogWidget::LatexLogWidget(QWidget *parent) :
    QWidget(parent), logModel(0), displayPartsActions(0),filterErrorAction(0),filterWarningAction(0),filterBadBoxAction(0),logpresent(false)
{
	logModel = new LatexLogModel(this);//needs loaded line marks

	errorTable = new QTableView(this);
	int rowHeight = getOptimalRowHeight(errorTable);
	errorTable->verticalHeader()->setDefaultSectionSize(rowHeight);
	QFontMetrics fm(QApplication::font());
	errorTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	errorTable->setSelectionMode(QAbstractItemView::SingleSelection);
	errorTable->setColumnWidth(0,fm.width("> "));
	errorTable->setColumnWidth(1,20*fm.width("w"));
	errorTable->setColumnWidth(2,fm.width("WarningW"));
	errorTable->setColumnWidth(3,fm.width("Line WWWWW"));
	errorTable->setColumnWidth(4,20*fm.width("w"));
	connect(errorTable, SIGNAL(clicked(const QModelIndex &)), this, SLOT(clickedOnLogModelIndex(const QModelIndex &)));

	errorTable->horizontalHeader()->setStretchLastSection(true);
	errorTable->setMinimumHeight(5*rowHeight);
	errorTable->setFrameShape(QFrame::NoFrame);
	errorTable->setSortingEnabled(true);

	proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(logModel);
	errorTable->setModel(proxyModel);

	QAction * act = new QAction(tr("&Copy"),errorTable);
	connect(act, SIGNAL(triggered()), SLOT(copyMessage()));
	errorTable->addAction(act);
	act = new QAction(tr("&Copy All"),errorTable);
	connect(act, SIGNAL(triggered()), SLOT(copyAllMessages()));
	errorTable->addAction(act);
	act = new QAction(tr("&Copy All With Line Numbers"),errorTable);
	connect(act, SIGNAL(triggered()), SLOT(copyAllMessagesWithLineNumbers()));
	errorTable->addAction(act);
	errorTable->setContextMenuPolicy(Qt::ActionsContextMenu);

	log = new LogEditor(this);
	log->setFocusPolicy(Qt::ClickFocus);
	log->setMinimumHeight(3*(fm.lineSpacing()+4));
	log->setReadOnly(true);
	connect(log, SIGNAL(clickOnLogLine(int)),this,SLOT(gotoLogLine(int)));

	QSplitter *splitter = new QSplitter(Qt::Vertical, this);
	splitter->setChildrenCollapsible(false);
	splitter->addWidget(errorTable);
	splitter->addWidget(log);

	infoLabel = new QLabel(tr("No log file available"), this);
	infoLabel->setStyleSheet("background: #FFFBBF;");
	infoLabel->setMargin(2);

	QVBoxLayout* vLayout = new QVBoxLayout(); //contains the widgets for the normal mode (OutputTable + OutputLogTextEdit)
	vLayout->setSpacing(0);
	vLayout->setMargin(0);
	vLayout->addWidget(infoLabel);
	vLayout->addWidget(splitter);
	setLayout(vLayout);

	displayPartsActions = new QActionGroup(this);
	displayPartsActions->setExclusive(true);
	connect(displayPartsActions, SIGNAL(triggered(QAction*)), this, SLOT(changeDisplay(QAction *)));
	displayTableAction = new QAction(tr("Issues"), displayPartsActions);
	displayTableAction->setData(qVariantFromValue(DisplayTable));
	displayTableAction->setCheckable(true);
	displayLogAction = new QAction(tr("Log File"), displayPartsActions);
	displayLogAction->setData(qVariantFromValue(DisplayLog));
	displayLogAction->setCheckable(true);
	displayLogAndTableAction = new QAction(tr("Issues and Log"), displayPartsActions);
	displayLogAndTableAction->setData(qVariantFromValue(DisplayLogAndTable));
	displayLogAndTableAction->setCheckable(true);
    filterErrorAction = new QAction(QIcon(":/images-ng/error.svgz"),tr("Show Error"),this);
    filterErrorAction->setCheckable(true);
    filterErrorAction->setChecked(true);
    connect(filterErrorAction,SIGNAL(toggled(bool)),this,SLOT(filterChanged(bool)));
    filterWarningAction = new QAction(QIcon(":/images-ng/warning.svgz"),tr("Show Warning"),this);
    filterWarningAction->setCheckable(true);
    filterWarningAction->setChecked(true);
    connect(filterWarningAction,SIGNAL(toggled(bool)),this,SLOT(filterChanged(bool)));
    filterBadBoxAction = new QAction(QIcon(":/images-ng/badbox.svg"),tr("Show BadBox"),this);
    filterBadBoxAction->setCheckable(true);
    filterBadBoxAction->setChecked(true);
    connect(filterBadBoxAction,SIGNAL(toggled(bool)),this,SLOT(filterChanged(bool)));

	setDisplayParts(DisplayTable);
}