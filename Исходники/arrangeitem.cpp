void ArrangeItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsItem::mousePressEvent(event);
    setCursor(getCursorByPos(event->pos()));
    m_timer->stop();
}