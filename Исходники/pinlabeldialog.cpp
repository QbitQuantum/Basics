QFrame * PinLabelDialog::initLabels(const QStringList & labels, bool singleRow, const QString & chipLabel)
{
	QFrame * frame = new QFrame();
	QVBoxLayout * vLayout = new QVBoxLayout();

	QLabel * label = new QLabel("<h2>" + chipLabel + "</h2>");
	label->setAlignment(Qt::AlignCenter);

	QFrame * subFrame = new QFrame();
	if (singleRow) {
		QGridLayout * gridLayout = new QGridLayout();
		gridLayout->setMargin(0);
		gridLayout->setSpacing(3);

		for (int i = 0; i < labels.count(); i++) {
			makeOnePinEntry(i, labels.at(i), Qt::AlignLeft, i, gridLayout);
		}

		subFrame->setLayout(gridLayout);
	}
	else {
		QHBoxLayout * hLayout = new QHBoxLayout();

		QFrame * lFrame = new QFrame();
		QGridLayout * lLayout = new QGridLayout;
		lLayout->setMargin(0);
		lLayout->setSpacing(3);
		for (int i = 0; i < labels.count() / 2; i++) {
			makeOnePinEntry(i, labels.at(i), Qt::AlignLeft, i, lLayout);
		}
		lFrame->setLayout(lLayout);

		QFrame * rFrame = new QFrame();
		QGridLayout * rLayout = new QGridLayout;
		rLayout->setMargin(0);
		rLayout->setSpacing(3);
		int row = labels.count() - 1;
		for (int i = labels.count() / 2; i < labels.count(); i++) {
			makeOnePinEntry(i, labels.at(i), Qt::AlignRight, row--, rLayout);
		}
		rFrame->setLayout(rLayout);

		hLayout->addWidget(lFrame);
		hLayout->addSpacing(15);
		hLayout->addWidget(rFrame);

		subFrame->setLayout(hLayout);
	}

	vLayout->addWidget(label);
	vLayout->addWidget(subFrame);
	frame->setLayout(vLayout);

	return frame;
}