qChat::qChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qChat)
{
    ui->setupUi(this);

    /* server parameters */
    _host = "achat.lorenzobianconi.net";
    _port = 9999;
    _nick = getHostname() + QString("@") + QHostInfo::localHostName();
    _sock = new QTcpSocket(this);
    _connecTimer = new QTimer(this);

    _ws = CLIENT_NOT_AUTHENTICATED;

    _attempt = 1;

    tableFormat.setBorder(0);

    connect(ui->msgEdit, SIGNAL(returnPressed()), this, SLOT(sndMsg()));
    connect(_sock, SIGNAL(connected()), this, SLOT(clientAuth()));
    connect(_sock, SIGNAL(readyRead()), this, SLOT(getMsg()));
    connect(_sock, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(_connecTimer, SIGNAL(timeout()), this, SLOT(try_connect()));

    _sock->connectToHost(_host, _port);
    _connecTimer->setSingleShot(true);
}