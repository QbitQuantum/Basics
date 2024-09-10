void AvatarEditScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    QGraphicsView *view = qobject_cast<QGraphicsView*>(event->widget()->parent());
    Q_ASSERT(view);

    view->setCursor(Qt::ArrowCursor);

    isDragged = false;
    isSizing = false;

    QGraphicsScene::mouseMoveEvent(event);
}