//! [0]
FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    fromStartCheckBox = new QCheckBox(tr("Search from &start"));
    fromStartCheckBox->setChecked(true);

//! [1]
    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true);

    moreButton = new QPushButton(tr("&More"));
    moreButton->setCheckable(true);
//! [0]
    moreButton->setAutoDefault(false);

//! [1]

//! [2]
    extension = new QWidget;

    wholeWordsCheckBox = new QCheckBox(tr("&Whole words"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));
    searchSelectionCheckBox = new QCheckBox(tr("Search se&lection"));
//! [2]

//! [3]
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    // Create menu
    QMenu *menu = new QMenu(this);

    // Create Find menu item
    menu->addAction(tr("Find"));

    // Create More menu item
    QAction *moreAction = menu->addAction(tr("More"));
    moreAction->setCheckable(true);

    // Create Options CBA
    QAction *optionAction = new QAction(tr("Options"), this);

    // Set defined menu into Options button
    optionAction->setMenu(menu);
    optionAction->setSoftKeyRole(QAction::PositiveSoftKey);
    addAction(optionAction);

    // Connect More menu item to setVisible slot
    connect(moreAction, SIGNAL(triggered(bool)), extension, SLOT(setVisible(bool)));

    // Create Exit CBA
    QAction *backSoftKeyAction = new QAction(QString(tr("Exit")), this);
    backSoftKeyAction->setSoftKeyRole(QAction::NegativeSoftKey);

    // Exit button closes the application
    connect(backSoftKeyAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    addAction(backSoftKeyAction);
#else
//! [6]
    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(findButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(moreButton, QDialogButtonBox::ActionRole);
//! [6]

    connect(moreButton, SIGNAL(toggled(bool)), extension, SLOT(setVisible(bool)));
#endif

    QVBoxLayout *extensionLayout = new QVBoxLayout;
    extensionLayout->setMargin(0);
    extensionLayout->addWidget(wholeWordsCheckBox);
    extensionLayout->addWidget(backwardCheckBox);
    extensionLayout->addWidget(searchSelectionCheckBox);
    extension->setLayout(extensionLayout);
//! [3]

//! [4]
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(fromStartCheckBox);

    QGridLayout *mainLayout = new QGridLayout;
#if !defined(Q_OS_SYMBIAN) && !defined(Q_WS_MAEMO_5) && !defined(Q_WS_SIMULATOR)
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
#endif
    mainLayout->addLayout(leftLayout, 0, 0);
#if !defined(Q_OS_SYMBIAN) && !defined(Q_WS_SIMULATOR)
    mainLayout->addWidget(buttonBox, 0, 1);
#endif
    mainLayout->addWidget(extension, 1, 0, 1, 2);
    mainLayout->setRowStretch(2, 1);

    setLayout(mainLayout);

    setWindowTitle(tr("Extension"));
//! [4] //! [5]
    extension->hide();
}