/*!
   \brief Calculate a scale division for an interval

   \param x1 First interval limit
   \param x2 Second interval limit
   \param maxMajorSteps Maximum for the number of major steps
   \param maxMinorSteps Maximum number of minor steps
   \param stepSize Step size. If stepSize == 0, the engine
                   calculates one.

   \return Calculated scale division
*/
QwtScaleDiv QwtLinearScaleEngine::divideScale( double x1, double x2,
    int maxMajorSteps, int maxMinorSteps, double stepSize ) const
{
    QwtInterval interval = QwtInterval( x1, x2 ).normalized();

    if ( qwtIntervalWidthL( interval ) > std::numeric_limits<double>::max() )
    {
        qWarning() << "QwtLinearScaleEngine::divideScale: overflow";
        return QwtScaleDiv();
    }

    if ( interval.width() <= 0 )
        return QwtScaleDiv();

    stepSize = qAbs( stepSize );
    if ( stepSize == 0.0 )
    {
        if ( maxMajorSteps < 1 )
            maxMajorSteps = 1;

        stepSize = QwtScaleArithmetic::divideInterval( 
            interval.width(), maxMajorSteps, base() );
    }

    QwtScaleDiv scaleDiv;

    if ( stepSize != 0.0 )
    {
        QList<double> ticks[QwtScaleDiv::NTickTypes];
        buildTicks( interval, stepSize, maxMinorSteps, ticks );

        scaleDiv = QwtScaleDiv( interval, ticks );
    }

    if ( x1 > x2 )
        scaleDiv.invert();

    return scaleDiv;
}