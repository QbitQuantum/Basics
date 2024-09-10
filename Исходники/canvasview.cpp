void CanvasView::drawForeground(QPainter *painter, const QRectF& rect)
{
	if(_enableoutline && _showoutline && _outlinesize>1 && !_locked) {
		const QRectF outline(_prevpoint-QPointF(_outlinesize,_outlinesize),
					QSizeF(_dia, _dia));
		if(rect.intersects(outline)) {
			painter->save();
			QPen pen(Qt::white);
			pen.setCosmetic(true);
			painter->setPen(pen);
			painter->setCompositionMode(QPainter::CompositionMode_Difference);
			painter->drawEllipse(outline);
			painter->restore();
		}
	}
}