bool IntersectTriangle(const Vec3& orig, const Vec3& dir,
					   Vec3& v0, Vec3& v1, Vec3& v2,
					   float* t, float* u, float* v)
{
	// E1
	Vec3 E1 = v1 - v0;

	// E2
	Vec3 E2 = v2 - v0;

	// P
	Vec3 P = dir.cross(E2);

	// determinant
	float det = E1.dot(P);

	// keep det > 0, modify T accordingly
	Vec3 T;
	if( det >0 )
	{
		T = orig - v0;
	}
	else
	{
		T = v0 - orig;
		det = -det;
	}

	// If determinant is near zero, ray lies in plane of triangle
	if( det < 0.0001f )
		return false;

	// Calculate u and make sure u <= 1
	*u = T.dot(P);
	if( *u < 0.0f || *u > det )
		return false;

	// Q
	Vec3 Q = T.cross(E1);

	// Calculate v and make sure u + v <= 1
	*v = dir.dot(Q);
	if( *v < 0.0f || *u + *v > det )
		return false;

	// Calculate t, scale parameters, ray intersects triangle
	*t = E2.dot(Q);

	float fInvDet = 1.0f / det;
	*t *= fInvDet;
	*u *= fInvDet;
	*v *= fInvDet;

	return true;
}