void LocalQmlProfilerRunnerTest::testFindFreePort()
{
    QString host;
    Utils::Port port = LocalQmlProfilerRunner::findFreePort(host);
    QVERIFY(port.isValid());
    QVERIFY(!host.isEmpty());
    QTcpServer server;
    QVERIFY(server.listen(QHostAddress(host), port.number()));
}