/*!
   \brief Calculate a scale division

   \param x1 First interval limit 
   \param x2 Second interval limit 
   \param maxMajSteps Maximum for the number of major steps
   \param maxMinSteps Maximum number of minor steps
   \param stepSize Step size. If stepSize == 0, the scaleEngine
                   calculates one.

   \sa QwtScaleEngine::stepSize, LogTimeScaleEngine::subDivide
*/
QwtScaleDiv LogTimeScaleEngine::divideScale(double x1, double x2,
    int maxMajSteps, int maxMinSteps, double stepSize) const
{
    QwtDoubleInterval interval = QwtDoubleInterval(x1, x2).normalized();
    interval = interval.limited(LOG_MIN, LOG_MAX);

    if (interval.width() <= 0 )
        return QwtScaleDiv();

    if (interval.maxValue() / interval.minValue() < 10.0)
    {
        // scale width is less than one decade -> build linear scale
    
        QwtLinearScaleEngine linearScaler;
        linearScaler.setAttributes(attributes());
        linearScaler.setReference(reference());
        linearScaler.setMargins(
                                #if (QWT_VERSION >= 0x050200)
				lowerMargin(), upperMargin()
				#else
				loMargin(), hiMargin()
				#endif
				);

        return linearScaler.divideScale(x1, x2, 
            maxMajSteps, maxMinSteps, stepSize);
    }

    stepSize = qwtAbs(stepSize);
    if ( stepSize == 0.0 )
    {
        if ( maxMajSteps < 1 )
            maxMajSteps = 1;

        stepSize = divideInterval(log10(interval).width(), maxMajSteps);
        if ( stepSize < 1.0 )
            stepSize = 1.0; // major step must be >= 1 decade
    }

    QwtScaleDiv scaleDiv;
    if ( stepSize != 0.0 )
    {
        QwtValueList ticks[QwtScaleDiv::NTickTypes];
        buildTicks(interval, stepSize, maxMinSteps, ticks);

        scaleDiv = QwtScaleDiv(interval, ticks);
    }

    if ( x1 > x2 )
        scaleDiv.invert();

    return scaleDiv;
}