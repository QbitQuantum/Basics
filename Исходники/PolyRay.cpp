Number Ray::boxIntersect(const Vector3 &box, const Matrix4 &transformMatrix, float near, float far) const {

	if(box.x == 0 || box.y == 0 || box.z == 0)
		return -1.0;

	Ray r  = tranformByMatrix(transformMatrix.Inverse());

	Vector3 bounds[2];
	bounds[0] = Vector3(-box.x * 0.5, -box.y * 0.5, -box.z * 0.5);
	bounds[1] = Vector3(box.x * 0.5, box.y * 0.5, box.z * 0.5);	
	
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	tmin = (bounds[r.sign[0]].x - r.origin.x) * r.inv_direction.x;
	tmax = (bounds[1-r.sign[0]].x - r.origin.x) * r.inv_direction.x;
	tymin = (bounds[r.sign[1]].y - r.origin.y) * r.inv_direction.y;
	tymax = (bounds[1-r.sign[1]].y - r.origin.y) * r.inv_direction.y;

	if ( (tmin > tymax) || (tymin > tmax) )
		return -1.0;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	tzmin = (bounds[r.sign[2]].z - r.origin.z) * r.inv_direction.z;
	tzmax = (bounds[1-r.sign[2]].z - r.origin.z) * r.inv_direction.z;
	
	if ( (tmin > tzmax) || (tzmin > tmax) )
		return -1.0;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;
		
	if( (tmin < far) && (tmax > near) ) {
        return fabs(tmin);
    } else {
        return -1.0;
    }
}