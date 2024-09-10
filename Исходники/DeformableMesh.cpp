// PT: TODO: use Gu::intersectLineTriangle
static bool raycastTriangle(
	PxVec3& hit, 
	PxReal& t,
	const PxVec3& rayOrigin,
	const PxVec3& rayDir,
	const PxVec3& p0, 
	const PxVec3& p1, 
	const PxVec3& p2)
{
	PxVec3 d1 = p1 - p0;
	PxVec3 d2 = p2 - p0;
	PxVec3 n = d1.cross(d2);
	t = rayDir.dot(n);
	if (t == 0.0f)
		return false;
	t = n.dot(p0 - rayOrigin) / t;
	if (t < 0.0f)
		return false;
	hit = rayOrigin + rayDir * t;
	PxVec3 d0 = p0 - hit;
	d1 = p1-hit;
	d2 = p2-hit;
	PxVec3 c = d0.cross(d1);
	if (c.dot(n) < 0.0f)
		return false;
	c = d1.cross(d2);
	if (c.dot(n) < 0.0f)
		return false;
	c = d2.cross(d0);
	if (c.dot(n) < 0.0f)
		return false;
	return true;
}