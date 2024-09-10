QPainterPath ZigZagWipeStrategy::clipPath(int step, const QRect &area)
{
    const int zigZagCount = 10;
    const qreal zigZagHeight = area.height() / static_cast<qreal>(zigZagCount);
    const qreal zigZagWidth = area.width() / static_cast<qreal>(zigZagCount);

    qreal percent = static_cast<qreal>(step) / static_cast<qreal>(StepCount);
    if(reverse())
        percent = static_cast<qreal>(StepCount-step) / static_cast<qreal>(StepCount);

    int stepx = static_cast<int>((area.width() + 2*zigZagWidth) * percent);
    int stepy = static_cast<int>((area.height() + 2*zigZagHeight) * percent);

    qreal zigZagHeight_2 = 0.5 * zigZagHeight;
    qreal zigZagWidth_2 = 0.5 * zigZagWidth;

    QPainterPath path;
    switch(subType())
    {
    case ZigZagWipeEffectFactory::FromTop:
    case ZigZagWipeEffectFactory::FromBottom:
    {
        qreal zigZagBase = stepy - zigZagHeight;
        qreal zigZagTip = stepy;
        path.moveTo(area.topLeft() - QPointF(0, zigZagHeight));
        path.lineTo(QPointF(area.left(), zigZagBase));
        for(int i = 0; i < zigZagCount; ++i)
        {
            path.lineTo(area.topLeft() + QPointF((2*i+1) * zigZagWidth_2, zigZagTip));
            path.lineTo(area.topLeft() + QPointF((i+1) * zigZagWidth, zigZagBase));
        }
        path.lineTo(area.topRight() - QPointF(0, zigZagHeight));
        break;
    }
    case ZigZagWipeEffectFactory::FromLeft:
    case ZigZagWipeEffectFactory::FromRight:
    {
        qreal zigZagBase = stepx - zigZagWidth;
        qreal zigZagTip = stepx;
        path.moveTo(area.topLeft() - QPointF(zigZagWidth, 0));
        path.lineTo(QPointF(zigZagBase, area.top()));
        for(int i = 0; i < zigZagCount; ++i)
        {
            path.lineTo(area.topLeft() + QPointF(zigZagTip, (2*i+1) * zigZagHeight_2));
            path.lineTo(area.topLeft() + QPointF(zigZagBase, (i+1) * zigZagHeight));
        }
        path.lineTo(area.bottomLeft() - QPointF(zigZagWidth, 0));
        break;
    }
    default:
        return QPainterPath();
    }

    path.closeSubpath();

    if(reverse())
    {
        QPainterPath areaPath;
        areaPath.addRect(area);
        path = areaPath.subtracted(path);
    }

    return path;
}