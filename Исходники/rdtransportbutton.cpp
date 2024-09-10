void RDTransportButton::drawOffCap()
{
  QPainter p;
  QPointArray triangle=QPointArray(3);
  int edge;

  if(height()<width()) {
    edge=height();
  }
  else {
    edge=width();
  }
  drawMask(off_cap);
  p.begin(off_cap);
  p.setPen(QColor(black));
  p.setBrush(QColor(black));
  switch(button_type) {
      case RDTransportButton::Play:
	triangle.setPoint(0,width()/2-(3*edge)/10,height()/2-(3*edge)/10);
	triangle.setPoint(1,width()/2+(3*edge)/10,height()/2);
	triangle.setPoint(2,width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	p.drawPolygon(triangle);
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	p.lineTo(width()/2-(3*edge)/10,height()/2-(3*edge)/10);
	p.setPen(QColor(colorGroup().dark()));
	p.lineTo(width()/2+(3*edge)/10,height()/2);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	break;
      case RDTransportButton::Stop:
	p.fillRect(width()/2-edge*3/10,height()/2-edge*3/10,
		   edge*3/5,edge*3/5,QColor(colorGroup().shadow()));
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2-edge*3/10,height()/2+edge*3/10);
	p.lineTo(width()/2-edge*3/10,height()/2-edge*3/10);
	p.lineTo(width()/2+edge*3/10,height()/2-edge*3/10);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2+edge*3/10,height()/2+edge*3/10);
	p.lineTo(width()/2-edge*3/10,height()/2+edge*3/10);
	break;
      case RDTransportButton::Record:
	p.setPen(QColor(darkRed));
	p.setBrush(QColor(darkRed));
	p.drawEllipse(width()/2-(3*edge)/10,height()/2-(3*edge)/10,
		      (3*edge)/5,(3*edge)/5);
	break;
      case RDTransportButton::FastForward:
	triangle.setPoint(0,width()/2-(3*edge)/10,height()/2-(3*edge)/10);
	triangle.setPoint(1,width()/2,height()/2);
	triangle.setPoint(2,width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	p.drawPolygon(triangle);
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	p.lineTo(width()/2-(3*edge)/10,height()/2-(3*edge)/10);
	p.setPen(QColor(colorGroup().dark()));
	p.lineTo(width()/2,height()/2);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	triangle.setPoint(0,width()/2,height()/2-(3*edge)/10);
	triangle.setPoint(1,width()/2+(3*edge)/10,height()/2);
	triangle.setPoint(2,width()/2,height()/2+(3*edge)/10);
	p.drawPolygon(triangle);
	p.drawPolygon(triangle);
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2,height()/2+(3*edge)/10);
	p.lineTo(width()/2,height()/2-(3*edge)/10);
	p.setPen(QColor(colorGroup().dark()));
	p.lineTo(width()/2+(3*edge)/10,height()/2);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2,height()/2+(3*edge)/10);
	break;
      case RDTransportButton::Rewind:
	triangle.setPoint(0,width()/2+(3*edge)/10,height()/2-(3*edge)/10);
	triangle.setPoint(1,width()/2,height()/2);
	triangle.setPoint(2,width()/2+(3*edge)/10,height()/2+(3*edge)/10);
	p.drawPolygon(triangle);
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2+(3*edge)/10,height()/2-(3*edge)/10);
	p.lineTo(width()/2,height()/2);
	p.setPen(QColor(colorGroup().dark()));
	p.lineTo(width()/2+(3*edge)/10,height()/2+(3*edge)/10);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2+(3*edge)/10,height()/2-(3*edge)/10);
	triangle.setPoint(0,width()/2,height()/2-(3*edge)/10);
	triangle.setPoint(1,width()/2-(3*edge)/10,height()/2);
	triangle.setPoint(2,width()/2,height()/2+(3*edge)/10);
	p.drawPolygon(triangle);
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2,height()/2-(3*edge)/10);
	p.lineTo(width()/2-(3*edge)/10,height()/2);
	p.setPen(QColor(colorGroup().dark()));
	p.lineTo(width()/2,height()/2+(3*edge)/10);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2,height()/2-(3*edge)/10);
	break;
      case RDTransportButton::Eject:
	triangle.setPoint(0,width()/2,height()/2-(3*edge)/10);
	triangle.setPoint(1,width()/2+(3*edge)/10,height()/2);
	triangle.setPoint(2,width()/2-(3*edge)/10,height()/2);
	p.drawPolygon(triangle);
	p.fillRect(width()/2-(3*edge)/10,height()/2+edge/10,
		   (3*edge)/5,edge/5,QColor(black));		   
	break;
      case RDTransportButton::Pause:
	p.fillRect(width()/2-(3*edge)/10,height()/2-(3*edge)/10,
		   (3*edge)/15,(3*edge)/5,QColor(black));
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	p.lineTo(width()/2-(3*edge)/10,height()/2-(3*edge)/10);
	p.lineTo(width()/2-(3*edge)/10+(3*edge)/15,height()/2-(3*edge)/10);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2-(3*edge)/10+(3*edge)/15,height()/2+(3*edge)/10);
	p.lineTo(width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	p.fillRect(width()/2+(3*edge)/30,height()/2-(3*edge)/10,
		   (3*edge)/15,(3*edge)/5,QColor(black));
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2+(3*edge)/30,height()/2+(3*edge)/10);
	p.lineTo(width()/2+(3*edge)/30,height()/2-(3*edge)/10);
	p.lineTo(width()/2+(3*edge)/10,height()/2-(3*edge)/10);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2+(3*edge)/10,height()/2+(3*edge)/10);
	p.lineTo(width()/2+(3*edge)/30,height()/2+(3*edge)/10);
	break;
      case RDTransportButton::PlayFrom:
	p.fillRect(width()/2-(3*edge)/10,height()/2-(3*edge)/10,
		   3,(3*edge)/5,QBrush(accent_color));
	triangle.setPoint(0,width()/2-(2*edge)/10+1,height()/2-(3*edge)/10);
	triangle.setPoint(1,width()/2+(3*edge)/10+1,height()/2);
	triangle.setPoint(2,width()/2-(2*edge)/10+1,height()/2+(3*edge)/10);
	p.drawPolygon(triangle);
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2-(2*edge)/10+1,height()/2+(3*edge)/10);
	p.lineTo(width()/2-(2*edge)/10+1,height()/2-(3*edge)/10);
	p.setPen(QColor(colorGroup().dark()));
	p.lineTo(width()/2+(3*edge)/10+1,height()/2);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2-(2*edge)/10+1,height()/2+(3*edge)/10);
	break;
      case RDTransportButton::PlayBetween:
	p.fillRect(width()/2-(3*edge)/10,height()/2-(3*edge)/10,
		   3,(3*edge)/5,QBrush(accent_color));
	p.fillRect(width()/2+(3*edge)/10,height()/2-(3*edge)/10,
		   3,(3*edge)/5,QBrush(accent_color));
	triangle.setPoint(0,width()/2-(2*edge)/10+1,height()/2-(3*edge)/10);
	triangle.setPoint(1,width()/2+(2*edge)/10+1,height()/2);
	triangle.setPoint(2,width()/2-(2*edge)/10+1,height()/2+(3*edge)/10);
	p.drawPolygon(triangle);
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2-(2*edge)/10+1,height()/2+(3*edge)/10);
	p.lineTo(width()/2-(2*edge)/10+1,height()/2-(3*edge)/10);
	p.setPen(QColor(colorGroup().dark()));
	p.lineTo(width()/2+(2*edge)/10+1,height()/2);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2-(2*edge)/10+1,height()/2+(3*edge)/10);
	break;
      case RDTransportButton::Loop:
	triangle.setPoint(0,width()/2-(2*edge)/10+1,height()/2-(edge)/4);
	triangle.setPoint(1,width()/2+(edge)/10+1,height()/2-edge/10);
	triangle.setPoint(2,width()/2-(2*edge)/10+1,height()/2+edge/20);
	p.drawPolygon(triangle);
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2-(2*edge)/10+1,height()/2+(edge)/4);
	p.lineTo(width()/2+(edge)/10+1,height()/2-edge/10);
	p.setPen(QColor(colorGroup().dark()));
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2-(2*edge)/10+1,height()/2+(edge)/4);
	p.setPen(QColor(colorGroup().shadow()));
	p.drawArc(width()/6,height()/2-edge/9,2*width()/3,
		  height()/3+edge/10,1440,5760);
	break;
      case RDTransportButton::Up:
	triangle.setPoint(0,width()/2,(3*edge)/10);
	triangle.setPoint(1,width()/2+(3*edge)/10,height()-(3*edge)/10);
	triangle.setPoint(2,width()/2-(3*edge)/10,height()-(3*edge)/10);
	p.drawPolygon(triangle);
	break;
      case RDTransportButton::Down:
	triangle.setPoint(0,width()/2,height()-(3*edge)/10);
	triangle.setPoint(1,width()/2+(3*edge)/10,(3*edge)/10);
	triangle.setPoint(2,width()/2-(3*edge)/10,(3*edge)/10);
	p.drawPolygon(triangle);
	break;
      case RDTransportButton::PlayTo:
	p.fillRect(width()/2+(3*edge)/10,height()/2-(3*edge)/10,
		   3,(3*edge)/5,QBrush(accent_color));
	triangle.setPoint(0,width()/2-(3*edge)/10,height()/2-(3*edge)/10);
	triangle.setPoint(1,width()/2+(2*edge)/10+1,height()/2);
	triangle.setPoint(2,width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	p.drawPolygon(triangle);
	p.setPen(QColor(colorGroup().shadow()));
	p.moveTo(width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	p.lineTo(width()/2-(3*edge)/10,height()/2-(3*edge)/10);
	p.setPen(QColor(colorGroup().dark()));
	p.lineTo(width()/2+(2*edge)/10+1,height()/2);
	p.setPen(QColor(colorGroup().light()));
	p.lineTo(width()/2-(3*edge)/10,height()/2+(3*edge)/10);
	break;
  }  
  p.end();
}