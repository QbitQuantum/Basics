void B9Projector::mouseMoveEvent ( QMouseEvent * pEvent )
{
	setCursor(Qt::CrossCursor);
	QTimer::singleShot(500, this, SLOT(hideCursor()));
	QWidget::mouseMoveEvent(pEvent);
}