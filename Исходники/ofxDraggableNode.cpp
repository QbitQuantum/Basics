bool ofxDraggableNode::isInside(ofPoint p) const {
	ofPoint screenCenter = cam->worldToScreen(this->getGlobalPosition());
	ofPoint screenCenterRadius = cam->worldToScreen(this->getGlobalPosition() + cam->getUpDir() * radius);
	float r = screenCenter.distance(screenCenterRadius); //radius on screen
	return p.distance(screenCenter) < r;
}