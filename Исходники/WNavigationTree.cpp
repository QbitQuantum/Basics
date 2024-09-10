WNavigationTreeCaption::WNavigationTreeCaption()
	{
	QToolButton * pwButtonUndock = new QToolButton(this);
	pwButtonUndock->setToolTip("Float / Unfloat");
	#if 1
	pwButtonUndock->setStyleSheet("QToolButton { border: none; padding: 3px; }");
	#else
	pwButtonUndock->setStyleSheet("QToolButton { border: none; padding: 0px; }");
	#endif
	QPixmap oPixmap = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
	pwButtonUndock->setIcon(oPixmap);
//	pwButtonUndock->setMaximumSize(oPixmap.size());
	pwButtonUndock->setCursor(Qt::ArrowCursor);
	pwButtonUndock->setFocusPolicy(Qt::ClickFocus);

	QHBoxLayout * layout = new QHBoxLayout(this);
	layout->setMargin(0);
//	layout->setSpacing(10);
//	layout->addStretch();
	#if 0
	layout->addWidget(g_pwButtonStatusOfNavigationTree, Qt::AlignLeft | Qt::AlignHCenter);
	#endif
	layout->addWidget(g_pwButtonSwitchProfile); // , Qt::AlignLeft | Qt::AlignHCenter);
	//layout->addWidget(new QWidget);
	layout->addStretch();
	//layout->addWidget(pwButtonUndock, Qt::AlignRight | Qt::AlignHCenter);
	layout->addWidget(pwButtonUndock);
	setLayout(layout);
	connect(pwButtonUndock, SIGNAL(clicked()), g_pwNavigationTree, SLOT(SL_ToggleDocking()));
	setCursor(Qt::OpenHandCursor);		// This cursor shows to the user he/she may drag the widget to undock the Navigation Tree
	}