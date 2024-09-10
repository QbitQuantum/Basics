PX_FORCE_INLINE void collideWithSphere(PxsParticleCollData& collData, const PxSphereGeometry& sphereShapeData,
									   PxReal proxRadius)
{
	PxVec3& oldPos = collData.localOldPos;
	PxVec3& newPos = collData.localNewPos;

	PxReal radius = sphereShapeData.radius;

	PxReal oldPosDist2 = oldPos.magnitudeSquared();
	PxReal radius2 = radius * radius;

	bool oldInSphere = (oldPosDist2 < radius2);

	if(oldInSphere)
	{
		// old position inside the skeleton
		// add ccd with time 0.0

		collData.localSurfaceNormal = oldPos;
		if (oldPosDist2 > 0.0f)
			collData.localSurfaceNormal *= PxRecipSqrt(oldPosDist2);
		else
			collData.localSurfaceNormal = PxVec3(0,1.0f,0);

		// Push particle to surface such that the distance to the surface is equal to the collision radius
		collData.localSurfacePos = collData.localSurfaceNormal * (radius + collData.restOffset);
		collData.ccTime = 0.0;
		collData.localFlags |= PXS_FLUID_COLL_FLAG_L_CC;
	}
	else
	{
		// old position is outside of the skeleton
		
		PxVec3 motion = newPos - oldPos;

		// Discriminant
		PxReal b = motion.dot(oldPos) * 2.0f;
		PxReal a2 = 2.0f * motion.magnitudeSquared();
		PxReal disc = (b*b) - (2.0f * a2 * (oldPosDist2 - radius2));

		bool intersection = disc > 0.0f;

		if ((!intersection) || (a2 == 0.0f))
		{
			// the ray does not intersect the sphere
			collideWithSphereNonContinuous(collData, newPos, radius, proxRadius);
		}
		else
		{
			// the ray intersects the sphere
			PxReal t = -(b + PxSqrt(disc)) / a2;	// Compute intersection point
			
			if (t < 0.0f || t > 1.0f)
			{
				// intersection point lies outside motion vector
				collideWithSphereNonContinuous(collData, newPos, radius, proxRadius);
			}
			else if(t < collData.ccTime)
			{
				// intersection point lies on sphere, add lcc
				//collData.localSurfacePos = oldPos + (motion * t);
				//collData.localSurfaceNormal = collData.localSurfacePos;
				//collData.localSurfaceNormal *= (1.0f / radius);
				//collData.localSurfacePos += (collData.localSurfaceNormal * collData.restOffset);
				PxVec3 relativeImpact = motion*t;
				collData.localSurfaceNormal = oldPos + relativeImpact;
				collData.localSurfaceNormal *= (1.0f / radius);		
				computeContinuousTargetPosition(collData.localSurfacePos, collData.localOldPos, relativeImpact, collData.localSurfaceNormal, collData.restOffset);
				
				collData.ccTime = t;
				collData.localFlags |= PXS_FLUID_COLL_FLAG_L_CC;
			}
		}
	}
}