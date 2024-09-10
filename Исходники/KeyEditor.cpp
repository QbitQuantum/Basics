bool KeyEditor::event(QEvent* event) {
	if (!m_button) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() != Qt::Key_Tab && keyEvent->key() != Qt::Key_Backtab) {
				return QWidget::event(event);
			}
			if (!(keyEvent->modifiers() & ~Qt::ShiftModifier)) {
				keyPressEvent(keyEvent);
				keyEvent->accept();
				return true;
			}
		}
	} else {
		if (event->type() == GamepadButtonEvent::Down()) {
			setValueButton(static_cast<GamepadButtonEvent*>(event)->value());
			event->accept();
			return true;
		}
		if (event->type() == GamepadHatEvent::Down()) {
			GamepadHatEvent* ghe = static_cast<GamepadHatEvent*>(event);
			setValueHat(ghe->hatId(), ghe->direction());
			event->accept();
			return true;
		}
		if (event->type() == GamepadAxisEvent::Type()) {
			GamepadAxisEvent* gae = static_cast<GamepadAxisEvent*>(event);
			if (gae->isNew()) {
				setValueAxis(gae->axis(), gae->direction());
			}
			event->accept();
			return true;
		}
	}
	return QWidget::event(event);
}