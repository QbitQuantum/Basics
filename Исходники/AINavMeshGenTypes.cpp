bool SAINAVMESHGEN_PLANE::RayIntersectNMGPlane( const LTVector& vRay0, const LTVector& vRay1, LTVector* pvIntersect )
{
	LTVector vNMGPlaneNormal;
	CAINavMeshGen::GetAINavMeshGen()->GetActualNormalFromPool( eNMGPlaneNormal, &vNMGPlaneNormal );

	LTVector vRayDir = vRay1 - vRay0;
	vRayDir.Normalize();

	// Determine if ray endpoints lie on opposite side of the plane.

	float fSign1 = ( ( vNMGPlaneNormal.x * vRay0.x ) +
					 ( vNMGPlaneNormal.y * vRay0.y ) +
				     ( vNMGPlaneNormal.z * vRay0.z ) + D );

	float fSign2 = ( ( vNMGPlaneNormal.x * vRay1.x ) +
				     ( vNMGPlaneNormal.y * vRay1.y ) +
				     ( vNMGPlaneNormal.z * vRay1.z ) + D );

	if( fSign1 * fSign2 >= 0.f )
	{
		return false;
	}

	// Determine if ray runs parallel to the plane.


	float fDenom = ( ( vNMGPlaneNormal.x * vRayDir.x ) + 
				     ( vNMGPlaneNormal.y * vRayDir.y ) + 
			  	     ( vNMGPlaneNormal.z * vRayDir.z ) );

	if( fDenom == 0.f )
	{
		return false;
	}

	// Calculate the point of intersection between the ray and the plane.

	float fNum = -( ( vNMGPlaneNormal.x * vRay0.x ) +
				    ( vNMGPlaneNormal.y * vRay0.y ) +
				    ( vNMGPlaneNormal.z * vRay0.z ) + D );

	float d = fNum / fDenom;
	*pvIntersect = ( vRay0 + ( vRayDir * d ) );

	return true;
}