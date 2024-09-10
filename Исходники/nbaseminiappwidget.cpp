void NBaseMiniAppWidget::enterEvent(QEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    NBaseMoveableWidget::enterEvent(event);
}