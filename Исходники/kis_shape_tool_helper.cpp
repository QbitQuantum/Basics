KoShape* KisShapeToolHelper::createRectangleShape(const QRectF& rect)
{
    KoShape* shape;
    KoShapeFactoryBase *rectFactory = KoShapeRegistry::instance()->value("RectangleShape");
    if (rectFactory) {
        shape = rectFactory->createDefaultShape();
        shape->setSize(rect.size());
        shape->setPosition(rect.topLeft());
    } else {
        //Fallback if the plugin wasn't found
        KoPathShape* path = new KoPathShape();
        path->setShapeId(KoPathShapeId);
        path->moveTo(rect.topLeft());
        path->lineTo(rect.topLeft() + QPointF(rect.width(), 0));
        path->lineTo(rect.bottomRight());
        path->lineTo(rect.topLeft() + QPointF(0, rect.height()));
        path->close();
        path->normalize();
        shape = path;
    }
    return shape;
}