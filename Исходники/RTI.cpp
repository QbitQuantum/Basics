int RTI::intersect(ray r, triangle b, TYPE t,bool& result)
{
	TYPE u, v;
	bool ret = true;
	Vec3<TYPE> v0v1 = b.vertices[1] - b.vertices[0];
	Vec3<TYPE> v0v2 = b.vertices[2] - b.vertices[0];


	Vec3<TYPE> pvec = (r.dir).cross(v0v2);
	TYPE det = v0v1.dot(pvec);
#ifdef CULLING
	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (det < kEpsilon) ret = false;//return false;
#else
	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < kEpsilon) ret = false;//return false;
#endif
	if (ret == false)
		det = 1;
	TYPE invDet = 1 / det;
	Vec3<TYPE> tvec = r.orig - b.vertices[0];
	u = tvec.dot(pvec) * invDet;

	Vec3<TYPE> qvec = tvec.cross(v0v1);
	v = r.dir.dot(qvec) * invDet;

	t = v0v2.dot(qvec) * invDet;
	if (u < 0/*|| u > 1 */ || v < 0 || u + v > 1) ret = false;//return false;
	result = ret;
	return RAY_TRI_INTERSECT_LATENCY;
}