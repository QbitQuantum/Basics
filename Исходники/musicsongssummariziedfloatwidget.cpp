MusicSongsSummariziedFloatWidget::MusicSongsSummariziedFloatWidget(QWidget *parent)
    : QLabel(parent)
{
    setWindowFlags( Qt::Window | Qt::FramelessWindowHint );
    setObjectName("MainWidget");
    setStyleSheet("#MainWidget{background:rgba(0, 0, 0, 60);}");

    resize(60, 25);
    MusicUtils::widgetToRound(this, 10, 10);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    QToolButton *locationButton = new QToolButton(this);
    QToolButton *searchButton = new QToolButton(this);
    layout->addWidget(locationButton);
    layout->addWidget(searchButton);

    locationButton->setIcon(QIcon(QString::fromUtf8(":/appTools/location")));
    locationButton->setIconSize(QSize(20, 20));
    locationButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    locationButton->setCursor(QCursor(Qt::PointingHandCursor));
    searchButton->setIcon(QIcon(QString::fromUtf8(":/appTools/search")));
    searchButton->setIconSize(QSize(20, 20));
    searchButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    searchButton->setCursor(QCursor(Qt::PointingHandCursor));
    connect(locationButton, SIGNAL(clicked()), SIGNAL(musicCurrentPlayLocation()));
    connect(searchButton, SIGNAL(clicked()), SIGNAL(musicSearch()));

    m_currentAnimationValue = 1;
    m_timer.setInterval(3*1000);
    connect(&m_timer, SIGNAL(timeout()), SLOT(leaveTimeout()));

    m_animation = new QPropertyAnimation(this, "windowOpacity");
    m_animation->setDuration(1000);
    connect(m_animation, SIGNAL(finished()), SLOT(animationFinished()));

    M_CONNECTION->setValue("MusicSongsSummariziedFloatWidget", this);
    M_CONNECTION->poolConnect("MusicSongsSummariziedFloatWidget", "MusicBottomAreaWidget");
    M_CONNECTION->poolConnect("MusicSongsSummariziedFloatWidget", "MusicApplication");
    m_timer.start();
}