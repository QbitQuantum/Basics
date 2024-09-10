SetColValuesDialog::SetColValuesDialog( ScriptingEnv *env, QWidget* parent, Qt::WFlags fl )
    : QDialog( parent, fl ), scripted(env)
{
    setName( "SetColValuesDialog" );
	setWindowTitle( tr( "QtiPlot - Set column values" ) );
	setSizeGripEnabled(true);
    setAttribute(Qt::WA_DeleteOnClose);

	QHBoxLayout *hbox1 = new QHBoxLayout();
	hbox1->addWidget(new QLabel(tr("For row (i)")));
	start = new QSpinBox();
	start->setMinValue(1);
    start->setMaxValue(INT_MAX);
	hbox1->addWidget(start);

	hbox1->addWidget(new QLabel(tr("to")));

	end = new QSpinBox();
	end->setMinValue(1);
    end->setMaxValue(INT_MAX);
	hbox1->addWidget(end);

	QGridLayout *gl1 = new QGridLayout();
	functions = new QComboBox(false);
	gl1->addWidget(functions, 0, 0);
	btnAddFunction = new QPushButton(tr( "Add function" ));
	gl1->addWidget(btnAddFunction, 0, 1);
	boxColumn = new QComboBox(false);
	gl1->addWidget(boxColumn, 1, 0);
	btnAddCol = new QPushButton(tr( "Add column" ));
	gl1->addWidget(btnAddCol, 1, 1);

	QHBoxLayout *hbox3 = new QHBoxLayout();
	hbox3->addStretch();
	buttonPrev = new QPushButton("&<<");
	hbox3->addWidget(buttonPrev);
	buttonNext = new QPushButton("&>>");
	hbox3->addWidget(buttonNext);
	gl1->addLayout(hbox3, 2, 0);
	addCellButton = new QPushButton(tr( "Add cell" ));
	gl1->addWidget(addCellButton, 2, 1);

	QGroupBox *gb = new QGroupBox();
	QVBoxLayout *vbox1 = new QVBoxLayout();
	vbox1->addLayout(hbox1);
	vbox1->addLayout(gl1);
	gb->setLayout(vbox1);
	gb->setSizePolicy(QSizePolicy (QSizePolicy::Preferred, QSizePolicy::Preferred));

	explain = new QTextEdit();
	explain->setReadOnly (true);
	explain->setSizePolicy(QSizePolicy (QSizePolicy::Preferred, QSizePolicy::Preferred));
	QPalette palette = explain->palette();
	palette.setColor(QPalette::Active, QPalette::Base, Qt::lightGray);
	explain->setPalette(palette);

	QHBoxLayout *hbox2 = new QHBoxLayout();
	hbox2->addWidget(explain);
	hbox2->addWidget(gb);

	commands = new ScriptEdit( scriptEnv);

	QVBoxLayout *vbox2 = new QVBoxLayout();
	btnApply = new QPushButton(tr( "&Apply" ));
	vbox2->addWidget(btnApply);
	btnCancel = new QPushButton(tr( "&Close" ));
	vbox2->addWidget(btnCancel);
	vbox2->addStretch();

	QHBoxLayout *hbox4 = new QHBoxLayout();
	hbox4->addWidget(commands);
	hbox4->addLayout(vbox2);

	QVBoxLayout* vbox3 = new QVBoxLayout();
	vbox3->addLayout(hbox2);
#ifdef SCRIPTING_PYTHON
	boxMuParser = NULL;
	if (env->name() != QString("muParser")){
		boxMuParser = new QCheckBox(tr("Use built-in muParser (much faster)"));
		boxMuParser->setChecked(true);
		vbox3->addWidget(boxMuParser);
	}
#endif

	colNameLabel = new QLabel();
	vbox3->addWidget(colNameLabel);
	vbox3->addLayout(hbox4);

	setLayout(vbox3);
	setFocusProxy (commands);
	commands->setFocus();

	functions->insertStringList(scriptEnv->mathFunctions(), -1);
	if (functions->count() > 0)
		insertExplain(0);

	connect(btnAddFunction, SIGNAL(clicked()),this, SLOT(insertFunction()));
	connect(btnAddCol, SIGNAL(clicked()),this, SLOT(insertCol()));
	connect(addCellButton, SIGNAL(clicked()),this, SLOT(insertCell()));
	connect(btnApply, SIGNAL(clicked()),this, SLOT(apply()));
	connect(btnCancel, SIGNAL(clicked()),this, SLOT(close()));
	connect(functions, SIGNAL(activated(int)),this, SLOT(insertExplain(int)));
	connect(buttonPrev, SIGNAL(clicked()), this, SLOT(prevColumn()));
	connect(buttonNext, SIGNAL(clicked()), this, SLOT(nextColumn()));
}