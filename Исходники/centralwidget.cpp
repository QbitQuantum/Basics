CentralWidget::CentralWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout5 = new QHBoxLayout;
    setLayout(layout5);
    ManScreen *screen = new ManScreen;
    layout5->addWidget(screen);
    QVBoxLayout *layout6 = new QVBoxLayout;
    layout5->addLayout(layout6);
    //
    QGroupBox *headBox = new QGroupBox(tr("head"));
    layout6->addWidget(headBox);
    QVBoxLayout *layout7 = new QVBoxLayout;
    headBox->setLayout(layout7);
    QLineEdit *headText = new QLineEdit();
    headText->setPlaceholderText(tr("Enter formula..."));
    layout7->addWidget(headText);
    FormulaValidator *headValidator = new FormulaValidator();
    connect(headText, SIGNAL(textChanged(QString)), headValidator, SLOT(reciveText(QString)));
    connect(headValidator, SIGNAL(newValidFormula(QString)), screen, SLOT(setHeadFormula(QString)));
    //
    QGroupBox *bodyBox = new QGroupBox(tr("body"));
    layout6->addWidget(bodyBox);
    QVBoxLayout *layout8 = new QVBoxLayout;
    bodyBox->setLayout(layout8);
    QLineEdit *bodyText = new QLineEdit();
    bodyText->setPlaceholderText(tr("Enter formula..."));
    layout8->addWidget(bodyText);
    FormulaValidator *bodyValidator = new FormulaValidator();
    connect(bodyText, SIGNAL(textChanged(QString)), bodyValidator, SLOT(reciveText(QString)));
    connect(bodyValidator, SIGNAL(newValidFormula(QString)), screen, SLOT(setBodyFormula(QString)));
    //
    QGroupBox *leftHandBox = new QGroupBox(tr("left hand"));
    layout6->addWidget(leftHandBox);
    QVBoxLayout *layout9 = new QVBoxLayout;
    leftHandBox->setLayout(layout9);
    QLineEdit *leftHandText = new QLineEdit();
    leftHandText->setPlaceholderText(tr("Enter formula..."));
    layout9->addWidget(leftHandText);
    FormulaValidator *leftHandValidator = new FormulaValidator();
    connect(leftHandText, SIGNAL(textChanged(QString)), leftHandValidator, SLOT(reciveText(QString)));
    connect(leftHandValidator, SIGNAL(newValidFormula(QString)), screen, SLOT(setLeftHandFormula(QString)));
    //
    QGroupBox *rightHandBox = new QGroupBox(tr("right hand"));
    layout6->addWidget(rightHandBox);
    QVBoxLayout *layout10 = new QVBoxLayout;
    rightHandBox->setLayout(layout10);
    QLineEdit *rightHandText = new QLineEdit();
    rightHandText->setPlaceholderText(tr("Enter formula..."));
    layout10->addWidget(rightHandText);
    FormulaValidator *rightHandValidator = new FormulaValidator();
    connect(rightHandText, SIGNAL(textChanged(QString)), rightHandValidator, SLOT(reciveText(QString)));
    connect(rightHandValidator, SIGNAL(newValidFormula(QString)), screen, SLOT(setRightHandFormula(QString)));
    //
    QGroupBox *leftLegBox = new QGroupBox(tr("left leg"));
    layout6->addWidget(leftLegBox);
    QVBoxLayout *layout11 = new QVBoxLayout;
    leftLegBox->setLayout(layout11);
    QLineEdit *leftLegText = new QLineEdit();
    leftLegText->setPlaceholderText(tr("Enter formula..."));
    layout11->addWidget(leftLegText);
    FormulaValidator *leftLegValidator = new FormulaValidator();
    connect(leftLegText, SIGNAL(textChanged(QString)), leftLegValidator, SLOT(reciveText(QString)));
    connect(leftLegValidator, SIGNAL(newValidFormula(QString)), screen, SLOT(setLeftLegFormula(QString)));
    //
    QGroupBox *rightLegBox = new QGroupBox(tr("right leg"));
    layout6->addWidget(rightLegBox);
    QVBoxLayout *layout12 = new QVBoxLayout;
    rightLegBox->setLayout(layout12);
    QLineEdit *rightLegText = new QLineEdit();
    rightLegText->setPlaceholderText(tr("Enter formula..."));
    layout12->addWidget(rightLegText);
    FormulaValidator *rightLegValidator = new FormulaValidator();
    connect(rightLegText, SIGNAL(textChanged(QString)), rightLegValidator, SLOT(reciveText(QString)));
    connect(rightLegValidator, SIGNAL(newValidFormula(QString)), screen, SLOT(setRightLegFormula(QString)));
}