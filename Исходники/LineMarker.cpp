void LineMarker::draw(QPainter *p, const QwtScaleMap &xMap, const QwtScaleMap &yMap, const QRect &r) const
{	
	const int x0 = xMap.transform(d_rect.left());
	const int y0 = yMap.transform(d_rect.top());
	const int x1 = xMap.transform(d_rect.right());
	const int y1 = yMap.transform(d_rect.bottom());
	
	p->save();
	p->setPen(pen);
	QBrush brush=QBrush(pen.color(), QBrush::SolidPattern);
	QwtPainter::drawLine(p,x0,y0,x1,y1);
	p->restore();
		
	if (endArrow)
		{
		p->save();
		p->translate(x1,y1);
		const double t = teta(x0, y0, x1, y1);
		p->rotate(-t);

		const QPointArray endArray(3);	
		endArray[0] = QPoint(0,0);
			
		int d=(int)floor(d_headLength*tan(M_PI*d_headAngle/180.0)+0.5);				
		endArray[1] = QPoint(-d_headLength,d);
		endArray[2] = QPoint(-d_headLength,-d);

		p->setPen(QPen(pen.color(),pen.width(),Qt::SolidLine));
		if (filledArrow)
			p->setBrush(brush);

		QwtPainter::drawPolygon(p,endArray);
		p->restore();
		}

	if (startArrow)
		{
		p->save();
		p->translate(x0,y0);
		const double t = teta(x0, y0, x1, y1);
		p->rotate(-t);

		const QPointArray startArray(3);	
		startArray[0] = QPoint(0,0);
			
		int d=(int)floor(d_headLength*tan(M_PI*d_headAngle/180.0)+0.5);
		startArray[1] = QPoint(d_headLength,d);
		startArray[2] = QPoint(d_headLength,-d);

		p->setPen(QPen(pen.color(), pen.width(), Qt::SolidLine));
		if (filledArrow)
			p->setBrush(brush);
		QwtPainter::drawPolygon(p,startArray);
		p->restore();
		}
}