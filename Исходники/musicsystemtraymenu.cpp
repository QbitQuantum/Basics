void MusicSystemTrayMenu::createPlayWidgetActions()
{
    m_widgetAction = new QWidgetAction(this);
    QWidget *widgetActionContainer = new QWidget(this);
    QVBoxLayout *vbox = new QVBoxLayout(widgetActionContainer);
    vbox->setMargin(0);

    QWidget *widgetContainer = new QWidget(widgetActionContainer);
    QHBoxLayout *box = new QHBoxLayout(widgetContainer);
    box->setMargin(0);

    QToolButton *previousPlay = new QToolButton(widgetContainer);
    QToolButton *nextPlay = new QToolButton(widgetContainer);
    m_PlayOrStop = new QToolButton(widgetContainer);

    previousPlay->setIcon(QIcon(QString::fromUtf8(":/contextMenu/sysprevious")));
    nextPlay->setIcon(QIcon(QString::fromUtf8(":/contextMenu/sysnext")));
    m_PlayOrStop->setIcon(QIcon(QString::fromUtf8(":/contextMenu/sysplay")));

    previousPlay->setIconSize(QSize(40, 40));
    nextPlay->setIconSize(QSize(40, 40));
    m_PlayOrStop->setIconSize(QSize(45, 45));

    previousPlay->setStyleSheet(MusicUIObject::MToolButtonStyle01);
    nextPlay->setStyleSheet(MusicUIObject::MToolButtonStyle01);
    m_PlayOrStop->setStyleSheet(MusicUIObject::MToolButtonStyle01);

    previousPlay->setCursor(QCursor(Qt::PointingHandCursor));
    nextPlay->setCursor(QCursor(Qt::PointingHandCursor));
    m_PlayOrStop->setCursor(QCursor(Qt::PointingHandCursor));

    previousPlay->setToolTip(tr("Previous"));
    nextPlay->setToolTip(tr("Next"));
    m_PlayOrStop->setToolTip(tr("Play"));

    box->addWidget(previousPlay);
    box->addWidget(m_PlayOrStop);
    box->addWidget(nextPlay);

    m_showText = new QLabel(widgetActionContainer);
    m_showText->setAlignment(Qt::AlignCenter);
    m_showText->setStyleSheet(MusicUIObject::MCustomStyle12);
    vbox->addWidget(widgetContainer);
    vbox->addWidget(m_showText);
    widgetActionContainer->setLayout(vbox);
    m_widgetAction->setDefaultWidget(widgetActionContainer);

    connect(previousPlay, SIGNAL(clicked()), parent(), SLOT(musicPlayPrevious()));
    connect(nextPlay, SIGNAL(clicked()), parent(), SLOT(musicPlayNext()));
    connect(m_PlayOrStop, SIGNAL(clicked()), parent(), SLOT(musicStatePlay()));
}