cc::Vec3f GeometricPlane::getNormal() {
	const cc::Vec3f p0 = (_xform.getWorld() * cc::Vec4f(_verts[0].position, 1.0f)).truncated();
	const cc::Vec3f p1 = (_xform.getWorld() * cc::Vec4f(_verts[1].position, 1.0f)).truncated();
	const cc::Vec3f p2 = (_xform.getWorld() * cc::Vec4f(_verts[2].position, 1.0f)).truncated();
	const cc::Vec3f p3 = (_xform.getWorld() * cc::Vec4f(_verts[3].position, 1.0f)).truncated();
	const cc::Vec3f a = p1 - p0;
	const cc::Vec3f b = p3 - p0;
	return a.cross(b).normalized();
}