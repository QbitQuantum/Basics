ColourChooser::ColourChooser(QString title, QWidget *parent) :
    QWidget(parent)
{
    isConstant = false;

    mainMinBtn = new QPushButton(tr("From"));
    mainMin = new QColor(0,64,0);
    mainMinBtn->setIcon(createIcon(mainMin));
    mainMinBtn->setObjectName(QString("mainMinBtn"));

    mainMaxBtn = new QPushButton(tr("To"));
    mainMax = new QColor(0,128,0);
    mainMaxBtn->setIcon(createIcon(mainMax));
    mainMaxBtn->setObjectName(QString("mainMaxBtn"));

    altMinBtn = new QPushButton(tr("From"));
    altMin = new QColor(32,64,32);
    altMinBtn->setIcon(createIcon(altMin));
    altMinBtn->setObjectName(QString("altMinBtn"));

    altMaxBtn = new QPushButton(tr("To"));
    altMax = new QColor(32,128,32);
    altMaxBtn->setIcon(createIcon(altMax));
    altMaxBtn->setObjectName(QString("altMaxBtn"));

    intensity = new VariationChooser(QString("Colouring Spread Distance"), 2,1,0);
    intensity->setMinimumHeight(50);

    connect(mainMinBtn,SIGNAL(clicked()),this,SLOT(btnClicked()));
    connect(mainMaxBtn,SIGNAL(clicked()),this,SLOT(btnClicked()));
    connect(altMinBtn,SIGNAL(clicked()),this,SLOT(btnClicked()));
    connect(altMaxBtn,SIGNAL(clicked()),this,SLOT(btnClicked()));

    sideImage = new QLabel();
    sideImage->setPixmap(createVPixmap());
    mainImage = new QLabel();
    mainImage->setPixmap(createHPixmap(mainMin,mainMax));
    altImage = new QLabel();
    altImage->setPixmap(createHPixmap(altMin,altMax));

    QGroupBox *box = new QGroupBox(title);
    QVBoxLayout *leftLayout = new QVBoxLayout();

    //Main Colour Box
    QGroupBox *topBox = new QGroupBox(tr("Main Colour:"));
    QVBoxLayout *topBoxLayout = new QVBoxLayout();
    topBoxLayout->addWidget(new QLabel(tr("Variation")),0,Qt::AlignCenter);

    QHBoxLayout *topBoxHLayout = new QHBoxLayout();
    topBoxHLayout->addWidget(mainMinBtn);
    topBoxHLayout->addStretch();
    topBoxHLayout->addWidget(mainMaxBtn);
    topBoxLayout->addLayout(topBoxHLayout);

    topBoxLayout->addWidget(new QLabel(tr("Range")),0,Qt::AlignCenter);
    topBoxLayout->addWidget(mainImage,0,Qt::AlignCenter);

    topBox->setLayout(topBoxLayout);

    //Alt Colour Box
    bottomBox = new QGroupBox(tr("Alternate Colour:"));
    QVBoxLayout *bottomBoxLayout = new QVBoxLayout();
    bottomBoxLayout->addWidget(new QLabel(tr("Variation")),0,Qt::AlignCenter);

    QHBoxLayout *bottomBoxHLayout = new QHBoxLayout();
    bottomBoxHLayout->addWidget(altMinBtn);
    bottomBoxHLayout->addStretch();
    bottomBoxHLayout->addWidget(altMaxBtn);
    bottomBoxLayout->addLayout(bottomBoxHLayout);

    bottomBoxLayout->addWidget(new QLabel(tr("Range")),0,Qt::AlignCenter);
    bottomBoxLayout->addWidget(altImage,0,Qt::AlignCenter);
    bottomBoxLayout->addWidget(intensity,0,Qt::AlignCenter);
    bottomBoxLayout->addStretch();

    bottomBox->setLayout(bottomBoxLayout);

    //Now add to left layout
    leftLayout->addWidget(topBox);
    leftLayout->addWidget(bottomBox);


    QHBoxLayout *boxLayout = new QHBoxLayout();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    boxLayout->addLayout(leftLayout);
    boxLayout->addWidget(sideImage,0,Qt::AlignBottom);
    box->setLayout(boxLayout);
    mainLayout->addWidget(box);

    this->setLayout(mainLayout);
}