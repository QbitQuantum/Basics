void Lilith3D::IntersectRayFromScreen( int x, int y, int flags, LilithObjectList* vec )
{
	double p0x, p0y, p0z, p1x, p1y, p1z;

	double modelView[ 16 ];
	glGetDoublev( GL_MODELVIEW_MATRIX, modelView );
	double projection[ 16 ];
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	int viewport[ 4 ];
	glGetIntegerv( GL_VIEWPORT, viewport );

	gluUnProject( (double) x, (double) ( viewport[3]-y ), 0,
							  modelView, projection, viewport,
							  &p0x, &p0y, &p0z );

	gluUnProject( (double) x, (double) ( viewport[3]-y ), 1,
							  modelView, projection, viewport,
							  &p1x, &p1y, &p1z );

	//GLOUTPUT( "ret0=%d ret1=%d\n", ret0, ret1 );

	Vector3F point = { (float) p0x, (float) p0y, (float) p0z };
	Vector3F dir   = { (float) ( p1x-p0x ), (float) ( p1y-p0y ), float( p1z-p0z ) };

	dir.Normalize();
	Ray ray;
	ray.origin = point;
	ray.direction = dir;
	ray.length = FAR_PLANE_DISTANCE;

	IntersectRay( ray, flags, vec );
}