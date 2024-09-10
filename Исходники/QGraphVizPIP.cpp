void QGraphVizPIP::drawBackground(QPainter *painter, const QRectF &rect)
{

    if(!rect.intersects(scene()->sceneRect())) {
        return;
    }

    QPen borderPen;
    borderPen.setColor(Qt::black);
    painter->setPen(borderPen);

    QRectF border = QRectF(mapToScene(1.0, 1.0),
                           mapToScene(width()-2.0, height()-2.0));

    painter->drawRect(border);
}