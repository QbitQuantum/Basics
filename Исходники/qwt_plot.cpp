//! Rebuild the scales and maps
void QwtPlot::updateAxes()
{
    int i;
    bool resetDone[axisCnt];
    for (i = 0; i < axisCnt; i++)
        resetDone[i] = FALSE;

    //
    //  Adjust autoscalers
    //

    QwtPlotCurveIterator itc = curveIterator();
    for (const QwtPlotCurve *c = itc.toFirst(); c != 0; c = ++itc )
    {
        const int xAxis = c->xAxis();
        const int yAxis = c->yAxis();

        if ( d_as[xAxis].autoScale() || d_as[yAxis].autoScale() )
        {
            const QwtDoubleRect rect = c->boundingRect();
            if ( rect.isValid() )
            {
                if ( d_as[xAxis].autoScale() )
                {
                    if ( !resetDone[xAxis] )
                    {
                        d_as[xAxis].reset();
                        resetDone[xAxis] = TRUE;
                    }
                    d_as[xAxis].adjust(rect.x1(), rect.x2());
                }

                if ( d_as[yAxis].autoScale() )
                {
                    if ( !resetDone[yAxis] )
                    {
                        d_as[yAxis].reset();
                        resetDone[yAxis] = TRUE;
                    }
                    d_as[yAxis].adjust(rect.y1(), rect.y2());
                }
            }
        }
    }

    //
    // Adjust scales
    //
    for (i = 0; i < axisCnt; i++)
    {
        d_scale[i]->setScaleDiv(d_as[i].scaleDiv());

        int startDist, endDist;
        d_scale[i]->minBorderDist(startDist, endDist);
        d_scale[i]->setBorderDist(startDist, endDist);
    }

    d_grid->setXDiv(d_as[d_grid->xAxis()].scaleDiv());
    d_grid->setYDiv(d_as[d_grid->yAxis()].scaleDiv());
}