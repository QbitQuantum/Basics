void tst_QCameraBackend::testCaptureToBuffer()
{
    QCamera camera;
    QCameraImageCapture imageCapture(&camera);
    camera.exposure()->setFlashMode(QCameraExposure::FlashOff);

    camera.load();

#ifdef Q_WS_MAEMO_6
    QVERIFY(imageCapture.isCaptureDestinationSupported(QCameraImageCapture::CaptureToBuffer));
#endif

    if (!imageCapture.isCaptureDestinationSupported(QCameraImageCapture::CaptureToBuffer))
        QSKIP("Buffer capture not supported");

    QTRY_COMPARE(camera.status(), QCamera::LoadedStatus);

    QCOMPARE(imageCapture.bufferFormat(), QVideoFrame::Format_Jpeg);

    QVERIFY(imageCapture.isCaptureDestinationSupported(QCameraImageCapture::CaptureToFile));
    QVERIFY(imageCapture.isCaptureDestinationSupported(QCameraImageCapture::CaptureToBuffer));
    QVERIFY(imageCapture.isCaptureDestinationSupported(
                QCameraImageCapture::CaptureToBuffer | QCameraImageCapture::CaptureToFile));

    QSignalSpy destinationChangedSignal(&imageCapture, SIGNAL(captureDestinationChanged(QCameraImageCapture::CaptureDestinations)));

    QCOMPARE(imageCapture.captureDestination(), QCameraImageCapture::CaptureToFile);
    imageCapture.setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    QCOMPARE(imageCapture.captureDestination(), QCameraImageCapture::CaptureToBuffer);
    QCOMPARE(destinationChangedSignal.size(), 1);
    QCOMPARE(destinationChangedSignal.first().first().value<QCameraImageCapture::CaptureDestinations>(),
             QCameraImageCapture::CaptureToBuffer);

    QSignalSpy capturedSignal(&imageCapture, SIGNAL(imageCaptured(int,QImage)));
    QSignalSpy imageAvailableSignal(&imageCapture, SIGNAL(imageAvailable(int,QVideoFrame)));
    QSignalSpy savedSignal(&imageCapture, SIGNAL(imageSaved(int,QString)));
    QSignalSpy errorSignal(&imageCapture, SIGNAL(error(int, QCameraImageCapture::Error,QString)));

    camera.start();
    QTRY_VERIFY(imageCapture.isReadyForCapture());

    int id = imageCapture.capture();
    QTRY_VERIFY(!imageAvailableSignal.isEmpty());

    QVERIFY(errorSignal.isEmpty());
    QVERIFY(!capturedSignal.isEmpty());
    QVERIFY(!imageAvailableSignal.isEmpty());

    QTest::qWait(2000);
    QVERIFY(savedSignal.isEmpty());

    QCOMPARE(capturedSignal.first().first().toInt(), id);
    QCOMPARE(imageAvailableSignal.first().first().toInt(), id);

    QVideoFrame frame = imageAvailableSignal.first().last().value<QVideoFrame>();
    QVERIFY(frame.isValid());
    QCOMPARE(frame.pixelFormat(), QVideoFrame::Format_Jpeg);
    QVERIFY(!frame.size().isEmpty());
    QVERIFY(frame.map(QAbstractVideoBuffer::ReadOnly));
    QByteArray data((const char *)frame.bits(), frame.mappedBytes());
    frame.unmap();
    frame = QVideoFrame();

    QVERIFY(!data.isEmpty());
    QBuffer buffer;
    buffer.setData(data);
    buffer.open(QIODevice::ReadOnly);
    QImageReader reader(&buffer, "JPG");
    reader.setScaledSize(QSize(640,480));
    QImage img(reader.read());
    QVERIFY(!img.isNull());

    capturedSignal.clear();
    imageAvailableSignal.clear();
    savedSignal.clear();

    //Capture to yuv buffer
#ifdef Q_WS_MAEMO_6
    QVERIFY(imageCapture.supportedBufferFormats().contains(QVideoFrame::Format_UYVY));
#endif

    if (imageCapture.supportedBufferFormats().contains(QVideoFrame::Format_UYVY)) {
        imageCapture.setBufferFormat(QVideoFrame::Format_UYVY);
        QCOMPARE(imageCapture.bufferFormat(), QVideoFrame::Format_UYVY);

        id = imageCapture.capture();
        QTRY_VERIFY(!imageAvailableSignal.isEmpty());

        QVERIFY(errorSignal.isEmpty());
        QVERIFY(!capturedSignal.isEmpty());
        QVERIFY(!imageAvailableSignal.isEmpty());
        QVERIFY(savedSignal.isEmpty());

        QTest::qWait(2000);
        QVERIFY(savedSignal.isEmpty());

        frame = imageAvailableSignal.first().last().value<QVideoFrame>();
        QVERIFY(frame.isValid());

        qDebug() << frame.pixelFormat();
        QCOMPARE(frame.pixelFormat(), QVideoFrame::Format_UYVY);
        QVERIFY(!frame.size().isEmpty());
        frame = QVideoFrame();

        capturedSignal.clear();
        imageAvailableSignal.clear();
        savedSignal.clear();

        imageCapture.setBufferFormat(QVideoFrame::Format_Jpeg);
        QCOMPARE(imageCapture.bufferFormat(), QVideoFrame::Format_Jpeg);
    }

    //Try to capture to both buffer and file
#ifdef Q_WS_MAEMO_6
    QVERIFY(imageCapture.isCaptureDestinationSupported(QCameraImageCapture::CaptureToBuffer | QCameraImageCapture::CaptureToFile));
#endif
    if (imageCapture.isCaptureDestinationSupported(QCameraImageCapture::CaptureToBuffer | QCameraImageCapture::CaptureToFile)) {
        imageCapture.setCaptureDestination(QCameraImageCapture::CaptureToBuffer | QCameraImageCapture::CaptureToFile);

        int oldId = id;
        id = imageCapture.capture();
        QVERIFY(id != oldId);
        QTRY_VERIFY(!savedSignal.isEmpty());

        QVERIFY(errorSignal.isEmpty());
        QVERIFY(!capturedSignal.isEmpty());
        QVERIFY(!imageAvailableSignal.isEmpty());
        QVERIFY(!savedSignal.isEmpty());

        QCOMPARE(capturedSignal.first().first().toInt(), id);
        QCOMPARE(imageAvailableSignal.first().first().toInt(), id);

        frame = imageAvailableSignal.first().last().value<QVideoFrame>();
        QVERIFY(frame.isValid());
        QCOMPARE(frame.pixelFormat(), QVideoFrame::Format_Jpeg);
        QVERIFY(!frame.size().isEmpty());

        QString fileName = savedSignal.first().last().toString();
        QVERIFY(QFileInfo(fileName).exists());
    }
}