bool OrE::Math::HitDetection( Ellipsoid e1, Ellipsoid e2, Vec3& _vFeedbackLocation )
{
	// Absolute squared distance vector from e2 to e1
	Vec3 vDist = e1.vMiddlePoint - e2.vMiddlePoint;
	Vec3 vDistSq = vDist * vDist;
	// Determine the point in the middle between both surfaces.
	// Point on surface from e1, which is nearest to the center of e2 is p1 = r1 * -vDist + e1.m.
	// Point on surface from e2, which is nearest to the center of e1 is p2 = r2 * vDist + e2.m.
	// The point between them is (p1+p2)/2 = ((r2-r1) * vDist + e1.m+e2.m)/2
	float r1 = InvSqrt( vDistSq.Dot( e1.vRadiiInvSq ) );
	float r2 = InvSqrt( vDistSq.Dot( e2.vRadiiInvSq ) );
	_vFeedbackLocation = 0.5f*((r2-r1) * vDist + e1.vMiddlePoint + e2.vMiddlePoint);

	// Same as in HitTest
	return r1+r2 >= 1.0f;
}