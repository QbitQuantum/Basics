void HRocker::onTouchMoved(Touch* touch, Event* event) {
	Vec2 touchPoint = touch->getLocationInView();
	touchPoint = Director::getInstance()->convertToGL(touchPoint);
	if (touchPoint.distance(centerPoint) > radius) {
		touchPoint.subtract(centerPoint);
		touchPoint.normalize();
		touchPoint *= radius;
		touchPoint.add(centerPoint);
		currentPoint = touchPoint;
//		currentPoint = ccpAdd(centerPoint,
//				ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)), radius));
	} else {
		currentPoint = touchPoint;
	}
}