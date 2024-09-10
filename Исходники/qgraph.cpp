void QGraph::paintEvent( QPaintEvent * ){
	if(!valid)
		pintafunc(NULL);
	front = buffer;
	finestra.begin(&front, this);
	QPen pfunc;
	QPen ccursor;
	QPoint ultim;
	
	pfunc.setColor(QColor(0,150,0));
	pfunc.setCapStyle(Qt::RoundCap);
	pfunc.setWidth(2);
	
	if(this->hasMouseTracking() && this->cursor().shape() != Qt::PointingHandCursor) {
		ccursor.setColor(QColor(0xc0,0,0));
		ccursor.setStyle(Qt::SolidLine);
		finestra.setPen(ccursor);
		finestra.drawLine(toWidget(viewport.left(),mark.y()), QPoint(this->width(), toWidget(viewport.right()+1, mark.y()).y()));
		finestra.drawLine(QPoint(toWidget(mark.x(),viewport.top()).x(), this->height()), QPoint( toWidget(mark.x(),viewport.bottom()+1).x(), 0));
		
		int w=110, h=13;
		ultim = toWidget(mark.x(), mark.y(), NULL);
		
		if(ultim.x()+w+10 > this->width())
			ultim.setX(this->width()-w-10);
		if(ultim.y()+h+10 > this->height())
			ultim.setY(this->height()-h-10);
		if(ultim.y() < 0)
			ultim.setY(-10);
		
		finestra.setPen(QPen(QColor(0,0,0)));
		finestra.drawText(ultim.x()+15, ultim.y()+15, QString("x=%1 y=%2") .arg(mark.x(),3,'f',2).arg(mark.y(),3,'f',2));
#if 0
		ultim = toWidget(mark.x(), mark.y(), NULL);
		//micepos->setText(QString("<qt>x=<b>%1</b> &nbsp; y=<b>%1</b></qt>") .arg(mark.x(),3,'f',2).arg(mark.y(),3,'f',2));
		
		if(ultim.x()+micepos->width()+10 > this->width())
			ultim.setX(this->width()-micepos->width()-10);
		if(ultim.y()+micepos->height()+10 > this->height())
			ultim.setY(this->height()-micepos->height()-10);
		else if(ultim.y() < 0)
		ultim.setY(-10);
		
		micepos->setGeometry(ultim.x()+10, ultim.y()+10, 160, 23);
#endif
	} else if(this->hasMouseTracking() && pushed==Qt::LeftButton) {
		QBrush rectbr(yellow);
		rectbr.setStyle(Dense6Pattern);
		ccursor.setColor(QColor(0xc0,0,0));
		ccursor.setStyle(Qt::SolidLine);
		finestra.setPen(ccursor);
		finestra.setBrush(rectbr);
// 		micepos->hide();
		
		QPoint p=last;
		QPoint p1=press;
		finestra.drawRect(QRect(p1,p));
		
		/*QPoint p=toViewport(last)+viewport.topLeft(); //REAL mode
		QPoint p1=toViewport(press)+viewport.topLeft();
		p=toWidget((double)p.x(), (double)p.y(), NULL);
		p1=toWidget((double)p1.x(), (double)p1.y(), NULL);
		finestra.drawRect(QRect(p1,p));*/
	} //else micepos->hide();
// 	qDebug("<%d>", pushed);
	finestra.end();
	
	///////////////////////////////
	//bitBlt(this,0,0,&buffer,0,0,this->width(),this->height());
	bitBlt(this,0,0,&front,0,0,this->width(),this->height());
}