void KisScanlineFillTest::testFillGeneral(const QVector<KisFillInterval> &initialBackwardIntervals,
                                          const QVector<QColor> &expectedResult,
                                          const QVector<KisFillInterval> &expectedForwardIntervals,
                                          const QVector<KisFillInterval> &expectedBackwardIntervals)
{
    const KoColorSpace * cs = KoColorSpaceRegistry::instance()->rgb8();
    KisPaintDeviceSP dev = new KisPaintDevice(cs);

    dev->setPixel(1, 0, Qt::white);
    dev->setPixel(2, 0, Qt::white);
    dev->setPixel(5, 0, Qt::white);
    dev->setPixel(8, 0, Qt::white);
    dev->setPixel(17, 0, Qt::white);

    QRect boundingRect(-10, -10, 30, 30);

    KisScanlineFill gc(dev, QPoint(), boundingRect);

    KisFillIntervalMap *backwardMap = gc.testingGetBackwardIntervals();
    Q_FOREACH (const KisFillInterval &i, initialBackwardIntervals) {
        backwardMap->insertInterval(i);
    }