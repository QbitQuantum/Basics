bool DashboardWindowContainer::sceneEvent(QEvent* event)
{
	if (event->type() == QEvent::GestureOverride) {
		QGestureEvent* ge = static_cast<QGestureEvent*>(event);
		ge->accept();
		return true;
	}
	else if (event->type() == QEvent::Gesture) {
		QGesture* g = static_cast<QGestureEvent*>(event)->gesture(Qt::TapGesture);
		if (g) {
			QTapGesture* tap = static_cast<QTapGesture*>(g);
			if (tap->state() == Qt::GestureFinished) {
				handleTap(mapFromScene(tap->position()));
			}
			
			return true;
		}

		if(!m_isMenu) {
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
			g = static_cast<QGestureEvent*>(event)->gesture((Qt::GestureType) SysMgrGestureFlick);
#else
            g = static_cast<QGestureEvent*>(event)->gesture(FlickGesture::gestureType());
#endif
			if (g) {
				FlickGesture* flick = static_cast<FlickGesture*>(g);
				if (flick->state() == Qt::GestureFinished) {
					bool flick_delete = abs(flick->velocity().x()) > abs(flick->velocity().y());

					if (flick_delete) {
						if (DashboardWindow* w = m_draggedWindow.data()) {
							m_draggedWindow.clear();
							if (!w->persistent()) {
								m_seenFlick = true;
								triggerItemDelete(w);
							}
						}
					}
				}
				return true;
			}
		}
	} else if (event->type() == QEvent::TouchBegin) {
		return true;
	} else if (event->type() == QEvent::TouchUpdate) {
		return true;
	} else if (event->type() == QEvent::TouchEnd){
		return true;
	}

	return QGraphicsObject::sceneEvent(event);        
}