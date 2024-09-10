void SunMenuItemView::updateShape()
{
    QPainterPath newPath;

    qreal tmp = qAbs(sweepLength());
    if (width() != 0 && tmp > 0.001)
    {
        qint32 innerRad = innerRadius();
        qint32 outerRadius = innerRad + width();
        QRectF r = QRect(-outerRadius, -outerRadius, outerRadius * 2,
                         outerRadius * 2);

        if (innerRad == 0 && qAbs(sweepLength() - 360) < 0.0001)
        {
            newPath.addEllipse(r);
        }
        else
        {
            newPath.arcMoveTo(r, startAngle());
            newPath.arcTo(r, startAngle(), sweepLength());

            if(innerRad == 0)
            {
                newPath.lineTo(0,0);
            }else
            {
                r = QRect(-innerRad, -innerRad, innerRad * 2, innerRad * 2);
                newPath.arcTo(r, startAngle() + sweepLength(), -sweepLength());
            }
            newPath.closeSubpath();
        }
    }
    //
    setPath(newPath);
    reinitializeDisplayedItemPosition();
}