void KoShapeStroke::Private::paintBorder(KoShape *shape, QPainter &painter, const QPen &pen) const
{
    if (!pen.isCosmetic()) {
        KoPathShape *pathShape = dynamic_cast<KoPathShape *>(shape);
        if (pathShape) {
            QPainterPath path = pathShape->pathStroke(pen);
            painter.fillPath(path, pen.brush());
            return;
        }
        painter.strokePath(shape->outline(), pen);
    }
}