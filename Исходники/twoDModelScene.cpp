void TwoDModelScene::worldWallDragged(items::WallItem *wall, const QPainterPath &shape, const QRectF &oldPos)
{
	bool isNeedStop = false;

	for (RobotItem * const robotItem : mRobots.values()) {
		if (shape.intersects(robotItem->realBoundingRect())) {
			isNeedStop = true;
			break;
		}
	}

	wall->onOverlappedWithRobot(isNeedStop);
	if (wall->isDragged() && ((mDrawingAction == none) ||
			(mDrawingAction == TwoDModelScene::wall && mCurrentWall == wall)))
	{
		wall->setFlag(QGraphicsItem::ItemIsMovable, !isNeedStop);
		if (isNeedStop) {
			wall->setCoordinates(oldPos);
		}
	}
}