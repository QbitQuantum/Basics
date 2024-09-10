void CurveWidget::paintEvent(QPaintEvent * /* event */)
{        
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing, true);
	static const QColor BASE_COLOR(Qt::black);
	static const QColor AXE_COLOR(Qt::black);
	
	QColor EXTREMITY_COLOR(isEnabled()? Qt::red : Qt::gray);
	QColor CURVE_COLOR(isEnabled()? Qt::darkRed : Qt::gray);
	QColor BREAKPOINT_COLOR(isEnabled()? Qt::blue : Qt::gray);
	
	static const QColor MOVING_BREAKPOINT_COLOR(Qt::darkBlue);
	static const QColor UNACTIVE_COLOR(Qt::darkGray);
	
	// Abcisses line
	QPen penXAxis((_unactive) ? UNACTIVE_COLOR : AXE_COLOR);
	
	painter->setPen(penXAxis);
	painter->drawLine(0, _xAxisPos, width(), _xAxisPos);
	
	painter->setPen(BASE_COLOR);
	
	vector<float>::iterator it;
	map<float, pair<float, float> >::iterator it2;
	float pointSizeX = 6;
	float pointSizeY = 6;
	QPointF curPoint(0, 0);
	QPointF precPoint(-1, -1);
	
	unsigned int i = 0;
	
	for (it = _abstract->_curve.begin(); it != _abstract->_curve.end(); ++it) 
	{
		curPoint = absoluteCoordinates(QPointF(1, *it));
		curPoint.setX(i * _interspace * _scaleX);
		
		if (it == _abstract->_curve.begin()) 
		{   // First point is represented by a specific color
			painter->fillRect(QRectF(curPoint - QPointF(pointSizeX / 2., pointSizeY / 2.), QSizeF(pointSizeX, pointSizeY)), EXTREMITY_COLOR);
		}
		
		if (precPoint != QPointF(-1, -1)) 
		{
			QPen pen(_unactive ? UNACTIVE_COLOR : CURVE_COLOR);
			pen.setWidth(_unactive ? 1 : 2);
			
			painter->setPen(pen);
			painter->drawLine(precPoint, curPoint);  // Draw lines between values
			
			painter->setPen(BASE_COLOR);
		}
		
		precPoint = curPoint;
		i++;
	}
	
	// Last point is represented by a specific color
	if (!_unactive) 
	{
		painter->fillRect(QRectF(curPoint - QPointF(pointSizeX / 2., pointSizeY / 2.), 
								 QSizeF(pointSizeX, pointSizeY)), 
						  EXTREMITY_COLOR);
		
		precPoint = QPointF(-1, -1);
		for (it2 = _abstract->_breakpoints.begin(); it2 != _abstract->_breakpoints.end(); ++it2) 
		{
			curPoint = absoluteCoordinates(QPointF(it2->first, it2->second.first));
			
			// Breakpoints are drawn with rectangles
			painter->fillRect(QRectF(curPoint - QPointF(pointSizeX / 2., pointSizeY / 2.), 
									 QSizeF(pointSizeX, pointSizeY)), 
							  _unactive ? UNACTIVE_COLOR : BREAKPOINT_COLOR);
			precPoint = curPoint;
		}
		
		if (_movingBreakpointX != -1 && _movingBreakpointY != -1) 
		{
			QPointF cursor = absoluteCoordinates(QPointF(_movingBreakpointX, _movingBreakpointY));
			
			// If a breakpoint is currently being moved, it is represented by a rectangle
			painter->fillRect(QRectF(cursor - QPointF(pointSizeX / 2., pointSizeY / 2.), 
									 QSizeF(pointSizeX, pointSizeY)), 
							  _abstract->_interpolate ? MOVING_BREAKPOINT_COLOR : UNACTIVE_COLOR);
		}
	}
	
	//text : minY, maxY
	if(_minYModified || _maxYModified)
	{
		painter->save();
		QFont textFont;
		textFont.setPointSize(9.);
		painter->setFont(textFont);
		painter->setPen(QPen(Qt::black));
		if(_minYModified)
		{
			painter->drawText(*_minYTextRect,QString("%1").arg(_minY));
			_minYModified = false;
		}
		else if(_maxYModified)
		{
			painter->drawText(*_maxYTextRect,QString("%1").arg(_maxY));
			_maxYModified = false;
		}
		painter->restore();
	}
	
	delete painter;
}