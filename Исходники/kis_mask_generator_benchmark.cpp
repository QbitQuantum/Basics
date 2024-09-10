void benchmarkSIMD(qreal fade) {
    const KoColorSpace * cs = KoColorSpaceRegistry::instance()->rgb8();
    KisFixedPaintDeviceSP dev = new KisFixedPaintDevice(cs);
    dev->setRect(QRect(0, 0, 1000, 1000));
    dev->initialize();

    MaskProcessingData data(dev, cs,
                            0.0, 1.0,
                            500, 500, 0);

    KisCircleMaskGenerator gen(1000, 1.0, fade, fade, 2, false);

    KisBrushMaskApplicatorBase *applicator = gen.applicator();
    applicator->initializeData(&data);

    QVector<QRect> rects = KritaUtils::splitRectIntoPatches(dev->bounds(), QSize(63, 63));

    QBENCHMARK{
        Q_FOREACH (const QRect &rc, rects) {
            applicator->process(rc);
        }
    }