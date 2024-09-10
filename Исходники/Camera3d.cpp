bool Camera3d::PointInFrustum(const Vector3f &point)
{
	float pcz,pcx,pcy,h;

	// compute vector from camera position to p
	Vector3f v = point - _eye;

	// compute and test the Z coordinate
	pcz = v.Dot(-_frustumZ);
	if (pcz > _far || pcz < _near)
		return false;

	// compute and test the Y coordinate
	pcy = v.Dot(_frustumY);
	h = pcz * _frustumTanFOV;
	if (pcy > h || pcy < -h)
		return false;

	// compute and test the X coordinate
	pcx = v.Dot(_frustumX);
	h = h * _ratioAspect;
	if (pcx > h || pcx < -h)
		return false;
	return true;
}