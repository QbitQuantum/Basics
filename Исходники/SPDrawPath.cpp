void Path::addOval(const cocos2d::Rect& oval) {
	moveTo(oval.getMaxX(), oval.getMidY());
	arcTo(oval.getMidX(), oval.getMidY(), oval.size.width/2, oval.size.height/2, 0.0f, 360.0_to_rad, 0.0f);
	closePath();
}