void KisConvolutionPainterTest::testGaussianSmall(bool useFftw)
{
    KisPaintDeviceSP dev = new KisPaintDevice(KoColorSpaceRegistry::instance()->rgb8());

    KoColor c(Qt::yellow, dev->colorSpace());

    for (int i = 0; i < 50; i++) {
        quint8 baseOpacity = 75;
        KoColor c(Qt::magenta, dev->colorSpace());

        for (int j = 0; j <= 6; j++) {
            c.setOpacity(static_cast<quint8>(baseOpacity + 30 * j));
            dev->setPixel(i + j, i, c);
        }
    }

    testGaussianBase(dev, useFftw, "reduced");
}