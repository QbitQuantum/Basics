void LuminanceRangeWidget::paintEvent( QPaintEvent *pe )
{
  {  
  QPainter p( this );

  QRect fRect = getPaintRect();

  if( fRect.width() < 50 )      // Does not make sense to paint anything
    return;

  // Paint range window
  {
    int x1, x2;
    x1 = getWindowX( draggedMin() );
    x2 = getWindowX( draggedMax() );
    QColor selectionColor = mouseDragStart == DRAGNOTSTARTED ?
      QColor( 0, 100, 255 ) : QColor( 0, 150, 255 );
    p.fillRect( x1, fRect.top(), x2-x1, fRect.height(), QBrush( selectionColor ) );
  }

  // Paint histogram
  if( histogramImage != NULL ) {
    if( histogram == NULL || histogram->getBins() != fRect.width() ) {
      delete histogram;
      // Build histogram from at least 5000 pixels
      int accuracy = histogramImage->getRows()*histogramImage->getCols()/5000;
      if( accuracy < 1 ) accuracy = 1;
      histogram = new Histogram( fRect.width(), accuracy );
      histogram->computeLog( histogramImage, minValue, maxValue );
    }
    
    float maxP = histogram->getMaxP();
    int i = 0;
    p.setPen( Qt::green );
    for( int x = fRect.left(); i < histogram->getBins(); x++, i++ ) {
      if( histogram->getP(i) > 0 ) {
        int barSize = (int)((float)fRect.height() * histogram->getP(i)/maxP);
        p.drawLine( x, fRect.bottom(), x, fRect.bottom() - barSize );
      }
      
    }
    
  }

  // Paint scale
  QFont labelFont( "SansSerif", 8 );
  p.setFont( labelFont );
  p.setPen( Qt::black );
  QRect textBounding = p.boundingRect( fRect, Qt::AlignHCenter|Qt::AlignBottom, "-8" );
  for( float x = ceil( minValue ); x <= floor( maxValue ); x++ ) {
    int rx = getWindowX(x);
    p.drawLine( rx, fRect.top(), rx, textBounding.top() );
    char str[10];
    sprintf( str, "%g", x );
    p.drawText( rx-20, textBounding.top(), 40, textBounding.height(),
      Qt::AlignHCenter|Qt::AlignBottom, str );
  }


  // Paint value pointer
  if( showVP )
  {
    int x = getWindowX( valuePointer );
    if( fRect.contains( x, fRect.y() ) ) {
      p.setPen( Qt::yellow );
      p.drawLine( x, fRect.top(), x, fRect.bottom() );
    }
    
  }
  
}
  QFrame::paintEvent(pe);  
}