void tst_QVolatileImage::bitmap()
{
#ifdef Q_OS_SYMBIAN
    CFbsBitmap *bmp = new CFbsBitmap;
    QVERIFY(bmp->Create(TSize(100, 50), EColor64K) == KErrNone);
    QVolatileImage bmpimg(bmp);
    CFbsBitmap *dupbmp = static_cast<CFbsBitmap *>(bmpimg.duplicateNativeImage());
    QVERIFY(dupbmp);
    QVERIFY(dupbmp != bmp);
    QCOMPARE(dupbmp->DataAddress(), bmp->DataAddress());
    delete dupbmp;
    delete bmp;
    bmpimg.beginDataAccess();
    qMemSet(bmpimg.bits(), 0, bmpimg.byteCount());
    qMemSet(bmpimg.bits(), 1, bmpimg.bytesPerLine() * bmpimg.height());
    bmpimg.endDataAccess();

    // Test bgr->rgb conversion in case of EColor16M.
    bmp = new CFbsBitmap;
    QVERIFY(bmp->Create(TSize(101, 89), EColor16M) == KErrNone);
    bmp->BeginDataAccess();
    TUint32 *addr = bmp->DataAddress();
    uint rgb = QColor(10, 20, 30).rgb();
    qMemCopy(bmp->DataAddress(), &rgb, 3);
    bmp->EndDataAccess();
    TRgb symrgb;
    bmp->GetPixel(symrgb, TPoint(0, 0));
    QVERIFY(symrgb.Red() == 10 && symrgb.Green() == 20 && symrgb.Blue() == 30);
    bmpimg = QVolatileImage(bmp);
    QVERIFY(bmpimg.toImage().pixel(0, 0) == rgb);
    // check if there really was a conversion
    bmp->BeginDataAccess();
    bmpimg.beginDataAccess();
    qMemCopy(&rgb, bmpimg.constBits(), 3);
    uint rgb2 = rgb;
    qMemCopy(&rgb2, bmp->DataAddress(), 3);
    QVERIFY(rgb != rgb2);
    bmpimg.endDataAccess(true);
    bmp->EndDataAccess(true);
    delete bmp;

    bmp = new CFbsBitmap;
    QVERIFY(bmp->Create(TSize(101, 89), EGray2) == KErrNone);
    bmpimg = QVolatileImage(bmp); // inverts pixels, but should do it in place
    QCOMPARE(bmpimg.constBits(), (const uchar *) bmp->DataAddress());
    QCOMPARE(bmpimg.format(), QImage::Format_MonoLSB);
    bmpimg.ensureFormat(QImage::Format_ARGB32_Premultiplied);
    QVERIFY(bmpimg.constBits() != (const uchar *) bmp->DataAddress());
    QCOMPARE(bmpimg.format(), QImage::Format_ARGB32_Premultiplied);
    delete bmp;

    // The following two formats must be optimal always.
    bmp = new CFbsBitmap;
    QVERIFY(bmp->Create(TSize(101, 89), EColor16MAP) == KErrNone);
    bmpimg = QVolatileImage(bmp);
    QCOMPARE(bmpimg.format(), QImage::Format_ARGB32_Premultiplied);
    QCOMPARE(bmpimg.constBits(), (const uchar *) bmp->DataAddress());
    bmpimg.ensureFormat(QImage::Format_ARGB32_Premultiplied);
    QCOMPARE(bmpimg.constBits(), (const uchar *) bmp->DataAddress());
    delete bmp;
    bmp = new CFbsBitmap;
    QVERIFY(bmp->Create(TSize(101, 89), EColor16MU) == KErrNone);
    bmpimg = QVolatileImage(bmp);
    QCOMPARE(bmpimg.format(), QImage::Format_RGB32);
    QCOMPARE(bmpimg.constBits(), (const uchar *) bmp->DataAddress());
    bmpimg.ensureFormat(QImage::Format_RGB32);
    QCOMPARE(bmpimg.constBits(), (const uchar *) bmp->DataAddress());
    delete bmp;

#else
    QSKIP("CFbsBitmap is only available on Symbian, skipping bitmap test", SkipSingle);
#endif
}