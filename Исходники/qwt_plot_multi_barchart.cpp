/*!
  \return Bounding rectangle of all samples.
  For an empty series the rectangle is invalid.
*/
QRectF QwtPlotMultiBarChart::boundingRect() const
{
    const size_t numSamples = dataSize();

    if ( numSamples == 0 )
        return QwtPlotSeriesItem::boundingRect();

    const double baseLine = baseline();

    QRectF rect;

    if ( d_data->style != QwtPlotMultiBarChart::Stacked )
    {
        rect = QwtPlotSeriesItem::boundingRect();

        if ( rect.height() >= 0 )
        {
            if ( rect.bottom() < baseLine )
                rect.setBottom( baseLine );
            if ( rect.top() > baseLine )
                rect.setTop( baseLine );
        }
    }
    else
    {
        double xMin, xMax, yMin, yMax;

        xMin = xMax = 0.0;
        yMin = yMax = baseLine;

        const QwtSeriesData<QwtSetSample> *series = data();

        for ( size_t i = 0; i < numSamples; i++ )
        {
            const QwtSetSample sample = series->sample( i );
            if ( i == 0 )
            {
                xMin = xMax = sample.value;
            }
            else
            {
                xMin = qMin( xMin, sample.value );
                xMax = qMax( xMax, sample.value );
            }

            const double y = baseLine + sample.added();

            yMin = qMin( yMin, y );
            yMax = qMax( yMax, y );
        }
        rect.setRect( xMin, yMin, xMax - xMin, yMax - yMin );
    }

    if ( orientation() == Qt::Horizontal )
        rect.setRect( rect.y(), rect.x(), rect.height(), rect.width() );

    return rect;
}