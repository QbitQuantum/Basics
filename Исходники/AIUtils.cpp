bool FindNearestPointOnLine( const LTVector& l0, const LTVector& l1, const LTVector& vPos, LTVector* pvPosNearest )
{
	// Sanity check.

	if( !pvPosNearest )
	{
		return false;
	}

	// Find the line's normal.

	LTVector vUp( 0.f, 1.f, 0.f );
	LTVector vDir = l1 - l0;
	vDir.Normalize();

	LTVector vNormal = vDir.Cross( vUp );
	vNormal.Normalize();

	// Find the nearest intersection point between the point and the line.

	LTVector vRay0 = vPos + ( vNormal * 100000.f );
	LTVector vRay1 = vPos - ( vNormal * 100000.f );

	return ( kRayIntersect_Failure != RayIntersectLineSegment( l0, l1, vRay0, vRay1, true, pvPosNearest ) );
}