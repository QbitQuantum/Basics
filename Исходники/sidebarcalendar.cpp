void SideBarCalendar::setUpViewMiniCalendar(){

    miniCal = new CustomCalendarWidget;
    QToolButton* next = new QToolButton;
    QToolButton* prev = new QToolButton;
    QPushButton* today = new QPushButton("Aujourd'hui");
    year = new QLabel(QString::number(miniCal->selectedDate().year()));
    month = new QLabel(QDate::longMonthName(miniCal->selectedDate().month()));

    QString styleToolButton = "QToolButton {background-color: rgba(0,0,0,0)}";
    QSize sizeToolButton(24,24);
    next->setIcon(QIcon(":/icons/img/icons/ic_chevron_right_48px.svg"));
    next->setStyleSheet(styleToolButton);
    next->setIconSize(sizeToolButton);
    next->setCursor(Qt::PointingHandCursor);

    prev->setIcon(QIcon(":/icons/img/icons/ic_chevron_left_48px.svg"));
    prev->setStyleSheet(styleToolButton);
    prev->setIconSize(sizeToolButton);
    prev->setCursor(Qt::PointingHandCursor);

    /* Infos jour sélectionné
     * Contient : No du jour et nom du jour de la semaine
     */
    currentDayCal = new DayWidget;
    currentDayCal->setDayName(QDate::longDayName(miniCal->selectedDate().dayOfWeek()));
    currentDayCal->setDayNumber(miniCal->selectedDate().day());

    /* Header
     * Contient: Bouton next, prev, mois et année
     */
    QWidget* header = new QWidget;
    header->setStyleSheet("QLabel{font-size: 16px;}");
    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->addWidget(prev);
    headerLayout->addStretch(1);
    headerLayout->addWidget(month);
    headerLayout->addWidget(year);
    headerLayout->addStretch(1);
    headerLayout->addWidget(next);
    header->setLayout(headerLayout);

    /*
     * Layout principale
     * Contient: Header et Calendar
     */
    layoutMiniCalendar = new QVBoxLayout;

    layoutMiniCalendar->addWidget(currentDayCal);
    layoutMiniCalendar->addWidget(header);
    layoutMiniCalendar->addWidget(today, 0, Qt::AlignCenter);
    layoutMiniCalendar->addWidget(miniCal, 0, Qt::AlignHCenter);
    layoutMiniCalendar->addStretch(1);
    miniCal->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    miniCal->setFixedHeight(280);
    miniCal->setFixedWidth(280);

    connect(prev, SIGNAL(clicked()), miniCal, SLOT(showPreviousMonth()));
    connect(next, SIGNAL(clicked()), miniCal, SLOT(showNextMonth()));
    connect(miniCal, SIGNAL(currentPageChanged(int,int)), this, SLOT(pageChanged(int,int)));
    connect(miniCal, SIGNAL(selectionChanged()), this, SLOT(onDayClicked()));
    connect(today, SIGNAL(clicked()), this, SLOT(onTodayClicked()));

    viewMiniCalendar->setLayout(layoutMiniCalendar);
}