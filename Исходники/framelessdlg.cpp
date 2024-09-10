void FramelessDlg::InitTitleBar()
{
	QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());

	m_closeBtn = new QToolButton(this);
	QToolButton* minBtn = new QToolButton(this);
	QToolButton* menuBtn = new QToolButton(this);

	m_subTitle = new QLabel(this);
	m_subTitle->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

	m_closeBtn->setObjectName("closeBtn");
	minBtn->setObjectName("minBtn");
	menuBtn->setObjectName("menuBtn");
	m_subTitle->setObjectName("subTitle");

	menuBtn->setPopupMode(QToolButton::InstantPopup);
	m_menu = new QMenu(this);
	menuBtn->setMenu(m_menu);

	m_closeBtn->setFixedSize(27, 22);
	minBtn->setFixedSize(27, 22);
	menuBtn->setFixedSize(27, 22);
	m_subTitle->setFixedSize(400, 25);

	connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(reject()));
	connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));

	QFrame* tb = new QFrame(this);
	tb->setObjectName("titleBar");
	QHBoxLayout* tbLayout = new QHBoxLayout;
	m_title = new QLabel(this);
	m_title->setObjectName("label_title");
	m_title->setFixedSize(300, 25);

	tbLayout->addWidget(m_title);
	tbLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Fixed));

	if ( m_flag & SUB_TITLE )
		tbLayout->addWidget(m_subTitle);

	if ( m_flag & MENU_BUTTON )
		tbLayout->addWidget(menuBtn);

	if ( m_flag & MIN_BUTTON )
		tbLayout->addWidget(minBtn);

	if ( m_flag & CLOSE_BUTTON )
		tbLayout->addWidget(m_closeBtn);

	tb->setLayout(tbLayout);
	layout->addWidget(tb);
}