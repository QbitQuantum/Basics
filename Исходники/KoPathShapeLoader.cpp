void KoPathShapeLoaderPrivate::svgLineTo(qreal x1, qreal y1, bool abs)
{
    if (abs)
        lastPoint = QPointF(x1, y1);
    else
        lastPoint += QPointF(x1, y1);

    path->lineTo(lastPoint);
}