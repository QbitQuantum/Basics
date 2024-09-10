void MapView::drawArrow(QPainter &painter, const QPoint &p)
{
    QPainterPath path;

    path.moveTo(0, 0);
    path.lineTo(1, 0);
    path.lineTo(7, 15);
    path.lineTo(0, 10);
    path.lineTo(-7, 15);
    path.lineTo(0, 0);

    path.translate(p);
    path.translate(0, 2);

    painter.fillPath(path, QBrush(Qt::yellow));
}