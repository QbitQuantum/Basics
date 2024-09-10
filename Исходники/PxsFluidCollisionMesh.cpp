	PX_FORCE_INLINE PxU32 collideWithMeshTriangle(PxVec3& surfaceNormal, PxVec3& surfacePos,
								  PxVec3& proxSurfaceNormal, PxVec3& proxSurfacePos,
								  PxReal& ccTime, PxReal& distOldToSurface,
								  const PxVec3& oldPos, const PxVec3& newPos,
								  const PxVec3& origin, const PxVec3& e0,
								  const PxVec3& e1, bool hasCC,
								  const PxReal& collRadius, const PxReal& proxRadius)
	{
		PxU32 flags = 0;

		PxReal collisionRadius2 = collRadius * collRadius;
		PxReal proximityRadius2 = proxRadius * proxRadius;

		PxVec3 motion = newPos - oldPos;

		// dc and proximity tests
		PxVec3 tmpV = origin - newPos;

		PxReal a = e0.dot(e0);
		PxReal b = e0.dot(e1);
		PxReal c = e1.dot(e1);
		PxReal d = e0.dot(tmpV);
		PxReal e = e1.dot(tmpV);
		PxVec3 coords;
		coords.x = b*e - c*d;	// s * det
		coords.y = b*d - a*e;	// t * det
		coords.z = a*c - b*b;	// det

		bool insideCase = false;
		PxVec3 clampedCoords(PxVec3(0));
		if (coords.x <= 0.0f) 
		{
			c = PxMax(c, FLT_MIN);
			clampedCoords.y = -e/c;
		}
		else if (coords.y <= 0.0f) 
		{
			a = PxMax(a, FLT_MIN);
			clampedCoords.x = -d/a;
		}
		else if (coords.x + coords.y > coords.z) 
		{
			PxReal denominator = a + c - b - b;
			PxReal numerator   = c + e - b - d;
			denominator = PxMax(denominator, FLT_MIN);
			clampedCoords.x = numerator / denominator;
			clampedCoords.y = 1.0f - clampedCoords.x;
		}
		else // all inside 
		{	
			PxReal tmpF = PxMax(coords.z, FLT_MIN);
			tmpF = 1.0f / tmpF;
			clampedCoords.x = coords.x * tmpF;
			clampedCoords.y = coords.y * tmpF;
			insideCase = true;
		}
		clampedCoords.x = PxMax(clampedCoords.x, 0.0f);
		clampedCoords.y = PxMax(clampedCoords.y, 0.0f);
		clampedCoords.x = PxMin(clampedCoords.x, 1.0f);
		clampedCoords.y = PxMin(clampedCoords.y, 1.0f);

		// Closest point to particle inside triangle
		PxVec3 closest = origin + e0 * clampedCoords.x + e1 * clampedCoords.y;

		PxVec3 triangleOffset = newPos - closest;
		PxReal triangleDistance2 = triangleOffset.magnitudeSquared();

		PxVec3 triangleNormal = e0.cross(e1);
		PxReal e0e1Span = triangleNormal.magnitude();
		
		bool isInFront = triangleOffset.dot(triangleNormal) > 0.0f;

		// MS: Possible optimzation
		/*
		if (isInFront && (triangleDistance2 >= proximityRadius2))
			return flags;
		*/

		bool isInProximity = insideCase && (triangleDistance2 < proximityRadius2) && isInFront;
		bool isInDiscrete = (triangleDistance2 < collisionRadius2) && isInFront;

		if (!hasCC)
		{
			// Only apply discrete and proximity collisions if no continuous collisions was detected so far (for any colliding shape)

			if (isInDiscrete)
			{
				if (triangleDistance2 > PXS_FLUID_COLL_TRI_DISTANCE)
				{
					surfaceNormal = triangleOffset * PxRecipSqrt(triangleDistance2);
				}
				else
				{
					surfaceNormal = triangleNormal * (1.0f / e0e1Span);
				}
				surfacePos = closest + (surfaceNormal * collRadius);
				flags |= PXS_FLUID_COLL_FLAG_L_DC;
			}
			
			if (isInProximity)
			{
				proxSurfaceNormal = triangleNormal * (1.0f / e0e1Span);
				proxSurfacePos = closest + (proxSurfaceNormal * collRadius);
				flags |= PXS_FLUID_COLL_FLAG_L_PROX;

				tmpV = (oldPos - origin); //this time it's not the newPosition offset.
				distOldToSurface = proxSurfaceNormal.dot(tmpV);	// Need to return the distance to decide which constraints should be thrown away
			}
		}

		if (!isInDiscrete && !isInProximity)
		{
			// cc test (let's try only executing this if no discrete coll, or proximity happend).
			tmpV = origin - oldPos; //this time it's not the newPosition offset.
			PxReal pDistN = triangleNormal.dot(tmpV);
			PxReal rLengthN = triangleNormal.dot(motion);

			if (pDistN > 0.0f || rLengthN >= pDistN) 
				return flags;

			//we are in the half closed interval [0.0f, 1.0)
			
			PxReal t = pDistN / rLengthN;
			PX_ASSERT((t >= 0.0f) && (t < 1.0f));

			PxVec3 relativePOSITION = (motion * t);
			PxVec3 testPoint = oldPos + relativePOSITION;

			// a,b,c and coords.z don't depend on test point -> still valid
			tmpV = origin - testPoint;
			d = e0.dot(tmpV);
			e = e1.dot(tmpV);
			coords.x = b*e - c*d;
			coords.y = b*d - a*e;

			//maybe we don't need this for rare case leaking on triangle boundaries? 
			PxReal eps = coords.z * PXS_FLUID_COLL_RAY_EPSILON_FACTOR;

			if ((coords.x >= -eps) && (coords.y >= -eps) && (coords.x + coords.y <= coords.z + eps)) 
			{
				PxReal invLengthN = (1.0f / e0e1Span);
				distOldToSurface = -pDistN * invLengthN;	// Need to return the distance to decide which constraints should be thrown away
				surfaceNormal = triangleNormal * invLengthN;
				//surfacePos = testPoint + (surfaceNormal * collRadius);
				computeContinuousTargetPosition(surfacePos, oldPos, relativePOSITION, surfaceNormal, collRadius);
				ccTime = t;
				flags |= PXS_FLUID_COLL_FLAG_L_CC;
			}
		}

		return flags;
	}