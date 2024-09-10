// Test buffered socket being properly closed on remote disconnect
void tst_QAbstractSocket::serverDisconnectWithBuffered()
{
    QTcpServer tcpServer;
#ifndef QT_NO_SSL
    QSslSocket testSocket;
#else
    QTcpSocket testSocket;
#endif

    QVERIFY(tcpServer.listen(QHostAddress::LocalHost));
    testSocket.connectToHost(tcpServer.serverAddress(), tcpServer.serverPort());
    // Accept connection on server side
    QVERIFY(tcpServer.waitForNewConnection(5000));
    QTcpSocket *newConnection = tcpServer.nextPendingConnection();
    // Send one char and drop link
    QVERIFY(newConnection != NULL);
    QVERIFY(newConnection->putChar(0));
    QVERIFY(newConnection->flush());
    delete newConnection;

    QVERIFY(testSocket.waitForConnected(5000)); // ready for write
    QVERIFY(testSocket.state() == QAbstractSocket::ConnectedState);

    QSignalSpy spyStateChanged(&testSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)));
    QSignalSpy spyDisconnected(&testSocket, SIGNAL(disconnected()));

    QVERIFY(testSocket.waitForReadyRead(5000)); // have one char already in internal buffer
    char buf[128];
    QCOMPARE(testSocket.read(buf, sizeof(buf)), Q_INT64_C(1));
    if (testSocket.state() != QAbstractSocket::UnconnectedState) {
        QVERIFY(testSocket.waitForDisconnected(5000));
        QVERIFY(testSocket.state() == QAbstractSocket::UnconnectedState);
    }
    // Test signal emitting
    QVERIFY(spyDisconnected.count() == 1);
    QVERIFY(spyStateChanged.count() > 0);
    QVERIFY(qvariant_cast<QAbstractSocket::SocketState>(spyStateChanged.last().first())
            == QAbstractSocket::UnconnectedState);
}