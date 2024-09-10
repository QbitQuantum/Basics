void SelectLocation::paintEvent(QPaintEvent *paintevent)
{
	QPainter painter;
	QPainterPath roundedrect;
	roundedrect.addRoundRect(this->rect(),20);
	
	painter.setOpacity(0.8);
	painter.fillPath(roundedrect,QColor(Qt::black));
	painter.setOpacity(1);
	
}