/*!
    Wrapper for QPainter::drawRect()
*/
void QwtPainter::drawRect(QPainter *painter, const QRect &rect) 
{
    QRect r = d_metricsMap.layoutToDevice(rect, painter);

    QRect clipRect;

    const bool deviceClipping = needDeviceClipping(painter, d_deviceClipping);
    if ( deviceClipping )
        clipRect = deviceClipRect();

    if ( clipRect.isValid() )
    {
        if ( !clipRect.intersects(r) )
            return;

        if ( !clipRect.contains(r) )
        {
            fillRect(painter, r & clipRect, painter->brush());

            int pw = painter->pen().width();
            pw = pw % 2 + pw / 2;

            QwtPolygon pa(5);
            pa.setPoint(0, r.left(), r.top());
            pa.setPoint(1, r.right() - pw, r.top());
            pa.setPoint(2, r.right() - pw, r.bottom() - pw);
            pa.setPoint(3, r.left(), r.bottom() - pw);
            pa.setPoint(4, r.left(), r.top());

            painter->save();
            painter->setBrush(Qt::NoBrush);
            drawPolyline(painter, pa);
            painter->restore();

            return;
        }
    }

#if QT_VERSION >= 0x040000
    if ( painter->pen().style() != Qt::NoPen && 
        painter->pen().color().isValid() )
    {
        // Qt4 adds the pen to the rect, Qt3 not.
        int pw = painter->pen().width();
        if ( pw == 0 )
            pw = 1;

        r.setWidth(r.width() - pw);
        r.setHeight(r.height() - pw);
    }
#endif
    painter->drawRect(r);
}