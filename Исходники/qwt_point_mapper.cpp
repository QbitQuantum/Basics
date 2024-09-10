static inline Polygon qwtToPoints( 
    const QRectF &boundingRect,
    const QwtScaleMap &xMap, const QwtScaleMap &yMap,
    const QwtSeriesData<QPointF> *series, 
    int from, int to, Round round )
{
    Polygon polyline( to - from + 1 );
    Point *points = polyline.data();

    int numPoints = 0;

    if ( boundingRect.isValid() )
    {
        // iterating over all values
        // filtering out all points outside of
        // the bounding rectangle

        for ( int i = from; i <= to; i++ )
        {
            const QPointF sample = series->sample( i );

            const double x = xMap.transform( sample.x() );
            const double y = yMap.transform( sample.y() );

            if ( boundingRect.contains( x, y ) )
            {
                points[ numPoints ].rx() = round( x );
                points[ numPoints ].ry() = round( y );

                numPoints++;
            }
        }

        polyline.resize( numPoints );
    }
    else
    {
        // simply iterating over all values
        // without any filtering

        for ( int i = from; i <= to; i++ )
        {
            const QPointF sample = series->sample( i );

            const double x = xMap.transform( sample.x() );
            const double y = yMap.transform( sample.y() );

            points[ numPoints ].rx() = round( x );
            points[ numPoints ].ry() = round( y );

            numPoints++;
        }
    }

    return polyline;
}