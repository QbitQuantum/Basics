void MathDisplay::buildActions()
{
	setContextMenuPolicy(Qt::ActionsContextMenu);

	act_copyText = new QAction(tr("Copy text"), this);
	connect(act_copyText, SIGNAL(triggered()), this, SLOT(copyText()));
	this->addAction(act_copyText);

	act_copyLatex = new QAction(tr("Copy LaTeX code"), this);
	connect(act_copyLatex, SIGNAL(triggered()), this, SLOT(copyLatex()));
	this->addAction(act_copyLatex);

	act_copyMml = new QAction(tr("Copy MathML code"), this);
	connect(act_copyMml, SIGNAL(triggered()), this, SLOT(copyMml()));
	this->addAction(act_copyMml);

	act_copyImage = new QAction(tr("Copy image"), this);
	connect(act_copyImage, SIGNAL(triggered()), this, SLOT(copyImage()));
	act_copyImage->setEnabled(false);
	this->addAction(act_copyImage);

	act_saveImage = new QAction(tr("Save image"), this);
	connect(act_saveImage, SIGNAL(triggered()), this, SLOT(saveImage()));
	act_saveImage->setEnabled(false);
	this->addAction(act_saveImage);
}