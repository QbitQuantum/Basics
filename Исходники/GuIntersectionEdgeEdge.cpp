bool Gu::intersectEdgeEdgeNEW(const PxVec3& p1, const PxVec3& p2, const PxVec3& dir, const PxVec3& p3, const PxVec3& p4, PxReal& dist, PxVec3& ip)
{
	// Build plane P based on edge (p1, p2) and direction (dir)
	const PxVec3 v12 = p2-p1;

	Gu::Plane plane;
	plane.normal = v12.cross(dir);
	plane.d = -(plane.normal.dot(p1));

	PxReal d3 = plane.distance(p3);
	PxReal d4 = plane.distance(p4);

	// line doesn't intersect plane if both have same sign or both are 0.
	if(d3*d4>0 || d3==d4) 
		return false;

	// vector from p1 to intersection point of plane and edge (p3,p4)
	PxVec3 v1i = (d3*p4 - d4*p3)/(d3-d4) - p1;

	// find largest 2D plane projection
	PxU32 i,j;
	Ps::closestAxis(plane.normal, i, j);

	// compute distance of v1i to intersection of line (v1i, v1i-dir) and line (0,v12)
	PxReal d = (v12[i]*v1i[j]-v12[j]*v1i[i])/(v12[i]*dir[j]-v12[j]*dir[i]);
	if(d<0.0f)
		return false;

	// vector from p1 to intersection point of two lines above
	v1i -= d*dir;

	// we are allowed to write invalid output
	dist = d;
	ip = p1 + v1i;

	// return if intersection point is on sweep side and between p1 and p2
	return v1i.dot(v1i-v12)<0.0f;
}