void AdvancedWidget<BaseClass>::mouseMoveEvent(QMouseEvent *event)
{
	if(!isUseBorder()) {
		bool isLeftButton = (event->buttons() & Qt::LeftButton);
		const QPoint pg = event->globalPos();
		QWidget *window = BaseClass::window();

		if(!isLeftButton) {
			Qt::WindowFrameSection region = getMouseRegion(pg.x(), pg.y(), window->geometry());

			updateCursor(region, window);
		}
		else if (isLeftButton && _action == WinAction::Resizing) {
			doWindowResize(window, pg, _region);
		}
		else if(isLeftButton && _action == WinAction::Dragging && !window->isMaximized()) {
			window->setCursor(QCursor(Qt::SizeAllCursor));
			window->move(pg - _movePath);
		}
	}

	BaseClass::mouseMoveEvent(event);
}