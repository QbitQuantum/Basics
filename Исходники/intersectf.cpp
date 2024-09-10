bool IntersectRaySpheref( const Point3f& origin, const Direction3f& direction, const Point3f& centerSph, F32 radius, F32& t, Point3f& q ) {
	Vec3f m;
	Vec3fSub( origin.point , centerSph.point, &m );
	F32 b = Vec3fDot( m , direction.dir );
	F32 c = Vec3fDot( m , m ) - radius * radius;
	// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
	if(c > 0.f &&  b > 0.f)
		return false;
	F32 discr = b * b - c;
	// A negative discriminant corresponds to ray missing sphere
	if (discr < 0.f)
		return false;
	// Ray now found to intersect sphere, compute smallest t value of intersection
	t = -b - Sqrtf(discr);
	// If t is negative, ray started inside sphere so clamp t to zero
	if (t < 0.f)
		t = 0.f;
	Vec3f tempRes = direction.dir;
	Vec3fMultScalarInplace( t , &tempRes );
	Vec3fSumInplace( origin.point , &tempRes );
	q.point = tempRes;
	return true;
}