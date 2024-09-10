void tst_QGraphicsEffect::boundingRect()
{
    // No source; empty bounding rect.
    CustomEffect *effect = new CustomEffect;
    QCOMPARE(effect->boundingRect(), QRectF());

    // Install effect on QGraphicsItem.
    QRectF itemRect(0, 0, 100, 100);
    QGraphicsRectItem *item = new QGraphicsRectItem;
    item->setRect(itemRect);
    item->setGraphicsEffect(effect);
    int margin = effect->margin();
    QCOMPARE(effect->boundingRect(), itemRect.adjusted(-margin, -margin, margin, margin));
    QCOMPARE(effect->boundingRect(), effect->boundingRectFor(itemRect));

    // Make sure disabling/enabling the effect doesn't change the bounding rect.
    effect->setEnabled(false);
    QCOMPARE(effect->boundingRect(), itemRect.adjusted(-margin, -margin, margin, margin));
    QCOMPARE(effect->boundingRect(), effect->boundingRectFor(itemRect));
    effect->setEnabled(true);
    QCOMPARE(effect->boundingRect(), itemRect.adjusted(-margin, -margin, margin, margin));
    QCOMPARE(effect->boundingRect(), effect->boundingRectFor(itemRect));

    // Change effect margins.
    effect->setMargin(margin = 20);
    QCOMPARE(effect->boundingRect(), itemRect.adjusted(-margin, -margin, margin, margin));
    QCOMPARE(effect->boundingRect(), effect->boundingRectFor(itemRect));

    // Uninstall effect on QGraphicsItem.
    QPointer<CustomEffect> ptr = effect;
    item->setGraphicsEffect(0);
    QVERIFY(!ptr);

    delete item;
}