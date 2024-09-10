QPainterPath ArrowItem::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    if (m_shaftItem &&m_shaftItem->path() != QPainterPath()) {
        QPainterPathStroker ps;
        QPen pen = m_shaftItem->pen();
        ps.setCapStyle(pen.capStyle());
        ps.setJoinStyle(pen.joinStyle());
        ps.setMiterLimit(pen.miterLimit());
        // overwrite pen width to make selection more lazy
        ps.setWidth(16.0);
        QPainterPath p = ps.createStroke(m_shaftItem->path());
        path.addPath(p);
    }
    if (m_startHeadItem)
        path.addRect(mapRectFromItem(m_startHeadItem, m_startHeadItem->boundingRect()));
    if (m_endHeadItem)
        path.addRect(mapRectFromItem(m_endHeadItem, m_endHeadItem->boundingRect()));
    return path;
}