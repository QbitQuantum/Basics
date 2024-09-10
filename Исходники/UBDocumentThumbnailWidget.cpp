void UBDocumentThumbnailWidget::dragMoveEvent(QDragMoveEvent *event)
{
	QRect boundingFrame = frameRect();
	//setting up automatic scrolling
	const int SCROLL_DISTANCE = 16;
	int bottomDist = boundingFrame.bottom() - event->pos().y(), topDist = boundingFrame.top() - event->pos().y();
	if(qAbs(bottomDist) <= SCROLL_DISTANCE)
	{
		mScrollMagnitude = (SCROLL_DISTANCE - bottomDist)*4;
		if(verticalScrollBar()->isVisible() && !mScrollTimer->isActive()) mScrollTimer->start(100);
	}
	else if(qAbs(topDist) <= SCROLL_DISTANCE)
	{
		mScrollMagnitude = (- SCROLL_DISTANCE - topDist)*4;
		if(verticalScrollBar()->isVisible() && !mScrollTimer->isActive()) mScrollTimer->start(100);
	}
	else
	{
		mScrollMagnitude = 0;
		mScrollTimer->stop();
	}

	QList<UBSceneThumbnailPixmap*> pixmapItems;
    foreach (QGraphicsItem *item, scene()->items(mapToScene(boundingFrame)))
    {
        UBSceneThumbnailPixmap* sceneItem = dynamic_cast<UBSceneThumbnailPixmap*>(item);
        if (sceneItem)
            pixmapItems.append(sceneItem);
    }