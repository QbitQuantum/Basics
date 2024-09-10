ContextTile::ContextTile(QString cmdTxt, QString descTxt, QWidget *parent) : QWidget(parent) {

	this->setMouseTracking(true);

	// The standard default stylesheet
	css = "font-weight: bold; color: black; border-radius: 5px; padding: 1px; font-size: 8pt;";

	// Some special stylesheet for hovered and normal
	cssBackgroundNorm = "background: rgba(255,255,255,100);";
	cssBackgroundHov = "background: rgba(255,255,255,200);";

	this->setStyleSheet(css + cssBackgroundNorm);

	// Main Layout
	QHBoxLayout *lay = new QHBoxLayout;

	lay->setSpacing(0);

	// Default index (i.e. invalid/unset)
	index = -1;

	// A label for dragging
	dragLabel = new CustomLabel(tr("Click here to drag"));
	dragLabel->setToolTip(tr("Click here to drag"));
	dragLabel->setCursor(Qt::SizeAllCursor);
	dragLabel->setFontColor("#333333");
	lay->addWidget(dragLabel);

	// A seperator
	QLabel *sep1 = new QLabel("|");
	sep1->setStyleSheet("background: transparent;");
	lay->addWidget(sep1);

	// The command (editable)
	cmd = new QLineEdit(cmdTxt);
	cmd->setStyleSheet("background: transparent; border-bottom: 1px solid rgb(50,50,50,100); border-radius: none;");
	cmd->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
	lay->addWidget(cmd);

	// A seperator
	QLabel *sep2 = new QLabel("|");
	sep2->setStyleSheet("background: transparent;");
	lay->addWidget(sep2);

	// The menu text (editable)
	desc = new QLineEdit(descTxt);
	desc->setStyleSheet("background: transparent; border-bottom: 1px solid rgb(50,50,50,100); border-radius: none;");
	desc->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
	lay->addWidget(desc);

	// A seperator
	QLabel *sep3 = new QLabel("|");
	sep3->setStyleSheet("background: transparent;");
	lay->addWidget(sep3);

	// Delete entry
	QPushButton *x = new QPushButton("x ");
	x->setFlat(true);
	x->setToolTip(tr("Delete Entry"));
	x->setCursor(Qt::PointingHandCursor);
	x->setStyleSheet("QPushButton { background: transparent; } QToolTip {font-weight: bold; color: black; border-radius: 5px; padding: 1px; font-size: 8pt; background: rgba(255,255,255,200); }");
	lay->addWidget(x);
	connect(x, SIGNAL(clicked()), this, SLOT(pleaseDeleteMe()));

	lay->setMargin(3);
	this->setLayout(lay);



}