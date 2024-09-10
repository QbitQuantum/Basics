bool AbstractItemContainer::itemVisibleInView(AbstractViewItem* item, const QRectF &viewRect, bool fullyVisible) const
{
    if (!item || !m_itemView)
        return false;

    QRectF itemRectBoundingRect = item->mapToItem(m_itemView, item->boundingRect()).boundingRect();

    if (fullyVisible && viewRect.contains(itemRectBoundingRect))
        return true;
    else if (viewRect.intersects(itemRectBoundingRect))
        return true;

    return false;
}