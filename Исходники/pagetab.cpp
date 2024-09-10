bool PageTab::sceneEvent(QEvent* event)
{
	if (event->type() == QEvent::GestureOverride) {
		QGestureEvent* ge = static_cast<QGestureEvent*>(event);
		ge->accept();
		return true;
	}
	else if (event->type() == QEvent::Gesture) {
		QGestureEvent* ge = static_cast<QGestureEvent*>(event);
		QGesture* g = ge->gesture(Qt::TapGesture);
		if (g) {
			QTapGesture* tap = static_cast<QTapGesture*>(g);
			if (tap->state() == Qt::GestureFinished) {
				tapGesture(tap,ge);
			}
			return true;
		}
		g = ge->gesture(Qt::TapAndHoldGesture);
		if (g) {
			QTapAndHoldGesture* hold = static_cast<QTapAndHoldGesture*>(g);
			if (hold->state() == Qt::GestureFinished) {
				tapAndHoldGesture(hold,ge);
			}
			return true;
		}
//		g = ge->gesture((Qt::GestureType) SysMgrGestureFlick);
//		if (g) {
//			FlickGesture* flick = static_cast<FlickGesture*>(g);
//			if (flick->state() == Qt::GestureFinished) {
//				flickGesture(flick,ge);
//			}
//			return true;
//		}
	}
	return QGraphicsObject::sceneEvent(event);
}