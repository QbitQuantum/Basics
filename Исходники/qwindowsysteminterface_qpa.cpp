void QWindowSystemInterface::handleTouchEvent(QWidget *tlw, ulong timestamp, QEvent::Type type, QTouchEvent::DeviceType devType, const QList<struct TouchPoint> &points)
{
    if (!points.size()) // Touch events must have at least one point
        return;

    QList<QTouchEvent::TouchPoint> touchPoints;
    Qt::TouchPointStates states;
    QTouchEvent::TouchPoint p;

    QList<struct TouchPoint>::const_iterator point = points.constBegin();
    QList<struct TouchPoint>::const_iterator end = points.constEnd();
    while (point != end) {
        p.setId(point->id);
        p.setPressure(point->pressure);
        states |= point->state;
        Qt::TouchPointStates state = point->state;
        if (point->isPrimary) {
            state |= Qt::TouchPointPrimary;
        }
        p.setState(state);
        p.setRect(point->area);
        p.setScreenPos(point->area.center());
        p.setNormalizedPos(point->normalPosition);

        touchPoints.append(p);
        ++point;
    }

    QWindowSystemInterfacePrivate::TouchEvent *e =
            new QWindowSystemInterfacePrivate::TouchEvent(tlw, timestamp, type, devType, touchPoints);
    QWindowSystemInterfacePrivate::queueWindowSystemEvent(e);
}