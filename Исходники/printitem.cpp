QGraphicsItem* CGraphicsRectItem::createItem()
{
	QGraphicsRectItem* pItem = new QGraphicsRectItem(m_Parent);

	drawPen(pItem);
	drawBrush(pItem);

	pItem->setRect(GET_VALUE(x).toInt(),GET_VALUE(y).toInt(),GET_VALUE(w).toInt(),GET_VALUE(h).toInt());
	return pItem;
}