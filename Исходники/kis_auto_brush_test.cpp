void KisAutoBrushTest::testMaskGeneration()
{
    KisCircleMaskGenerator* circle = new KisCircleMaskGenerator(10, 1.0, 1.0, 1.0, 2, false);
    KisBrushSP a = new KisAutoBrush(circle, 0.0, 0.0);
    const KoColorSpace * cs = KoColorSpaceRegistry::instance()->rgb8();

    KisPaintInformation info(QPointF(100.0, 100.0), 0.5);

    // check masking an existing paint device
    KisFixedPaintDeviceSP fdev = new KisFixedPaintDevice(cs);
    fdev->setRect(QRect(0, 0, 100, 100));
    fdev->initialize();
    cs->setOpacity(fdev->data(), OPACITY_OPAQUE_U8, 100 * 100);

    QPoint errpoint;
    QImage result(QString(FILES_DATA_DIR) + QDir::separator() + "result_autobrush_1.png");
    QImage image = fdev->convertToQImage(0);

    if (!TestUtil::compareQImages(errpoint, image, result)) {
        image.save("kis_autobrush_test_1.png");
        QFAIL(QString("Failed to create identical image, first different pixel: %1,%2 \n").arg(errpoint.x()).arg(errpoint.y()).toLatin1());
    }

    // Check creating a mask dab with a single color
    fdev = new KisFixedPaintDevice(cs);
    a->mask(fdev, KoColor(Qt::black, cs), KisDabShape(), info);

    result = QImage(QString(FILES_DATA_DIR) + QDir::separator() + "result_autobrush_3.png");
    image = fdev->convertToQImage(0);
    if (!TestUtil::compareQImages(errpoint, image, result)) {
        image.save("kis_autobrush_test_3.png");
        QFAIL(QString("Failed to create identical image, first different pixel: %1,%2 \n").arg(errpoint.x()).arg(errpoint.y()).toLatin1());
    }

    // Check creating a mask dab with a color taken from a paint device
    KoColor red(Qt::red, cs);
    cs->setOpacity(red.data(), quint8(128), 1);
    KisPaintDeviceSP dev = new KisPaintDevice(cs);
    dev->fill(0, 0, 100, 100, red.data());

    fdev = new KisFixedPaintDevice(cs);
    a->mask(fdev, dev, KisDabShape(), info);

    result = QImage(QString(FILES_DATA_DIR) + QDir::separator() + "result_autobrush_4.png");
    image = fdev->convertToQImage(0);
    if (!TestUtil::compareQImages(errpoint, image, result)) {
        image.save("kis_autobrush_test_4.png");
        QFAIL(QString("Failed to create identical image, first different pixel: %1,%2 \n").arg(errpoint.x()).arg(errpoint.y()).toLatin1());
    }

}