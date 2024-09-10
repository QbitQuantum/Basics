KviIrcViewToolWidget::KviIrcViewToolWidget(KviIrcView * pParent)
: QWidget(pParent)
{
	m_pIrcView = pParent;
	setAutoFillBackground(true);
	setContentsMargins(0,0,0,0);

	QHBoxLayout * pLayout = new QHBoxLayout(this);
	pLayout->setMargin(2);
	pLayout->setSpacing(2);

	QPushButton * pButton = new QPushButton(QIcon(*g_pIconManager->getSmallIcon(KviIconManager::Close)), QString(),this);
	pButton->setFixedSize(16,16);
	pButton->setFlat(true);
	connect(pButton,SIGNAL(clicked()),m_pIrcView,SLOT(toggleToolWidget()));
	pLayout->addWidget(pButton);

	m_pStringToFind = new KviThemedLineEdit(this, m_pIrcView->parentKviWindow(), "search_lineedit");
	pLayout->addWidget(m_pStringToFind);
	connect(m_pStringToFind,SIGNAL(returnPressed()),this,SLOT(findNext()));
	connect(m_pStringToFind,SIGNAL(textChanged(QString)),this,SLOT(findNextHelper(QString)));

	pButton = new QPushButton(__tr2qs("&Next"),this);
	pButton->setDefault(true);
	connect(pButton,SIGNAL(clicked()),this,SLOT(findNext()));
	pLayout->addWidget(pButton);

	pButton = new QPushButton(__tr2qs("&Previous"),this);
	connect(pButton,SIGNAL(clicked()),this,SLOT(findPrev()));
	pLayout->addWidget(pButton);

	m_pOptionsButton = new QPushButton(this);
	m_pOptionsButton->setText(__tr2qs("&Options"));
	pLayout->addWidget(m_pOptionsButton);

	m_pOptionsWidget = new QMenu(m_pOptionsButton);
	QGridLayout * pOptionsLayout = new QGridLayout(m_pOptionsWidget);
	pOptionsLayout->setSpacing(2);

	connect(m_pOptionsButton, SIGNAL(clicked()), this, SLOT(toggleOptions()));

	// Filter tab

	QLabel * pLabel = new QLabel(__tr2qs("Message Types"), m_pOptionsWidget); //groupbox title
	pOptionsLayout->addWidget(pLabel,0,0,1,2);

	m_pFilterView = new QTreeWidget(m_pOptionsWidget);
	m_pFilterView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pFilterView->setRootIsDecorated(false);
	//FIXME hardcoded size sucks
	m_pFilterView->setMinimumSize(QSize(200,150));
	m_pFilterView->setColumnCount(1);
	m_pFilterView->header()->hide();
	pOptionsLayout->addWidget(m_pFilterView,1,0,4,2);

	m_pFilterItems = (KviIrcMessageCheckListItem **)KviMemory::allocate(KVI_NUM_MSGTYPE_OPTIONS * sizeof(KviIrcMessageCheckListItem *));

	for(int i=0;i<KVI_NUM_MSGTYPE_OPTIONS;i++)
	{
		m_pFilterItems[i] = new KviIrcMessageCheckListItem(m_pFilterView,this,i);
	}

	pButton = new QPushButton(__tr2qs("Set &All"),m_pOptionsWidget);
	connect(pButton,SIGNAL(clicked()),this,SLOT(filterEnableAll()));
	pOptionsLayout->addWidget(pButton,6,0);

	pButton = new QPushButton(__tr2qs("Set &None"),m_pOptionsWidget);
	connect(pButton,SIGNAL(clicked()),this,SLOT(filterEnableNone()));
	pOptionsLayout->addWidget(pButton,6,1);

	pButton = new QPushButton(__tr2qs("&Load from..."),m_pOptionsWidget);
	connect(pButton,SIGNAL(clicked()),this,SLOT(filterLoad()));
	pOptionsLayout->addWidget(pButton,7,0);

	pButton = new QPushButton(__tr2qs("&Save As..."),m_pOptionsWidget);
	connect(pButton,SIGNAL(clicked()),this,SLOT(filterSave()));
	pOptionsLayout->addWidget(pButton,7,1);

	pLabel = new QLabel(__tr2qs("Pattern:"),m_pOptionsWidget);
	pOptionsLayout->addWidget(pLabel,8,0);
	m_pSearchMode = new QComboBox(m_pOptionsWidget);
    m_pSearchMode->insertItem(PlainText, __tr2qs("Plain Text"));
    m_pSearchMode->insertItem(Wildcards, __tr2qs("Wildcards"));
    m_pSearchMode->insertItem(RegExp, __tr2qs("RegExp"));
	pOptionsLayout->addWidget(m_pSearchMode,8,1);

	pLabel = new QLabel(__tr2qs("Match:"),m_pOptionsWidget);
	pOptionsLayout->addWidget(pLabel,9,0);

	m_pCaseSensitive = new QCheckBox(__tr2qs("&Case sensitive"),m_pOptionsWidget);
	pOptionsLayout->addWidget(m_pCaseSensitive,9,1);

// 	m_pFindResult = new QLabel(this);
// 	m_pFindResult->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
// 	pOptionsLayout->addWidget(m_pFindResult,0,6);

	// Focussing the 'string to find' widget has been moved to the toggle function so that it happens whenever the widget is shown

	KviShortcut::create(Qt::Key_Escape,m_pIrcView,SLOT(toggleToolWidget()),0,Qt::WidgetWithChildrenShortcut);
	KviShortcut::create(KVI_SHORTCUTS_WIN_SEARCH,m_pIrcView,SLOT(toggleToolWidget()),0,Qt::WidgetWithChildrenShortcut);
}