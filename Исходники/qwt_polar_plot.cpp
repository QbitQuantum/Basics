/*!
   \brief Calculate the bounding rect of the plot area

   The plot area depends on the zoom parameters.

   \param canvasRect Rectangle of the canvas
   \return Rectangle for displaying 100% of the plot
*/
QRectF QwtPolarPlot::plotRect( const QRectF &canvasRect ) const
{
    const QwtScaleDiv *sd = scaleDiv( QwtPolar::Radius );
    const QwtScaleEngine *se = scaleEngine( QwtPolar::Radius );

    const int margin = plotMarginHint();
    const QRectF cr = canvasRect;
    const int radius = qMin( cr.width(), cr.height() ) / 2 - margin;

    QwtScaleMap map;
    map.setTransformation( se->transformation() );
    map.setPaintInterval( 0.0, radius / d_data->zoomFactor );
    map.setScaleInterval( sd->lowerBound(), sd->upperBound() );

    double v = map.s1();
    if ( map.s1() <= map.s2() )
        v += d_data->zoomPos.radius();
    else
        v -= d_data->zoomPos.radius();
    v = map.transform( v );

    const QPointF off =
        QwtPointPolar( d_data->zoomPos.azimuth(), v ).toPoint();

    QPointF center( cr.center().x(), cr.top() + margin + radius );
    center -= QPointF( off.x(), -off.y() );

    QRectF rect( 0, 0, 2 * map.p2(), 2 * map.p2() );
    rect.moveCenter( center );

    return rect;
}