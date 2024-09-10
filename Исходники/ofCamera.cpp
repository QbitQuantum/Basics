//----------------------------------------
float ofCamera::getImagePlaneDistance(ofRectangle viewport) const {
	return viewport.height / (2.0f * tanf(PI * fov / 360.0f));
}