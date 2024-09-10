void tst_QSocketNotifier::bogusFds()
{
#ifndef Q_OS_SYMBIAN
    //behaviour of QSocketNotifier with an invalid fd is totally different across OS
    //main point of this test was to check symbian backend doesn't crash
    QSKIP("test only for symbian", SkipAll);
#else
    QTest::ignoreMessage(QtWarningMsg, "QSocketNotifier: Internal error");
    QSocketNotifier max(std::numeric_limits<int>::max(), QSocketNotifier::Read);
    QTest::ignoreMessage(QtWarningMsg, "QSocketNotifier: Invalid socket specified");
    QTest::ignoreMessage(QtWarningMsg, "QSocketNotifier: Internal error");
    QSocketNotifier min(std::numeric_limits<int>::min(), QSocketNotifier::Write);
    QTest::ignoreMessage(QtWarningMsg, "QSocketNotifier: Internal error");
    //bogus magic number is the first pseudo socket descriptor from symbian socket engine.
    QSocketNotifier bogus(0x40000000, QSocketNotifier::Exception);
    QSocketNotifier largestlegal(FD_SETSIZE - 1, QSocketNotifier::Read);

    QSignalSpy maxspy(&max, SIGNAL(activated(int)));
    QSignalSpy minspy(&min, SIGNAL(activated(int)));
    QSignalSpy bogspy(&bogus, SIGNAL(activated(int)));
    QSignalSpy llspy(&largestlegal, SIGNAL(activated(int)));

    //generate some unrelated socket activity
    QTcpServer server;
    QVERIFY(server.listen(QHostAddress::LocalHost));
    connect(&server, SIGNAL(newConnection()), &QTestEventLoop::instance(), SLOT(exitLoop()));
    QTcpSocket client;
    client.connectToHost(QHostAddress::LocalHost, server.serverPort());
    QTestEventLoop::instance().enterLoop(5);
    QVERIFY(server.hasPendingConnections());

    //check no activity on bogus notifiers
    QCOMPARE(maxspy.count(), 0);
    QCOMPARE(minspy.count(), 0);
    QCOMPARE(bogspy.count(), 0);
    QCOMPARE(llspy.count(), 0);
#endif
}