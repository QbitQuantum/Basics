void UniTransform3fPlane(const UniTransform3f& transf,const Plane3f& plane, Plane3f* outPlane) {
	
	
	UniTransform3fDirection(transf, plane.norm.dir, &outPlane->norm.dir);
	F32 d = plane.d;
	
	Point3f point;
	//origin projection on the plane
	F32 t = - d/(plane.norm.dir.dir.x *plane.norm.dir.dir.x + plane.norm.dir.dir.y*plane.norm.dir.dir.y + plane.norm.dir.dir.z*plane.norm.dir.dir.z);
	point.point.x = t * plane.norm.dir.dir.x;
	point.point.y = t * plane.norm.dir.dir.y;
	point.point.z = t * plane.norm.dir.dir.z;
	
	Point3f transfPoint;
	UniTransform3fPoint(transf, point, &transfPoint);
	
	
	//distance fro origin and new point
	outPlane->d = Sqrtf((transfPoint.point.x * transfPoint.point.x)+(transfPoint.point.y * transfPoint.point.y)+(transfPoint.point.z * transfPoint.point.z));
	
}