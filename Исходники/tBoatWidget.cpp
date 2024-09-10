//-----------------------------------------------------------------------------
//! 
//-----------------------------------------------------------------------------
void tBoatWidget::DrawThrustArrow( QPainter& painter, int value, int yPos )
{
    painter.save();
    painter.translate( QPointF(width()/2, yPos+0.5) );

    int minValue = 10;
    int headLength = 24;
    int valuePix = value/2;
    if( valuePix < 0 )
        valuePix = -valuePix;
   
    int s = (value > 0) ? 1 : -1;
    QColor arrowColor = (value > 0) ? QColor(0,188,0) : Qt::red;

    QColor grad1Color = QColor(7,131,255,255);
    QColor grad2Color = QColor(7,131,255,0);

    if( tSystemSettings::Instance()->NightMode() )
    {
        arrowColor = arrowColor.darker();
        grad1Color = grad1Color.darker();
    }

    // Draw arrow
    QPainterPath path;
    path.moveTo( 0, -10 );
    path.lineTo( s*(minValue + valuePix), -10);
    path.lineTo( s*(minValue + valuePix), -15 );
    path.lineTo( s*(minValue + valuePix + headLength), 0 );
    path.lineTo( s*(minValue + valuePix), 15 );
    path.lineTo( s*(minValue + valuePix), 10 );
    path.lineTo( 0, 10 );
    painter.fillPath( path, arrowColor );

    // Draw vacuum
    QGradient grad = QLinearGradient( QPointF(0,0), QPointF(-s*40,0) );
    grad.setColorAt(0.0, grad1Color );
    grad.setColorAt(1.0, grad2Color );
    QPainterPath p2;
    p2.moveTo( 0, -12 );
    p2.lineTo( -s*40, -21 );
    p2.lineTo( -s*40, 21 );
    p2.lineTo( 0, 12 );
    painter.fillPath( p2, grad );

    painter.restore();
}