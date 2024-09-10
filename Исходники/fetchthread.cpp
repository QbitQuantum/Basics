void FetchThread::process(QString phost)
{

    QUdpSocket *udpSocket ;
    udpSocket= new QUdpSocket(0);
    udpSocket->bind(QHostAddress::LocalHost, 9999);
    udpSocket->waitForConnected(250);



    QTcpSocket socket;
    socket.connectToHost("localhost", 4949);
    socket.waitForConnected(500);

    while (socket.waitForReadyRead(250));
    QString t_hello = socket.readAll();
    qDebug() << "READ: " << t_hello;

    socket.write(QString("list\n").toStdString().c_str() );
    while (socket.waitForReadyRead(250));
    QString buf1 = socket.readAll();

    qDebug() << "READ: " << buf1;
    QStringList list_probe = buf1.split(QRegExp("\\s+"));

    for (int z=0; z< list_probe.size(); z++)
    {
        QString probe=list_probe.at(z);
        QString cmd = QString("fetch ").append(probe).append("\n");
        qDebug() << "cmd : " << cmd;
        socket.write(cmd.toStdString().c_str() );


        while (socket.waitForReadyRead(250));
        QString buf2 = socket.readAll();
        qDebug() << "Rep fetch :" << buf2 << "\n";

        QRegularExpression re("(\\w+).(\\w+) ([0-9.]+)\\n");
        QRegularExpressionMatchIterator i = re.globalMatch(buf2);
        re.setPatternOptions(QRegularExpression::MultilineOption);

        while (i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            QString s_metric = match.captured(1);
            QString s_value = match.captured(3);
            QString s_mtr = "monit2influxdb,metric="+probe + "_" + s_metric + ",host=" + phost+ " value=" + s_value + " " + QString::number(1000000* QDateTime::currentMSecsSinceEpoch());
            qDebug() << "metric:  " << s_mtr.toLower();

            udpSocket->writeDatagram(s_mtr.toStdString().c_str(), QHostAddress::LocalHost, 9999);




        }

        udpSocket->close();


    }
}