QGestureRecognizer::Result
QTapAndHoldGestureRecognizer::recognize(QGesture *state, QObject *object,
                                        QEvent *event)
{
#ifndef QT_WEBOS
    QTapAndHoldGesture *q = static_cast<QTapAndHoldGesture *>(state);
    QTapAndHoldGesturePrivate *d = q->d_func();

    if (object == state && event->type() == QEvent::Timer) {
        q->killTimer(d->timerId);
        d->timerId = 0;
        return QGestureRecognizer::FinishGesture | QGestureRecognizer::ConsumeEventHint;
    }

    const QTouchEvent *ev = static_cast<const QTouchEvent *>(event);
    const QMouseEvent *me = static_cast<const QMouseEvent *>(event);
#ifndef QT_NO_GRAPHICSVIEW
    const QGraphicsSceneMouseEvent *gsme = static_cast<const QGraphicsSceneMouseEvent *>(event);
#endif

    enum { TapRadius = 40 };

    switch (event->type()) {
#ifndef QT_NO_GRAPHICSVIEW
    case QEvent::GraphicsSceneMousePress:
        d->position = gsme->screenPos();
        q->setHotSpot(d->position);
        if (d->timerId)
            q->killTimer(d->timerId);
        d->timerId = q->startTimer(QTapAndHoldGesturePrivate::Timeout);
        return QGestureRecognizer::MayBeGesture; // we don't show a sign of life until the timeout
#endif
    case QEvent::MouseButtonPress:
        d->position = me->globalPos();
        q->setHotSpot(d->position);
        if (d->timerId)
            q->killTimer(d->timerId);
        d->timerId = q->startTimer(QTapAndHoldGesturePrivate::Timeout);
        return QGestureRecognizer::MayBeGesture; // we don't show a sign of life until the timeout
    case QEvent::TouchBegin:
        d->position = ev->touchPoints().at(0).startScreenPos();
        q->setHotSpot(d->position);
        if (d->timerId)
            q->killTimer(d->timerId);
        d->timerId = q->startTimer(QTapAndHoldGesturePrivate::Timeout);
        return QGestureRecognizer::MayBeGesture; // we don't show a sign of life until the timeout
#ifndef QT_NO_GRAPHICSVIEW
    case QEvent::GraphicsSceneMouseRelease:
#endif
    case QEvent::MouseButtonRelease:
    case QEvent::TouchEnd:
        return QGestureRecognizer::CancelGesture; // get out of the MayBeGesture state
    case QEvent::TouchUpdate:
        if (d->timerId && ev->touchPoints().size() == 1) {
            QTouchEvent::TouchPoint p = ev->touchPoints().at(0);
            QPoint delta = p.pos().toPoint() - p.startPos().toPoint();
            if (delta.manhattanLength() <= TapRadius)
                return QGestureRecognizer::MayBeGesture;
        }
        return QGestureRecognizer::CancelGesture;
    case QEvent::MouseMove: {
        QPoint delta = me->globalPos() - d->position.toPoint();
        if (d->timerId && delta.manhattanLength() <= TapRadius)
            return QGestureRecognizer::MayBeGesture;
        return QGestureRecognizer::CancelGesture;
    }
#ifndef QT_NO_GRAPHICSVIEW
    case QEvent::GraphicsSceneMouseMove: {
        QPoint delta = gsme->screenPos() - d->position.toPoint();
        if (d->timerId && delta.manhattanLength() <= TapRadius)
            return QGestureRecognizer::MayBeGesture;
        return QGestureRecognizer::CancelGesture;
    }
#endif
    default:
        return QGestureRecognizer::Ignore;
    }
#else
    QGestureRecognizer::Result result = QGestureRecognizer::CancelGesture;
    QTapAndHoldGesture *q = static_cast<QTapAndHoldGesture *>(state);
    QTapAndHoldGesturePrivate *d = q->d_func();

    if (object == state && event->type() == QEvent::Timer) {
        q->killTimer(d->timerId);
        d->timerId = 0;
        if (q->state() != Qt::NoGesture && q->state() != Qt::GestureCanceled) {
        	result = QGestureRecognizer::FinishGesture;
        }
        return result | QGestureRecognizer::ConsumeEventHint;
    }

    const QTouchEvent *ev = static_cast<const QTouchEvent *>(event);

    enum { TimerInterval = 700 };
    enum { TapRadius = 40 };

    switch (event->type()) {
    case QEvent::TouchBegin:
        d->position = ev->touchPoints().at(0).startScreenPos();
        q->setHotSpot(d->position);
        if (d->timerId)
            q->killTimer(d->timerId);
        d->timerId = q->startTimer(TimerInterval);
        return QGestureRecognizer::TriggerGesture;
    case QEvent::TouchEnd:
		result = QGestureRecognizer::CancelGesture;
		if (d->timerId)
			q->killTimer(d->timerId);
		d->timerId = 0;
        break;
    case QEvent::TouchUpdate:
        if (d->timerId && ev->touchPoints().size() == 1) {
            QTouchEvent::TouchPoint p = ev->touchPoints().at(0);
            QPoint delta = p.pos().toPoint() - p.startPos().toPoint();
            if (delta.manhattanLength() > TapRadius) {
                result = QGestureRecognizer::CancelGesture;
				if (d->timerId)
	                q->killTimer(d->timerId);
				d->timerId = 0;
            } else {
            	result = QGestureRecognizer::Ignore;
            }
        } else if (ev->touchPoints().size() > 1) {
        	result = QGestureRecognizer::CancelGesture;
			if (d->timerId)
	        	q->killTimer(d->timerId);
			d->timerId = 0;
        } else {
        	result = QGestureRecognizer::Ignore;
        }
		break;
    default:
        return QGestureRecognizer::Ignore;
    }
    return result;
#endif // QT_WEBOS
}