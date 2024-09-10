/*!
  \brief Complete a polygon to be a closed polygon including the 
         area between the original polygon and the baseline.

  \param painter Painter
  \param xMap X map
  \param yMap Y map
  \param polygon Polygon to be completed
*/
void QwtPlotCurve::closePolyline( QPainter *painter,
    const QwtScaleMap &xMap, const QwtScaleMap &yMap,
    QPolygonF &polygon ) const
{
    if ( polygon.size() < 2 )
        return;

    const bool doAlign = QwtPainter::roundingAlignment( painter );

    double baseline = d_data->baseline;
    
    if ( orientation() == Qt::Vertical )
    {
        if ( yMap.transformation()->type() == QwtScaleTransformation::Log10 )
        {
            if ( baseline < QwtScaleMap::LogMin )
                baseline = QwtScaleMap::LogMin;
        }

        double refY = yMap.transform( baseline );
        if ( doAlign )
            refY = qRound( refY );

        polygon += QPointF( polygon.last().x(), refY );
        polygon += QPointF( polygon.first().x(), refY );
    }
    else
    {
        if ( xMap.transformation()->type() == QwtScaleTransformation::Log10 )
        {
            if ( baseline < QwtScaleMap::LogMin )
                baseline = QwtScaleMap::LogMin;
        }

        double refX = xMap.transform( baseline );
        if ( doAlign )
            refX = qRound( refX );

        polygon += QPointF( refX, polygon.last().y() );
        polygon += QPointF( refX, polygon.first().y() );
    }
}