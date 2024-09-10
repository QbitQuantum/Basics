bool FormTriangle::rayTest(const Vec3f &start, const Vec3f &dir, float &t, Vec3f &hitPos) {
	Vec3f e1 = _points[1] - _points[0];
	Vec3f e2 = _points[2] - _points[0];

	Vec3f h = dir.cross(e2);
	float a = e1.dot(h);

	if(abs(a) < 0.00001f)
		return false;

	float f = 1.0f / a;

	Vec3f s = start - _points[0];

	float u = f * s.dot(h);

	if(u < 0.0f || u > 1.0f)
		return false;

	Vec3f q = s.cross(e1);

	float v = f * dir.dot(q);

	if(v < 0.0f || u + v > 1.0f)
		return false;

	t = f * e2.dot(q);

	if(t > 0.00001f) {
		hitPos = start + dir * t;
		
		return true;
	}

	return false;
}