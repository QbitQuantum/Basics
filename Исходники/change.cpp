Change::Change(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Change)
{
    pathToRes = new QString("/home/midv/Projects/TrajectoryBuilder/Trajectory/resourses/");
    ui->setupUi(this);
    QHBoxLayout *generalLay = new QHBoxLayout(this);
    generalLay->setContentsMargins(0,0,0,0);
    QLabel *label = new QLabel();
    label->setFixedSize(this->size());
    label->setContentsMargins(0,0,0,0);
    label->setStyleSheet("QLabel{border:4px solid #00aa00; border-radius:10px}");
    generalLay->addWidget(label);
    QHBoxLayout *lay = new QHBoxLayout();
    label->setLayout(lay);
    lay->setAlignment(Qt::AlignCenter);
    lay->setSpacing(0);
    lay->setContentsMargins(5,0,0,0);
    QtSvgButton *button1 = new QtSvgButton();
    button1->setLockalSkin(*pathToRes,"Line");
    connect(button1,SIGNAL(clicked()),SLOT(pressButton1()));
    button1->setFixedSize(110,110);
    lay->addWidget(button1);
    QtSvgButton *button2 = new QtSvgButton();
    button2->setLockalSkin(*pathToRes,"Aссel");
    connect(button2,SIGNAL(clicked()),SLOT(pressButton2()));
    button2->setFixedSize(110,110);
    lay->addWidget(button2);
    QtSvgButton *button3 = new QtSvgButton();
    button3->setLockalSkin(*pathToRes,"ArcV");
    connect(button3,SIGNAL(clicked()),SLOT(pressButton3()));
    button3->setFixedSize(110,110);
    lay->addWidget(button3);
    QtSvgButton *button4 = new QtSvgButton();
    button4->setLockalSkin(*pathToRes,"ArcH");
    connect(button4,SIGNAL(clicked()),SLOT(pressButton4()));
    button4->setFixedSize(110,110);
    lay->addWidget(button4);
    QtSvgButton *button5 = new QtSvgButton();
    button5->setLockalSkin(*pathToRes,"ZmeyV");
    connect(button5,SIGNAL(clicked()),SLOT(pressButton5()));
    button5->setFixedSize(110,110);
    lay->addWidget(button5);
    QtSvgButton *button6 = new QtSvgButton();
    button6->setLockalSkin(*pathToRes,"ZmeyH");
    connect(button6,SIGNAL(clicked()),SLOT(pressButton6()));
    button6->setFixedSize(110,110);
    lay->addWidget(button6);
    QtSvgButton *button7 = new QtSvgButton();
    button7->setLockalSkin(*pathToRes,"Remove");
    connect(button7,SIGNAL(clicked()),SLOT(pressButton7()));
    button7->setFixedSize(110,110);
    lay->addWidget(button7);
}