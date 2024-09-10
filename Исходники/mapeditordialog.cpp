void MapEditorWidget::paintPoints()
{
  QPolygonF sPoints = transform.map(points);
  QPainter p;
  p.begin(this);
  
  p.setRenderHint(QPainter::Antialiasing);

  p.setPen(QColor("#000000"));
  p.setBrush(QBrush());
  //  p.drawRect(plotArea);
  
  p.setPen(connectionPen);
  if(sPoints.size()){
    QPainterPath path;
    path.moveTo(QPointF(plotArea.topLeft().x(),sPoints.at(0).y()));
    path.lineTo(QPointF(sPoints.at(0)));
      //    path.moveTo(sPoints.at(0));
    for (int i=1; i<sPoints.size(); ++i) {
      QPointF p1 = sPoints.at(i-1);
      QPointF p2 = sPoints.at(i);
      double distance = p2.x() - p1.x();
      
      path.cubicTo(p1.x() + distance / 2, p1.y(),
		   p1.x() + distance / 2, p2.y(),
		   p2.x(), p2.y());
    }
    path.lineTo(plotArea.bottomRight().x(),sPoints.last().y());
    p.drawPath(path);    
    path.lineTo(plotArea.bottomRight());
    path.lineTo(plotArea.topLeft().x(),plotArea.bottomRight().y());
    QLinearGradient grad = QLinearGradient(0,0,0,plotArea.height());
    grad.setColorAt(0,QColor("#B2DFEE"));
    grad.setColorAt(1,QColor("#26466D"));
    QBrush grad_brush(grad);      
    p.fillPath(path,grad_brush);
  }
  p.setPen(pointPen);
  p.setBrush(pointBrush);
  for (int i=0; i<sPoints.size(); ++i) {
    QRectF bounds = pointBoundingRect(i);
    p.drawEllipse(bounds);
  }



}