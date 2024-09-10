void KoCreatePathTool::paintPath(KoPathShape& pathShape, QPainter &painter, const KoViewConverter &converter)
{
    Q_D(KoCreatePathTool);
    painter.setTransform(pathShape.absoluteTransformation(&converter) * painter.transform());
    painter.save();

    KoShapePaintingContext paintContext; //FIXME
    pathShape.paint(painter, converter, paintContext);
    painter.restore();
    if (pathShape.stroke()) {
        painter.save();
        pathShape.stroke()->paint(d->shape, painter, converter);
        painter.restore();
    }
}