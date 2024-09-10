void PieChart3D::paintLeft( QPainter& painter, QColor color ) {
  if ( myRender == WireFrame ) {
    return;
  }
  painter.save();
  color.setAlpha( 125 );
  configureColor( painter, color, 0 );
  int width = painter.pen().width()/2;
  painter.setPen( Qt::NoPen );
  QPainterPath path;
  QPainterPath ellipse1, ellipse2;
  ellipse1.addEllipse( myRect );
  ellipse2.addEllipse( myRect.translated( 0, myHeight ) );
  path.moveTo( ellipse1.pointAtPercent( 0.5 ) + QPointF( -width, 0 ) );
  path.lineTo( ellipse2.pointAtPercent( 0.5 ) + QPointF( -width, 0 ) );
  path.arcTo( myRect.translated( 0, myHeight ), 180, -90 );
  path.moveTo( ellipse1.pointAtPercent( 0.5 ) );
  path.arcTo( myRect, 180, 90 );
  path = path.subtracted( ellipse1 );
  painter.fillPath( path, color );
  painter.restore();
}