void Plot::drawInwardMinorTicks(QPainter *painter, const QRect &rect,
                                const QwtDiMap &map, int axis) const
{
    QwtScale *scale=(QwtScale *) QwtPlot::axis (axis);
    if (!scale)
        return;

    int x1=rect.left();
    int x2=rect.right();
    int y1=rect.top();
    int y2=rect.bottom();

    QPalette pal=scale->palette();
    QColor color=pal.color(QPalette::Active, QColorGroup::Foreground);

    painter->save();
    painter->setPen(QPen(color, d_lineWidth, QPainter::SolidLine));

    QwtScaleDiv *scDiv=(QwtScaleDiv *)axisScale(axis);
    int minTicks=scDiv->minCnt();

    int j, x, y, low,high;
    switch (axis)
    {
    case QwtPlot::yLeft:
        x=x1;
        low=y1+majTickLength;
        high=y2-majTickLength;
        for (j = 0; j < minTicks; j++)
        {
            y = map.transform(scDiv->minMark(j));
            if (y>low && y< high)
                QwtPainter::drawLine(painter, x, y, x+minTickLength, y);
        }
        break;

    case QwtPlot::yRight:
    {
        x=x2;
        low=y1+majTickLength;
        high=y2-majTickLength;
        for (j = 0; j < minTicks; j++)
        {
            y = map.transform(scDiv->minMark(j));
            if (y>low && y< high)
                QwtPainter::drawLine(painter, x+1, y, x-minTickLength, y);
        }
    }
    break;

    case QwtPlot::xBottom:
        y=y2;
        low=x1+majTickLength;
        high=x2-majTickLength;
        for (j = 0; j < minTicks; j++)
        {
            x = map.transform(scDiv->minMark(j));
            if (x>low && x<high)
                QwtPainter::drawLine(painter, x, y+1, x, y-minTickLength);
        }
        break;

    case QwtPlot::xTop:
        y=y1;
        low=x1+majTickLength;
        high=x2-majTickLength;
        for (j = 0; j < minTicks; j++)
        {
            x = map.transform(scDiv->minMark(j));
            if (x>low && x<high)
                QwtPainter::drawLine(painter, x, y, x, y + minTickLength);
        }
        break;
    }
    painter->restore();
}