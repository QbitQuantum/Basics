bool SphereTriangleDetector::collide(const btVector3& sphereCenter,btVector3 &point, btVector3& resultNormal, btScalar& depth, btScalar &timeOfImpact, btScalar contactBreakingThreshold)
{

	const btVector3* vertices = &m_triangle->getVertexPtr(0);
	
	btScalar radius = m_sphere->getRadius();
	btScalar radiusWithThreshold = radius + contactBreakingThreshold;

	btVector3 normal = (vertices[1]-vertices[0]).cross(vertices[2]-vertices[0]);
	normal.normalize();
	btVector3 p1ToCentre = sphereCenter - vertices[0];
	btScalar distanceFromPlane = p1ToCentre.dot(normal);

	if (distanceFromPlane < btScalar(0.))
	{
		//triangle facing the other way
		distanceFromPlane *= btScalar(-1.);
		normal *= btScalar(-1.);
	}

	bool isInsideContactPlane = distanceFromPlane < radiusWithThreshold;
	
	// Check for contact / intersection
	bool hasContact = false;
	btVector3 contactPoint;
	if (isInsideContactPlane) {
		if (facecontains(sphereCenter,vertices,normal)) {
			// Inside the contact wedge - touches a point on the shell plane
			hasContact = true;
			contactPoint = sphereCenter - normal*distanceFromPlane;
		} else {
			// Could be inside one of the contact capsules
			btScalar contactCapsuleRadiusSqr = radiusWithThreshold*radiusWithThreshold;
			btVector3 nearestOnEdge;
			for (int i = 0; i < m_triangle->getNumEdges(); i++) {
				
				btVector3 pa;
				btVector3 pb;
				
				m_triangle->getEdge(i,pa,pb);

				btScalar distanceSqr = SegmentSqrDistance(pa,pb,sphereCenter, nearestOnEdge);
				if (distanceSqr < contactCapsuleRadiusSqr) {
					// Yep, we're inside a capsule
					hasContact = true;
					contactPoint = nearestOnEdge;
				}
				
			}
		}
	}

	if (hasContact) {
		btVector3 contactToCentre = sphereCenter - contactPoint;
		btScalar distanceSqr = contactToCentre.length2();

		if (distanceSqr < radiusWithThreshold*radiusWithThreshold)
		{
			if (distanceSqr>SIMD_EPSILON)
			{
				btScalar distance = btSqrt(distanceSqr);
				resultNormal = contactToCentre;
				resultNormal.normalize();
				point = contactPoint;
				depth = -(radius-distance);
			} else
			{
				btScalar distance = 0.f;
				resultNormal = normal;
				point = contactPoint;
				depth = -radius;
			}
			return true;
		}
	}
	
	return false;
}