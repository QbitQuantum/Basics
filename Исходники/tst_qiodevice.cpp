//--------------------------------------------------------------------
void tst_QIODevice::unget()
{
#if defined(Q_OS_WINCE) && defined(WINCE_EMULATOR_TEST)
    QSKIP("Networking tests in a WinCE emulator are unstable", SkipAll);
#endif
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    buffer.write("ZXCV");
    buffer.seek(0);
    QCOMPARE(buffer.read(4), QByteArray("ZXCV"));
    QCOMPARE(buffer.pos(), qint64(4));

    buffer.ungetChar('a');
    buffer.ungetChar('b');
    buffer.ungetChar('c');
    buffer.ungetChar('d');

    QCOMPARE(buffer.pos(), qint64(0));

    char buf[6];
    QCOMPARE(buffer.readLine(buf, 5), qint64(4));
    QCOMPARE(buffer.pos(), qint64(4));
    QCOMPARE(static_cast<const char*>(buf), "dcba");

    buffer.ungetChar('a');
    buffer.ungetChar('b');
    buffer.ungetChar('c');
    buffer.ungetChar('d');

    QCOMPARE(buffer.pos(), qint64(0));

    for (int i = 0; i < 5; ++i) {
        buf[0] = '@';
        buf[1] = '@';
        QTest::ignoreMessage(QtWarningMsg,
                             "QIODevice::readLine: Called with maxSize < 2");
        QCOMPARE(buffer.readLine(buf, 1), qint64(-1));
        QCOMPARE(buffer.readLine(buf, 2), qint64(i < 4 ? 1 : -1));
        switch (i) {
        case 0:
            QCOMPARE(buf[0], 'd');
            break;
        case 1:
            QCOMPARE(buf[0], 'c');
            break;
        case 2:
            QCOMPARE(buf[0], 'b');
            break;
        case 3:
            QCOMPARE(buf[0], 'a');
            break;
        case 4:
            QCOMPARE(buf[0], '\0');
            break;
        }
        QCOMPARE(buf[1], i < 4 ? '\0' : '@');
    }

    buffer.ungetChar('\n');
    QCOMPARE(buffer.readLine(), QByteArray("\n"));

    buffer.seek(1);
    buffer.readLine(buf, 3);
    QCOMPARE(static_cast<const char*>(buf), "XC");

    buffer.seek(4);
    buffer.ungetChar('Q');
    QCOMPARE(buffer.readLine(buf, 3), qint64(1));

    for (int i = 0; i < 2; ++i) {
        QTcpSocket socket;
        QIODevice *dev;
        QByteArray result;
        const char *lineResult;
        if (i == 0) {
            dev = &buffer;
            result = QByteArray("ZXCV");
            lineResult = "ZXCV";
        } else {
            socket.connectToHost(QtNetworkSettings::serverName(), 80);
            socket.write("GET / HTTP/1.0\r\n\r\n");
            QVERIFY(socket.waitForReadyRead());
            dev = &socket;
            result = QByteArray("HTTP");
            lineResult = "Date";
        }
        char ch, ch2;
        dev->seek(0);
        dev->getChar(&ch);
        dev->ungetChar(ch);
        QCOMPARE(dev->peek(4), result);
        dev->getChar(&ch);
        dev->getChar(&ch2);
        dev->ungetChar(ch2);
        dev->ungetChar(ch);
        QCOMPARE(dev->read(1), result.left(1));
        QCOMPARE(dev->read(3), result.right(3));

        if (i == 0)
            dev->seek(0);
        else
            dev->readLine();
        dev->getChar(&ch);
        dev->ungetChar(ch);
        dev->readLine(buf, 5);
        QCOMPARE(static_cast<const char*>(buf), lineResult);

        if (i == 1)
            socket.close();
    }
}