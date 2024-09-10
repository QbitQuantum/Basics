/*!
  Draw a subset of the points

  \param painter Painter
  \param xMap Maps x-values into pixel coordinates.
  \param yMap Maps y-values into pixel coordinates.
  \param canvasRect Contents rectangle of the canvas
  \param from Index of the first sample to be painted
  \param to Index of the last sample to be painted. If to < 0 the
         series will be painted to its last sample.

  \sa drawSeries()
*/
void CpPlotCurve::drawDots( QPainter *painter,
    const QwtScaleMap &xMap, const QwtScaleMap &yMap,
    const QRectF &canvasRect, int from, int to ) const
{
    if ( !d_data->colorRange.isValid() )
        return;

    const bool doAlign = QwtPainter::roundingAlignment( painter );

    const QwtColorMap::Format format = d_data->colorMap->format();
    if ( format == QwtColorMap::Indexed )
        d_data->colorTable = d_data->colorMap->colorTable( d_data->colorRange );

    const QwtSeriesData<QwtPoint3D> *series = data();

    for ( int i = from; i <= to; i++ )
    {
        const QwtPoint3D sample = series->sample( i );

        double xi = xMap.transform( sample.x() );
        double yi = yMap.transform( sample.y() );
        if ( doAlign )
        {
            xi = qRound( xi );
            yi = qRound( yi );
        }

        if ( d_data->paintAttributes & CpPlotCurve::ClipPoints )
        {
            if ( !canvasRect.contains( xi, yi ) )
                continue;
        }

        if ( format == QwtColorMap::RGB )
        {
            const QRgb rgb = d_data->colorMap->rgb(
                d_data->colorRange, sample.z() );

            painter->setPen( QPen( QColor::fromRgba( rgb ), d_data->penWidth ) );
        }
        else
        {
            const unsigned char index = d_data->colorMap->colorIndex(
                d_data->colorRange, sample.z() );

            painter->setPen( QPen( QColor::fromRgba( d_data->colorTable[index] ), 
                d_data->penWidth ) );
        }

        QwtPainter::drawPoint( painter, QPointF( xi, yi ) );
    }

    d_data->colorTable.clear();
}