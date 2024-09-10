bool PageTabBar::sceneEvent(QEvent* event)
{
	if (event->type() == QEvent::GestureOverride) {
		QGestureEvent* ge = static_cast<QGestureEvent*>(event);
		ge->accept();
		return true;
	}
	else if (event->type() == QEvent::Gesture) {
		QGestureEvent* ge = static_cast<QGestureEvent*>(event);
		QGesture * g = 0;
//		QGesture* g = ge->gesture(Qt::TapGesture);
//		if (g) {
//			QTapGesture* tap = static_cast<QTapGesture*>(g);
//			if (tap->state() == Qt::GestureFinished) {
//				tapGestureEvent(tap);
//			}
//			return true;
//		}
//		g = ge->gesture(Qt::TapAndHoldGesture);
//		if (g) {
//			QTapAndHoldGesture* hold = static_cast<QTapAndHoldGesture*>(g);
//			if (hold->state() == Qt::GestureFinished) {
//				tapAndHoldGestureEvent(hold);
//			}
//			return true;
//		}
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
		g = ge->gesture((Qt::GestureType) SysMgrGestureFlick);
#else
        g = ge->gesture(FlickGesture::gestureType());
#endif
		if (g) {
			FlickGesture* flick = static_cast<FlickGesture*>(g);
			if (flick->state() == Qt::GestureFinished) {
				flickGesture(flick);
			}
			return true;
		}
	}
	return QGraphicsObject::sceneEvent(event);
}