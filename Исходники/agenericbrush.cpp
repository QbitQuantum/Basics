QRect AGenericBrush::move(const QString &brush, QPainter &painter,const QPoint &oldPos, const QPoint &newPos)
{
	painter.save();

	int rad = painter.pen().width();
	QRect boundingRect = QRect(oldPos, newPos).normalized().adjusted(-rad, -rad, +rad, +rad);
	QColor color = painter.pen().color();
	int thickness = painter.pen().width();
	QColor transparentColor(color.red(), color.green(), color.blue(), 0);
	
	QPainterPath path;
	path.setFillRule ( Qt::WindingFill );
// 	m_path.setFillRule ( Qt::WindingFill );
	path.moveTo(oldPos);
	path.lineTo(newPos);
	
	m_path.closeSubpath();
	m_path.addPath(path);

	painter.drawPath(path);
	
	painter.restore();
	return boundingRect;
}