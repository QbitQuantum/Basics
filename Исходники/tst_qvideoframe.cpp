void tst_QVideoFrame::assign()
{
    QFETCH(QAbstractVideoBuffer::HandleType, handleType);
    QFETCH(QSize, size);
    QFETCH(QVideoFrame::PixelFormat, pixelFormat);
    QFETCH(QVideoFrame::FieldType, fieldType);
    QFETCH(qint64, startTime);
    QFETCH(qint64, endTime);

    QPointer<QtTestVideoBuffer> buffer = new QtTestVideoBuffer(handleType);

    QVideoFrame frame;
    {
        QVideoFrame otherFrame(buffer, size, pixelFormat);
        otherFrame.setFieldType(fieldType);
        otherFrame.setStartTime(startTime);
        otherFrame.setEndTime(endTime);

        frame = otherFrame;

        QVERIFY(!buffer.isNull());

        QVERIFY(otherFrame.isValid());
        QCOMPARE(otherFrame.handleType(), handleType);
        QCOMPARE(otherFrame.pixelFormat(), pixelFormat);
        QCOMPARE(otherFrame.size(), size);
        QCOMPARE(otherFrame.width(), size.width());
        QCOMPARE(otherFrame.height(), size.height());
        QCOMPARE(otherFrame.fieldType(), fieldType);
        QCOMPARE(otherFrame.startTime(), startTime);
        QCOMPARE(otherFrame.endTime(), endTime);

        otherFrame.setStartTime(-1);

        QVERIFY(!buffer.isNull());

        QVERIFY(otherFrame.isValid());
        QCOMPARE(otherFrame.handleType(), handleType);
        QCOMPARE(otherFrame.pixelFormat(), pixelFormat);
        QCOMPARE(otherFrame.size(), size);
        QCOMPARE(otherFrame.width(), size.width());
        QCOMPARE(otherFrame.height(), size.height());
        QCOMPARE(otherFrame.fieldType(), fieldType);
        QCOMPARE(otherFrame.startTime(), qint64(-1));
        QCOMPARE(otherFrame.endTime(), endTime);
    }

    QVERIFY(!buffer.isNull());

    QVERIFY(frame.isValid());
    QCOMPARE(frame.handleType(), handleType);
    QCOMPARE(frame.pixelFormat(), pixelFormat);
    QCOMPARE(frame.size(), size);
    QCOMPARE(frame.width(), size.width());
    QCOMPARE(frame.height(), size.height());
    QCOMPARE(frame.fieldType(), fieldType);
    QCOMPARE(frame.startTime(), qint64(-1));
    QCOMPARE(frame.endTime(), endTime);

    frame = QVideoFrame();

    QVERIFY(buffer.isNull());

    QVERIFY(!frame.isValid());
    QCOMPARE(frame.handleType(), QAbstractVideoBuffer::NoHandle);
    QCOMPARE(frame.pixelFormat(), QVideoFrame::Format_Invalid);
    QCOMPARE(frame.size(), QSize());
    QCOMPARE(frame.width(), -1);
    QCOMPARE(frame.height(), -1);
    QCOMPARE(frame.fieldType(), QVideoFrame::ProgressiveFrame);
    QCOMPARE(frame.startTime(), qint64(-1));
    QCOMPARE(frame.endTime(), qint64(-1));
}