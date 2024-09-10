//virtual
bool PixButton::sceneEvent(QEvent * event)
{
	if (event->type() == QEvent::GestureOverride) {
		QGestureEvent* ge = static_cast<QGestureEvent*>(event);
		ge->accept();
		return true;
	}
	else if (event->type() == QEvent::Gesture) {
		QGestureEvent* ge = static_cast<QGestureEvent*>(event);
		QGesture * g = 0;
		g = ge->gesture(Qt::TapGesture);
		if (g) {
			QTapGesture* tap = static_cast<QTapGesture*>(g);
			if (tap->state() == Qt::GestureFinished) {
				tapGesture(tap);
			}
			return true;
		}
		g = ge->gesture(Qt::TapAndHoldGesture);
		if (g) {
			QTapAndHoldGesture* hold = static_cast<QTapAndHoldGesture*>(g);
			if (hold->state() == Qt::GestureFinished) {
				tapAndHoldGesture(hold);
			}
			return true;
		}
	}
	else if (event->type() == QEvent::TouchBegin)
	{
		return touchStartEvent(static_cast<QTouchEvent *>(event));
	}
	else if (event->type() == QEvent::TouchUpdate)
	{
		return touchUpdateEvent(static_cast<QTouchEvent *>(event));
	}
	else if (event->type() == QEvent::TouchEnd)
	{
		return touchEndEvent(static_cast<QTouchEvent *>(event));
	}
	return QGraphicsObject::sceneEvent(event);
}