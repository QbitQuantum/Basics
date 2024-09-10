KviMircTextColorSelector::KviMircTextColorSelector(QWidget * par,const QString &txt,unsigned int * uFore,unsigned int * uBack,bool bEnabled)
: KviTalHBox(par), KviSelectorInterface()
{
	m_pLabel = new QLabel(txt,this);

	m_pButton = new QPushButton(__tr2qs("Sample Text"),this);
	// m_pButton->setMinimumWidth(150);
	connect(m_pButton,SIGNAL(clicked()),this,SLOT(buttonClicked()));

	setSpacing(4);
	setStretchFactor(m_pLabel,1);

	m_pUFore = uFore;
	m_pUBack = uBack;

	m_uBack = *uBack;
	m_uFore = *uFore;

	setButtonPalette();

	setEnabled(bEnabled);

    m_pContextPopup = new QMenu(this);

    QAction *pAction = 0;
    m_pForePopup = new QMenu(this);
    connect(m_pForePopup,SIGNAL(triggered(QAction*)),this,SLOT(foreSelected(QAction*)));
    int iColor;
    for(iColor=0;iColor<KVI_MIRCCOLOR_MAX_FOREGROUND;iColor++)
	{
		QPixmap tmp(120,16);
        tmp.fill(KVI_OPTION_MIRCCOLOR(iColor));
        pAction = m_pForePopup->addAction(tmp,QString("x"));
        pAction->setData(iColor);
	}
    pAction = m_pContextPopup->addAction(__tr2qs("Foreground"));
    pAction->setMenu(m_pForePopup);

    m_pBackPopup = new QMenu(this);
    connect(m_pBackPopup,SIGNAL(triggered(QAction*)),this,SLOT(backSelected(QAction*)));
    pAction = m_pBackPopup->addAction(__tr2qs("Transparent"));
    pAction->setData(KviControlCodes::Transparent);
    for(iColor=0;iColor<KVI_MIRCCOLOR_MAX_BACKGROUND;iColor++)
	{
		QPixmap tmp(120,16);
        tmp.fill(KVI_OPTION_MIRCCOLOR(iColor));
        pAction = m_pBackPopup->addAction(tmp,QString("x"));
        pAction->setData(iColor);
	}
    pAction = m_pContextPopup->addAction(__tr2qs("Background"));
    pAction->setMenu(m_pBackPopup);
}