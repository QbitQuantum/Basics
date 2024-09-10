// ------------------------------------------------------------------------
void DicomParser::setUpDisplay()
{

	parseDicom();
	loadImages();


	QWidget * w1 = new QWidget(this);
	QHBoxLayout * l1 = new QHBoxLayout;
	l1->addWidget(createTable());
	l1->addWidget(createViewer());
	w1->setLayout(l1);
	

	
	okButton = new QPushButton("OK", this);
	connect(okButton, SIGNAL(clicked()), this, SLOT(okPressed()));
	
	cancelButton = new QPushButton("Cancel", this);
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelPressed()));

	QHBoxLayout * l2 = new QHBoxLayout;
	l2->addWidget(cancelButton);
	l2->addWidget(okButton);

	QWidget * w2 = new QWidget(this);
	w2->setLayout(l2);

	QVBoxLayout * l3 = new QVBoxLayout;
	l3->addWidget(w1);
	l3->addWidget(w2);

	this->setLayout(l3);

}