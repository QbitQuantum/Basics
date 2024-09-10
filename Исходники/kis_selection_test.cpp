void KisSelectionTest::testInvertSelection()
{
    KisSelectionSP selection = new KisSelection();
    KisPixelSelectionSP pixelSelection = selection->getOrCreatePixelSelection();
    pixelSelection->select(QRect(20, 20, 20, 20));
    QCOMPARE(pixelSelection->selected(30, 30), MAX_SELECTED);
    QCOMPARE(pixelSelection->selected(0, 0), MIN_SELECTED);
    QCOMPARE(pixelSelection->selected(512, 512), MIN_SELECTED);

    pixelSelection->invert();


    QCOMPARE(pixelSelection->selected(100, 100), MAX_SELECTED);
    QCOMPARE(pixelSelection->selected(22, 22), MIN_SELECTED);
    QCOMPARE(pixelSelection->selected(0, 0), MAX_SELECTED);
    QCOMPARE(pixelSelection->selected(512, 512), MAX_SELECTED);
    pixelSelection->convertToQImage(0, 0, 0, 100, 100).save("yyy.png");
    // XXX: This should happen automatically
    selection->updateProjection();
    selection->convertToQImage(0, 0, 0, 100, 100).save("zzz.png");

    QCOMPARE(selection->selectedExactRect(), QRect(qint32_MIN/2, qint32_MIN/2, qint32_MAX, qint32_MAX));
    QCOMPARE(selection->selectedRect(), QRect(qint32_MIN/2, qint32_MIN/2, qint32_MAX, qint32_MAX));

    QCOMPARE(selection->selected(100, 100), MAX_SELECTED);
    QCOMPARE(selection->selected(22, 22), MIN_SELECTED);
    QCOMPARE(selection->selected(10, 10), MAX_SELECTED);
    QCOMPARE(selection->selected(0, 0), MAX_SELECTED);
    QCOMPARE(selection->selected(512, 512), MAX_SELECTED);

}