/*!
 Description: Unit test for NFC LLCP server sync(waitXXX) functions

 TestScenario: 1. Server will listen to a pre-defined URI
               2. Wait client to connect.
               3. Read message from client.
               4. Echo the same message back to client
               5. Wait client disconnect event.

 TestExpectedResults:
               1. The listen successfully set up.
               2. The message has be received from client.
               3. The echoed message has been sent to client.
               4. Connection disconnected and NO error signals emitted.
*/
void tst_QLlcpServer::newConnection_wait()
{
    QFETCH(QString, uri);
    QFETCH(QString, hint);

    QLlcpServer server;
    qDebug() << "Create QLlcpServer completed";
    qDebug() << "Start listening...";
    bool ret = server.listen(uri);
    QVERIFY(ret);
    qDebug() << "Listen() return ok";
    QSignalSpy connectionSpy(&server, SIGNAL(newConnection()));

    QNfcTestUtil::ShowAutoMsg(hint, &connectionSpy, 1);

    QTRY_VERIFY(!connectionSpy.isEmpty());
    qDebug() << "try to call nextPendingConnection()";
    QLlcpSocket *socket = server.nextPendingConnection();
    QVERIFY(socket != NULL);

    QSignalSpy errorSpy(socket, SIGNAL(error(QLlcpSocket::SocketError)));
    //Get data from client
    const int Timeout = 10 * 1000;

    quint16 blockSize = 0;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_6);
    while (socket->bytesAvailable() < (int)sizeof(quint16)) {
        bool ret = socket->waitForReadyRead(Timeout);
        QVERIFY(ret);
    }

    in >> blockSize;
    qDebug()<<"Read blockSize from client: " << blockSize;
    while (socket ->bytesAvailable() < blockSize) {
        bool ret = socket->waitForReadyRead(Timeout);
        QVERIFY(ret);
    }
    QString echo;
    in >> echo;
    qDebug() << "Read data from client:" << echo;
    //Send data to client
    QSignalSpy bytesWrittenSpy(socket, SIGNAL(bytesWritten(qint64)));

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out << (quint16)0;
    out << echo;
    qDebug()<<"Write echoed data back to client";
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    qint64 val = socket->write(block);
    qDebug("Write() return value = %d", val);
    QVERIFY(val == 0);

    ret = socket->waitForBytesWritten(Timeout);
    QVERIFY(ret);

    QTRY_VERIFY(!bytesWrittenSpy.isEmpty());
    qint64 written = countBytesWritten(bytesWrittenSpy);

    while (written < block.size())
    {
        QSignalSpy bytesWrittenSpy(socket, SIGNAL(bytesWritten(qint64)));
        bool ret = socket->waitForBytesWritten(Timeout);
        QVERIFY(ret);
        QTRY_VERIFY(!bytesWrittenSpy.isEmpty());
        written += countBytesWritten(bytesWrittenSpy);
    }
    QVERIFY(written == block.size());
    //Now data has been sent,check the if existing error
    if (!errorSpy.isEmpty())
    {
        QLlcpSocket::SocketError error = errorSpy.first().at(0).value<QLlcpSocket::SocketError>();
        qDebug("QLlcpSocket::SocketError =%d", error);
    }
    QVERIFY(errorSpy.isEmpty());
    QTest::qWait(1500);//give some time to client to finish
    server.close();
}