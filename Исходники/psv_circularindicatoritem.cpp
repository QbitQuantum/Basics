void PSV_CircularIndicatorItem::drawOuterCircle(int zValue)
{
    QRadialGradient outerGradient(m_rect.center(), m_outerRadius, m_rect.center());
    outerGradient.setColorAt(0.0, QColor(200, 200, 200));
    outerGradient.setColorAt(0.9, QColor(80, 80, 80));
    outerGradient.setColorAt(0.95, QColor(180, 180, 180));
    outerGradient.setColorAt(1.0, QColor(80, 80, 80));
    //==========================
    QPen pen(Qt::NoPen);
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(this);
    item->setRect(m_rect.center().x() - m_outerRadius, m_rect.center().y() - m_outerRadius, m_outerRadius*2, m_outerRadius*2);
    item->setPen(pen);
    item->setBrush(outerGradient);
    item->setZValue(zValue);
    {//TEST

        QGraphicsRectItem *item = new QGraphicsRectItem(m_rect, this);
        item->setPen(QPen(Qt::blue));
        //        item->setPen();
    }
}