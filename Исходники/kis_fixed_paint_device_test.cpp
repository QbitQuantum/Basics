void KisFixedPaintDeviceTest::testMirroring()
{
    QFETCH(QRect, rc);
    QFETCH(bool, mirrorHorizontally);
    QFETCH(bool, mirrorVertically);

    const KoColorSpace *cs = KoColorSpaceRegistry::instance()->rgb8();
    KisFixedPaintDeviceSP dev = new KisFixedPaintDevice(cs);
    dev->setRect(rc);
    dev->initialize();

    KoColor c(Qt::black, cs);

    qsrand(1);
    int value = 0;

    for (int i = rc.x(); i < rc.x() + rc.width(); i++) {
        for (int j = rc.y(); j < rc.y() + rc.height(); j++) {
            setPixel(dev, i, j, value);
            value = qrand() % 255;
        }
        value = qrand() % 255;
    }

    //dev->convertToQImage(0).save("0_a.png");
    dev->mirror(mirrorHorizontally, mirrorVertically);
    //dev->convertToQImage(0).save("0_b.png");

    int startX;
    int endX;
    int incX;

    int startY;
    int endY;
    int incY;

    if (mirrorHorizontally) {
        startX = rc.x() + rc.width() - 1;
        endX = rc.x() - 1;
        incX = -1;
    } else {
        startX = rc.x();
        endX = rc.x() + rc.width();
        incX = 1;
    }

    if (mirrorVertically) {
        startY = rc.y() + rc.height() - 1;
        endY = rc.y() - 1;
        incY = -1;
    } else {
        startY = rc.y();
        endY = rc.y() + rc.height();
        incY = 1;
    }

    qsrand(1);
    value = 0;

    for (int i = startX; i != endX ; i += incX) {
        for (int j = startY; j != endY; j += incY) {
            QCOMPARE(pixel(dev, i, j), (quint8)value);
            value = qrand() % 255;
        }
        value = qrand() % 255;
    }
}