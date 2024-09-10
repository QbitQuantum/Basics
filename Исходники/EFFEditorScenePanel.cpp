	QWidget * createWidget (QWidget * pParent)
	{
		QToolButton * pToolButton = new QToolButton(pParent);
		pToolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
		pToolButton->setPopupMode(QToolButton::InstantPopup);
		pToolButton->setMinimumHeight(TOOLBAR_MIN_HEIGHT);
		pToolButton->setMinimumWidth(80);

		QMenu * pMenu = new QMenu(pToolButton);
		pMenu->addMenu(tr("RGB"));
		pMenu->addMenu(tr("Alpha"));
		pMenu->addMenu(tr("Overdraw"));
		pMenu->addMenu(tr("Mipmaps"));

		pToolButton->setMenu(pMenu);
		return pToolButton;
	}