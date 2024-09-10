DelDialog::DelDialog(QString name, QString text, QWidget* parent)
{
	setParent(parent);
	setWindowFlags(Qt::Dialog);
	setWindowTitle(name);
	setModal(1);

	layout = new QGridLayout;
	label = new QLabel (text, this);
	acceptButton = new QPushButton (tr("&yes"), this);
	rejectButton = new QPushButton (tr("&no"), this);

	rejectButton->setFocus();

	connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(rejectButton, SIGNAL(clicked()), this, SLOT(reject()));

	layout->addWidget(label, 0, 0, 1, 0);
	layout->addWidget(acceptButton, 1, 0);
	layout->addWidget(rejectButton, 1, 1);

	setLayout(layout);
}