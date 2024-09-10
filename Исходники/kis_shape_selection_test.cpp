void KisShapeSelectionTest::testAddChild()
{
    const KoColorSpace * cs = KoColorSpaceRegistry::instance()->rgb8();
    KisImageSP image = new KisImage(new KisUndoAdapter(0), 300, 300, cs, "test");

    KisSelectionSP selection = new KisSelection();
    QVERIFY(selection->hasPixelSelection() == false);
    QVERIFY(selection->hasShapeSelection() == false);
    KisPixelSelectionSP pixelSelection = selection->getOrCreatePixelSelection();

    pixelSelection->select(QRect(0, 0, 100, 100));
    // Selection is using the pixel selection as datamanager so no projection update
    // needed
    QCOMPARE(pixelSelection->selected(25, 25), MAX_SELECTED);
    QCOMPARE(selection->selectedExactRect(), QRect(0, 0, 100, 100));

    QRect rect(50, 50, 100, 100);
    QTransform matrix;
    matrix.scale(1 / image->xRes(), 1 / image->yRes());
    rect = matrix.mapRect(rect);

    KoPathShape* shape = new KoPathShape();
    shape->setShapeId(KoPathShapeId);
    shape->moveTo(rect.topLeft());
    shape->lineTo(rect.topLeft() + QPointF(rect.width(), 0));
    shape->lineTo(rect.bottomRight());
    shape->lineTo(rect.topLeft() + QPointF(0, rect.height()));
    shape->close();
    shape->normalize();

    KisShapeSelection * shapeSelection = new KisShapeSelection(image, selection);
    selection->setShapeSelection(shapeSelection);
    shapeSelection->addShape(shape);

    QCOMPARE(pixelSelection->selected(25, 25), MAX_SELECTED);
    QCOMPARE(selection->selectedExactRect(), QRect(0, 0, 150, 150));

    selection->updateProjection();
}