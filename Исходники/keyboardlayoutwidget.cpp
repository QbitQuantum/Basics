void KeyboardLayoutWidget::drawCurveRectangle(QPainter* painter, bool filled, QColor color, int x, int y, int width, int height, double radius)
{
    double x1, y1;

    if (!width || !height)
        return;

    x1 = x + width;
    y1 = y + height;

    radius = qMin (radius, (double) qMin (width / 2, height / 2));

    QPainterPath path;

    path.moveTo(x, y + radius);
    path.arcTo(x, y, 2 * radius, 2 * radius, 180, -90);
    path.lineTo (x1 - radius, y);
    path.arcTo (x1 - 2 * radius, y, 2 * radius, 2 * radius, 90, - 90);
    path.lineTo (x1, y1 - radius);
    path.arcTo (x1 - 2 * radius, y1 - 2 * radius, 2 * radius, 2 * radius, 0, -90);
    path.lineTo (x + radius, y1);
    path.arcTo (x , y1 - 2 * radius, 2 * radius, 2 * radius, -90, -90);
    path.closeSubpath();

    painter->save();
    if (filled) {
        QBrush brush(color);
        painter->fillPath (path, brush);
    }
    else {
        painter->setPen(color);
        painter->drawPath(path);
    }
    painter->restore();
}