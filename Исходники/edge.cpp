QPointF Edge::qualityTextPoint(const QLineF &linePos) {
	QPointF middlePoint;
	middlePoint.setX((linePos.x1() + linePos.x2()) / 2);
	middlePoint.setY((linePos.y1() + linePos.y2()) / 2);
	middlePoint.setY(middlePoint.y()-20);
	return middlePoint;
}