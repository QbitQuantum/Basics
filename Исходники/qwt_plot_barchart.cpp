/*!
  Draw a sample

  \param painter Painter
  \param xMap x map
  \param yMap y map
  \param canvasRect Contents rect of the canvas
  \param boundingInterval Bounding interval of sample values
  \param index Index of the sample
  \param sample Value of the sample

  \sa drawSeries()
*/
void QwtPlotBarChart::drawSample( QPainter *painter,
    const QwtScaleMap &xMap, const QwtScaleMap &yMap,
    const QRectF &canvasRect, const QwtInterval &boundingInterval,
    int index, const QPointF &sample ) const
{
    QwtColumnRect barRect;

    if ( orientation() == Qt::Horizontal )
    {
        const double barHeight = sampleWidth( yMap, canvasRect.height(),
            boundingInterval.width(), sample.y() );

        const double x1 = xMap.transform( baseline() );
        const double x2 = xMap.transform( sample.y() );

        const double y = yMap.transform( sample.x() );
        const double y1 = y - 0.5 * barHeight;
        const double y2 = y + 0.5 * barHeight;

        barRect.direction = ( x1 < x2 ) ?
            QwtColumnRect::LeftToRight : QwtColumnRect::RightToLeft;

        barRect.hInterval = QwtInterval( x1, x2 ).normalized();
        barRect.vInterval = QwtInterval( y1, y2 );
    }
    else
    {
        const double barWidth = sampleWidth( xMap, canvasRect.width(),
            boundingInterval.width(), sample.y() );

        const double x = xMap.transform( sample.x() );
        const double x1 = x - 0.5 * barWidth;
        const double x2 = x + 0.5 * barWidth;

        const double y1 = yMap.transform( baseline() );
        const double y2 = yMap.transform( sample.y() );

        barRect.direction = ( y1 < y2 ) ?
            QwtColumnRect::TopToBottom : QwtColumnRect::BottomToTop;

        barRect.hInterval = QwtInterval( x1, x2 );
        barRect.vInterval = QwtInterval( y1, y2 ).normalized();
    }

    drawBar( painter, index, sample, barRect );
}