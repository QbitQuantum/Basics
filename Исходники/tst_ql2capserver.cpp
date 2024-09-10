void tst_QL2capServer::tst_listen()
{
    QFETCH(QBluetoothAddress, address);
    QFETCH(quint16, port);

    {
        QL2capServer server;

        bool result = server.listen(address, port);

        QVERIFY(result);
        QVERIFY(server.isListening());

        if (!address.isNull())
            QCOMPARE(server.serverAddress(), address);
        else
            QVERIFY(!server.serverAddress().isNull());

        if (port != 0)
            QCOMPARE(server.serverPort(), port);
        else
            QVERIFY(server.serverPort() != 0);

        QCOMPARE(server.maxPendingConnections(), 1);

        QVERIFY(!server.hasPendingConnections());
        QVERIFY(server.nextPendingConnection() == 0);

        server.close();

        QVERIFY(!server.isListening());

        QVERIFY(server.serverAddress().isNull());
        QVERIFY(server.serverPort() == 0);

        QVERIFY(!server.hasPendingConnections());
        QVERIFY(server.nextPendingConnection() == 0);
    }
}