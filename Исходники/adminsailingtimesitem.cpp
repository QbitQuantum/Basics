AdminSailingTimesItem::AdminSailingTimesItem(QString id, QString cat, SaverDbSailingTimes data, QStringList islands, QWidget *parent) : QWidget(parent) {

	allData = data;
	this->islands = islands;
	this->id = id;
	category = cat;

	fromIsland = (data.from == cat);
	toIsland = (data.to == cat);

	// THIS IS THE LAYOUT STRUCTURE:
	/****************************************************************************************
	 *		islands				time	*			*	*
	 ********************************************************	dates		*  del	*
	 *			days				*			*	*
	 ****************************************************************************************/



	// The first row containing the islands and the time


	QLabel *labelSailingFrom = new QLabel("Sailing from");
	labelSailingFrom->setStyleSheet("font-weight: bold");


	QLabel *islandFixed = new QLabel(cat);
	islandFixed->setStyleSheet("font-weight: bold");

	QLabel *labelSailingTo = new QLabel("to");
	labelSailingTo->setStyleSheet("font-weight: bold");

	islandVariable = new QComboBox;
	islandVariable->setStyleSheet("font-weight: bold");
	islandVariable->addItem("Mainland");
	for(int j = 0; j < islands.length(); ++j) {
		islandVariable->addItem(islands.at(j));
		if(islands.at(j) == data.to && !fromIsland) islandVariable->setCurrentIndex(j+1);
	}
	if((fromIsland && !toIsland) || (!fromIsland && toIsland)) islandVariable->setCurrentIndex(0);



	QLabel *timeLabel = new QLabel("at");
	timeLabel->setStyleSheet("font-weight: bold");
	time = new Clock;
	time->setStyleSheet("font-weight: bold");
	time->setTime(QTime(data.sailingtime/100,data.sailingtime%100));


	QHBoxLayout *islandTimesLay = new QHBoxLayout;
	islandTimesLay->addWidget(labelSailingFrom);
	if(fromIsland) islandTimesLay->addWidget(islandFixed);
	else islandTimesLay->addWidget(islandVariable);
	islandTimesLay->addWidget(labelSailingTo);
	if(fromIsland) islandTimesLay->addWidget(islandVariable);
	else islandTimesLay->addWidget(islandFixed);
	islandTimesLay->addWidget(timeLabel);
	islandTimesLay->addWidget(time);
	islandTimesLay->addSpacing(10);
	islandTimesLay->addStretch();



	// The part containing checkboxes for all the days


	QHBoxLayout *dayLay = new QHBoxLayout;

	QStringList days;
	days << "Mo" << "Tue" << "Wed" << "Thu" << "Fri" << "Sat" << "Sun";
	for(int j = 0; j < days.length(); ++j) {
		QCheckBox *ch = new QCheckBox(days.at(j));
		ch->setCursor(Qt::PointingHandCursor);
		allDays.append(ch);
		if(data.daysofweek.at(j) == *"1") ch->setChecked(true);
		dayLay->addWidget(ch);
	}

	QVBoxLayout *islandsTimesDaysLay = new QVBoxLayout;
	islandsTimesDaysLay->addLayout(islandTimesLay);
	islandsTimesDaysLay->addLayout(dayLay);


	// the two rows of dates (start and end)

	QLabel *dateStartLabel = new QLabel("Starting:");
	dateStart = new DateEdit(150,"dd MMMM yyyy");
	dateStart->setDate(data.start);
	dateStart->setNoDateLimits();
	QHBoxLayout *dateStartLay = new QHBoxLayout;
	dateStartLay->addWidget(dateStartLabel);
	dateStartLay->addWidget(dateStart);

	QLabel *dateEndLabel = new QLabel("Ending:");
	dateEnd = new DateEdit(150,"dd MMMM yyyy");
	dateEnd->setDate(data.end);
	dateEnd->setNoDateLimits();
	QHBoxLayout *dateEndLay = new QHBoxLayout;
	dateEndLay->addWidget(dateEndLabel);
	dateEndLay->addWidget(dateEnd);

	QVBoxLayout *dateLay = new QVBoxLayout;
	dateLay->addLayout(dateStartLay);
	dateLay->addLayout(dateEndLay);


	// A delete button

	QPushButton *del = new QPushButton("X");
	del->setFixedWidth(40);
	del->setCursor(Qt::PointingHandCursor);
	del->setStyleSheet("font-weight: bold; color: red");
	connect(del, SIGNAL(clicked()), this, SLOT(delClicked()));



	// The main layout combining all the elements above

	QHBoxLayout *lay = new QHBoxLayout;
	lay->addStretch();
	lay->addLayout(islandsTimesDaysLay);
	lay->addSpacing(10);
	lay->addLayout(dateLay);
	lay->addSpacing(10);
	lay->addWidget(del);
	lay->addStretch();

	this->setLayout(lay);

}