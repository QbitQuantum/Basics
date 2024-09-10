void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    QPen pen(Qt::black, 2);
    QBrush brush(Qt::red);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawEllipse(rect());
    painter->drawText(rect(), Qt::AlignCenter, label);

    if (!subscript.isEmpty()) {
        QRectF subRect;
        subRect.setRect(cx - 1.65*r, cy + 1.15*r, 15, 15);
        painter->drawText(subRect, Qt::AlignCenter, subscript);
        scene()->update(subRect);
    }
}