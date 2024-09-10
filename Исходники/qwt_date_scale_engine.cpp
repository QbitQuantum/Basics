/*!
   \brief Calculate a scale division for a date/time interval

   \param x1 First interval limit
   \param x2 Second interval limit
   \param maxMajorSteps Maximum for the number of major steps
   \param maxMinorSteps Maximum number of minor steps
   \param stepSize Step size. If stepSize == 0, the scaleEngine
                   calculates one.
   \return Calculated scale division
*/
QwtScaleDiv QwtDateScaleEngine::divideScale( double x1, double x2,
    int maxMajorSteps, int maxMinorSteps, double stepSize ) const
{
    if ( maxMajorSteps < 1 )
        maxMajorSteps = 1;

    const double min = qMin( x1, x2 );
    const double max = qMax( x1, x2 );

    const QDateTime from = toDateTime( min );
    const QDateTime to = toDateTime( max );

    if ( from == to )
        return QwtScaleDiv();

    stepSize = qAbs( stepSize );
    if ( stepSize > 0.0 )
    {
        // as interval types above hours are not equidistant
        // ( even days might have 23/25 hours because of daylight saving )
        // the stepSize is used as a hint only

        maxMajorSteps = qCeil( ( max - min ) / stepSize );
    }

    const QwtDate::IntervalType intvType = 
        intervalType( from, to, maxMajorSteps );

    QwtScaleDiv scaleDiv;

    if ( intvType == QwtDate::Millisecond )
    {
        // for milliseconds and below we can use the decimal system
        scaleDiv = QwtLinearScaleEngine::divideScale( min, max,
            maxMajorSteps, maxMinorSteps, stepSize );
    }
    else
    {
        const QDateTime minDate = QwtDate::floor( from, intvType );
        const QDateTime maxDate = QwtDate::ceil( to, intvType );

        scaleDiv = buildScaleDiv( minDate, maxDate, 
            maxMajorSteps, maxMinorSteps, intvType );

        // scaleDiv has been calculated from an extended interval
        // adjusted to the step size. We have to shrink it again.

        scaleDiv = scaleDiv.bounded( min, max );
    }

    if ( x1 > x2 )
        scaleDiv.invert();

    return scaleDiv;
}