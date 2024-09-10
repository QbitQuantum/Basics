void BaseView::frameAll(const BoundingBox & b)
{
	Vector3F eye = b.center();
	eye.z = b.getMax(2) + b.distance(0) / hfov() * .55f + 120.f;
	setEyePosition(eye);
	
	Matrix44F m;
	m.setTranslation(eye);
	*cameraSpaceR() = m;
	m.inverse();
	*cameraInvSpaceR() = m;
	setFrustum(1.33f, 1.f, 26.2f, -1.f, -1000.f);
}