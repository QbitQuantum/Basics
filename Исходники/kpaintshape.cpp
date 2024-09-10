void KPaintShape::paintEllipse(QPainter &painter, const QPointF &startPoint, 
	const QPointF &endPoint, float rotateAngle, bool bScale)
{
	QPointF central = calShapeCentralPoint(startPoint,endPoint);
	setShapePainter(painter, central, rotateAngle, bScale); 
	QRectF rectF(startPoint, endPoint);
	painter.drawEllipse(rectF);
}