bool WindowSticker::eventFilter(QObject *AWatched, QEvent *AEvent)
{
	if (AEvent->type() == QEvent::NonClientAreaMouseButtonPress)
	{
		QWidget *window = qobject_cast<QWidget *>(AWatched);
		if (window && window->isWindow())
		{
			FCurWindow = window;
		}
	}
	else if (AEvent->type() == QEvent::NonClientAreaMouseButtonRelease)
	{
		FCurWindow = NULL;
	}
	else if (AEvent->type() == QEvent::NonClientAreaMouseMove)
	{
		FCurWindow = NULL;
	}
	else if (AEvent->type() == QEvent::WindowStateChange)
	{
		FCurWindow = NULL;
	}
	else if (AWatched==FCurWindow && AEvent->type()==QEvent::Move)
	{
		const int delta = 15;
		QPoint cursorPos = QCursor::pos();
		QRect windowRect = FCurWindow->frameGeometry();
		QRect desckRect = QApplication::desktop()->availableGeometry(FCurWindow);

		int borderTop = cursorPos.y() - windowRect.y();
		int borderLeft = cursorPos.x() - windowRect.x();
		int borderRight = cursorPos.x() + desckRect.right() - windowRect.right();
		int borderBottom = cursorPos.y() + desckRect.bottom() - windowRect.bottom();

		FStickPos = windowRect.topLeft();
		if (qAbs(borderTop - cursorPos.y()) < delta)
		{
			FStickPos.setY(0);
		}
		else if (qAbs(borderBottom - cursorPos.y()) < delta)
		{
			FStickPos.setY(desckRect.bottom() - windowRect.height());
		}
		if (qAbs(borderLeft - cursorPos.x()) < delta)
		{
			FStickPos.setX(0);
		}
		else if(qAbs(borderRight - cursorPos.x()) < delta)
		{
			FStickPos.setX(desckRect.right() - windowRect.width());
		}

		if (FStickPos != windowRect.topLeft())
		{
			QEvent *stickEvent = new QEvent((QEvent::Type)FStickEvent);
			QApplication::postEvent(AWatched,stickEvent,Qt::HighEventPriority);
		}
	}
	else if (FCurWindow==AWatched && AEvent->type()==FStickEvent)
	{
		FCurWindow->move(FStickPos);
		return true;
	}
	return QObject::eventFilter(AWatched,AEvent);
}