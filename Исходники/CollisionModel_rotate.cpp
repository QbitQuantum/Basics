/*
================
CM_RotatePoint

  rotates a point about an arbitrary axis using the tangent of half the rotation angle
================
*/
void CM_RotatePoint( idVec3 &point, const idVec3 &origin, const idVec3 &axis, const float tanHalfAngle ) {
	double d, t, s, c;
	idVec3 proj, v1, v2;
	point -= origin;
	proj = axis * ( point * axis );
	v1 = point - proj;
	v2 = axis.Cross( v1 );
	// r = tan( a / 2 );
	// sin(a) = 2*r/(1+r*r);
	// cos(a) = (1-r*r)/(1+r*r);
	t = tanHalfAngle * tanHalfAngle;
	d = 1.0f / ( 1.0f + t );
	s = 2.0f * tanHalfAngle * d;
	c = ( 1.0f - t ) * d;
	point = v1 * c - v2 * s + proj + origin;
}