void KoPathPoint::paint(QPainter &painter, int handleRadius, PointTypes types, bool active)
{
    QRectF handle(-handleRadius, -handleRadius, 2*handleRadius, 2*handleRadius);

    bool drawControlPoint1 = types & ControlPoint1 && (!active || activeControlPoint1());
    bool drawControlPoint2 = types & ControlPoint2 && (!active || activeControlPoint2());

    // draw lines at the bottom
    if (drawControlPoint2)
        painter.drawLine(point(), controlPoint2());

    if (drawControlPoint1)
        painter.drawLine(point(), controlPoint1());


    QTransform worldMatrix = painter.worldTransform();

    painter.setWorldTransform(QTransform());

    // the point is lowest
    if (types & Node) {
        if (properties() & IsSmooth)
            painter.drawRect(handle.translated(worldMatrix.map(point())));
        else if (properties() & IsSymmetric) {
            QTransform matrix;
            matrix.rotate(45.0);
            QPolygonF poly(handle);
            poly = matrix.map(poly);
            poly.translate(worldMatrix.map(point()));
            painter.drawPolygon(poly);
        } else
            painter.drawEllipse(handle.translated(worldMatrix.map(point())));
    }

    // then comes control point 2
    if (drawControlPoint2)
        painter.drawEllipse(handle.translated(worldMatrix.map(controlPoint2())));

    // then comes control point 1
    if (drawControlPoint1)
        painter.drawEllipse(handle.translated(worldMatrix.map(controlPoint1())));

    painter.setWorldTransform(worldMatrix);
}