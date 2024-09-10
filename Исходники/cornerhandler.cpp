void CornerHandler::doSetRect(const QRectF &newRect) {
	setFlag(QGraphicsItem::ItemIgnoresTransformations,false);
	setRect(mapFromParent(newRect).boundingRect());
}