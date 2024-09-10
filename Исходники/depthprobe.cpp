depthProbe::depthProbe(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::depthProbe)
{
    ui->setupUi(this);
#ifdef DISCONNECTED
    zeroed = true;
#else
    zeroed=false;
#endif
    connect(ui->btnOpenFile,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(ui->btnOpenPort,SIGNAL(clicked()),this,SLOT(openPort()));
    connect(ui->btnBegin,SIGNAL(clicked()),this,SLOT(Run()));
    connect(ui->btnZero,SIGNAL(clicked()),this,SLOT(Zero()));
#ifdef DEBUG
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(button()));
    ui->pushButton->setVisible(true);
#else
    ui->pushButton->setVisible(false);
#endif
    portOpen = false;
#ifdef Q_WS_X11
    ui->cmbPort->addItem("USB0");
    ui->cmbPort->addItem("USB1");
    ui->cmbPort->addItem("USB2");
    ui->cmbPort->addItem("USB3");
    ui->cmbPort->addItem("USB4");
    ui->cmbPort->addItem("USB5");
    ui->cmbPort->addItem("ACM0");
    ui->cmbPort->addItem("ACM1");
    ui->cmbPort->addItem("ACM2");
    ui->cmbPort->addItem("ACM3");
    ui->cmbPort->addItem("ACM4");
    ui->cmbPort->addItem("ACM5");
#ifdef DEBUG
    ui->cmbPort->setCurrentIndex(6);
#endif
#else
    ui->cmbPort->addItem("COM1");
    ui->cmbPort->addItem("COM2");
    ui->cmbPort->addItem("COM3");
    ui->cmbPort->addItem("COM4");
    ui->cmbPort->addItem("COM5");
    ui->cmbPort->addItem("COM6");
    ui->cmbPort->addItem("COM7");
    ui->cmbPort->addItem("COM8");
    ui->cmbPort->addItem("COM9");
    ui->cmbPort->addItem("COM10");
    ui->cmbPort->addItem("COM11");
    ui->cmbPort->addItem("COM12");
    ui->cmbPort->addItem("COM13");
    ui->cmbPort->addItem("COM14");
    ui->cmbPort->addItem("COM15");
    ui->cmbPort->addItem("COM16");
#ifdef DEBUG
    ui->cmbPort->setCurrentIndex(11);
#endif
#endif
    styleSheet = ui->btnOpenPort->styleSheet();
}