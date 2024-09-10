bool Transform::intersect(const Ray &r, Hit &h, float tmin)
{
	float scaler;
	Vec3f d, o, n_ws;
	Ray r1;
	Matrix m;

	r1 = r;
	m = matrix;

	// get the length of direction vector
	scaler = r.getDirection().Length();

	// normalize the direction vector
	d = r1.getDirection();
	d.Normalize();

	// transform the ray
	o = r1.getOrigin();
	m.Transform(o);
	m.TransformDirection(d);

	// Now, Ray origin and direction is transformed to Object Space
	// intersect at Object space
	if (object->intersect(r1, h, tmin) == false)
		return false;

	// transform the hit point and 
	// normal vector back to world space
	//
	// In order to transform the normal vector,
	// let,
	// n_ws,  normal vector in world space,
	// v_ws,  perpendicular to normal in world space,
	// n_os,  normal vector in object space
	// v_os,  perpendicular to normal in object space,
	//
	// given,
	// n_os^T * v_os = 0 and v_ws^T * n_ws = 0
	// 
	// where,
	//   ^T present transport of the vector(matrix)
	//   ^-1 present inverse of the matrix
	//
	// n_os^T * v_os = 0 
	// ==> n_os^T * (M^-1 * M) * v_os = 0 
	// ==> (n_os^T * M^-1) * v_ws = 0
	// and
	//   n_ws * v_ws = 0
	// thus 
	//   n_ws = (n_os^T) * M^-1 = (M^T)^-1 * n_os

	m.Transpose();
	m.Inverse();
	n_ws = h.getNormal();
	m.Transform(n_ws);

	h.set(h.getT() * scaler, h.getMaterial(), n_ws, r);

	return true;
}