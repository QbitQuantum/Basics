//
// Replace home window when no ride
//
BlankStatePage::BlankStatePage(Context *context) : context(context), canShow_(true)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    QHBoxLayout *homeLayout = new QHBoxLayout;
    mainLayout->addLayout(homeLayout);
    homeLayout->setAlignment(Qt::AlignCenter);
    homeLayout->addSpacing(20); // left margin
    setAutoFillBackground(true);
    setProperty("color", QColor(Qt::white));
    setProperty("nomenu", true);

    // left part
    QWidget *left = new QWidget(this);
    leftLayout = new QVBoxLayout(left);
    leftLayout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    left->setLayout(leftLayout);

    welcomeTitle = new QLabel(left);
    welcomeTitle->setFont(QFont("Helvetica", 30, QFont::Bold, false));
    leftLayout->addWidget(welcomeTitle);

    welcomeText = new QLabel(left);
    welcomeText->setFont(QFont("Helvetica", 16, QFont::Light, false));
    leftLayout->addWidget(welcomeText);

    leftLayout->addSpacing(10);

    homeLayout->addWidget(left);
    homeLayout->addSpacing(50);

    QWidget *right = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(right);
    rightLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
    right->setLayout(rightLayout);

    img = new QToolButton(this);
    img->setFocusPolicy(Qt::NoFocus);
    img->setToolButtonStyle(Qt::ToolButtonIconOnly);
    img->setStyleSheet("QToolButton {text-align: left;color : blue;background: transparent}");
    rightLayout->addWidget(img);

    homeLayout->addWidget(right);
    // right margin
    homeLayout->addSpacing(20);

    // control if shown or not in future
    QHBoxLayout *bottomRow = new QHBoxLayout;
    mainLayout->addSpacing(20);
    mainLayout->addLayout(bottomRow);

    dontShow = new QCheckBox(tr("Don't show this next time."), this);
    dontShow->setFocusPolicy(Qt::NoFocus);
    closeButton = new QPushButton(tr("Close"), this);
    closeButton->setFocusPolicy(Qt::NoFocus);
    bottomRow->addWidget(dontShow);
    bottomRow->addStretch();
    bottomRow->addWidget(closeButton);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(setCanShow()));
    connect(closeButton, SIGNAL(clicked()), this, SIGNAL(closeClicked()));
}