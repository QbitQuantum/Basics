void tst_QGraphicsPolygonItem::qgraphicspolygonitem()
{
    SubQGraphicsPolygonItem item;

    item.boundingRect();
    item.contains(QPoint());
    item.isObscuredBy(0);
    item.opaqueArea();
    //item.paint();
    item.shape();
    item.type();
    item.call_extension(QVariant());
    item.call_setExtension(SubQGraphicsPolygonItem::UserExtension, QVariant());
    item.call_supportsExtension(SubQGraphicsPolygonItem::UserExtension);
    item.fillRule();
    item.polygon();
    item.setFillRule(Qt::OddEvenFill);
    item.setPolygon(QPolygonF());
}