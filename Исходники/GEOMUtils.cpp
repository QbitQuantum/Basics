double
angleBetweenVectors( const SbVec3f& u, const SbVec3f& v, const SbVec3f& normal )
{
	double cosAngle = v.dot( u ) / ( u.length() * v.length() );
	float     angle = acos( cosAngle );

	// FIXME: Check if this is required
	//
	SbVec3f cross  = u.cross( v );
	
	if( cross.dot( normal ) < 0 )
		angle = 2 * M_PI - angle;
	//

	return angle;
}