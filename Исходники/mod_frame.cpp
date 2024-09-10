	/* Constructor */
	ModFrame::ModFrame(FilterWin *parent) : QFrame(parent), filterWin(parent)
	{
		// base layout
		QVBoxLayout * layout = new QVBoxLayout;
		QVBoxLayout * vbox;
		QHBoxLayout * hbox;
		QFrame * frame;
		int i;
		// mode div
		frame = new QFrame;
		vbox = new QVBoxLayout;
		frame->setLayout(vbox);
		addLabelRow(vbox, "Mode:");
		hbox = new QHBoxLayout;
		modeRadios[MOVIESOAP_SKIP] = addRadio(hbox, "&Skip");
		modeRadios[MOVIESOAP_MUTE] = addRadio(hbox, "&Mute");
		modeRadios[MOVIESOAP_BLACKOUT] = addRadio(hbox, "&Blackout");
		QPushButton *blackoutButton = addButton(hbox, "S&et blackout bounds");
		connect( blackoutButton, SIGNAL(clicked()), this, SLOT(blackoutClicked()) );
		vbox->addLayout(hbox);
		layout->addWidget(frame);
		// time div
		addLabelRow(layout, "Time:");
		hbox = new QHBoxLayout;
		hbox->addWidget(new QLabel(tr("from")));
		startText = addText(hbox, "00:00:00.00");
		startText->setFixedWidth(110);
		hbox->addWidget(new QLabel(tr("to")));
		stopText = addText(hbox, "00:00:00.00");
		stopText->setFixedWidth(110);
		hbox->addWidget(new QLabel(tr("title")));
		titleText = addText(hbox, "-1");
		titleText->setFixedWidth(50);
		layout->addLayout(hbox);
		// severity/tolerance div
		frame = new QFrame;
		vbox = new QVBoxLayout;
		frame->setLayout(vbox);
		addLabel(vbox, "Offensiveness (scarcely <-> very)");
		hbox = new QHBoxLayout;
		for (i = 0; i < MOVIESOAP_TOLERANCE_COUNT-1; i++) {
			severityRadios[i] = addRadio(hbox);	}
		vbox->addLayout(hbox);
		layout->addWidget(frame);
		// category div
		hbox = new QHBoxLayout;
		addLabel(hbox, "Category:");
		categoryBox = new QComboBox;
		for (i = 0; i < MOVIESOAP_CAT_COUNT; i ++) {
			categoryBox->addItem(QString(toleranceLabels[i]), QVariant(i)); }
		hbox->addWidget(categoryBox);
		layout->addLayout(hbox);
		// description div
		hbox = new QHBoxLayout;
		addLabel(hbox, "Description:");
		descText = addText(hbox, "e.g. skip shootout scene");
		layout->addLayout(hbox);
		// Submit div
		hbox = new QHBoxLayout;
		QPushButton * okButton = addButton(hbox, "&Ok");
		QPushButton * cancelButton = addButton(hbox, "<< (&cancel)");
		layout->addLayout(hbox);
		connect( okButton, SIGNAL(clicked()), this, SLOT(okClicked()) );
		connect( cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()) );

		hbox = new QHBoxLayout;
		QPushButton * previewButton = addButton(hbox, "&Preview edit");
		layout->addLayout(hbox);
		connect( previewButton, SIGNAL(clicked()), this, SLOT(previewClicked()) );
		// finish
		hbox = new QHBoxLayout;
		layout->addLayout(hbox, 9);
		setLayout(layout);
	}