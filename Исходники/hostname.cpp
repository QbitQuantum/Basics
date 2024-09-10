Hostname::Hostname(QWidget *parent, QString ihost, QString iport) :
    QDialog(parent), networkSession(0)
//    ui(new Ui::Hostname)
{
  //  ui->
    defaultport="23000";
    host=ihost;
    port=iport;
    setupUi(this);
    this->lineEditHostname->setText(host);
    this->lineEditHostport->setText(port);
    this->pushButtonDefaultPort->setText(tr("Default port ")+defaultport);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readPort()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));

    QObject::connect(this->pushButtonDefaultPort,SIGNAL(clicked()),this,SLOT(setDefaultPort()));
    QObject::connect(this->pushButtonGetData,SIGNAL(clicked()),this,SLOT(requestNewData()));

}