static PxU32 computeSweepConvexPlane(
	const PxConvexMeshGeometry& convexGeom, ConvexHullData* hullData, const PxU32& nbPolys, const PxTransform& pose,
	const PxVec3& impact_, const PxVec3& unitDir)
{
	PX_ASSERT(nbPolys);

	const PxVec3 impact = impact_ - unitDir * gEpsilon;

	const PxVec3 localPoint = pose.transformInv(impact);
	const PxVec3 localDir = pose.rotateInv(unitDir);

	const FastVertex2ShapeScaling scaling(convexGeom.scale);

// BEGIN EPIC MODIFICATION Improved selection of 'most opposing' face
	bool bMinIndexValid = false;
	PxU32 minIndex = 0;
	PxReal maxD = -PX_MAX_REAL;
	PxU32 maxDIndex = 0;
	PxReal minNormalDot = PX_MAX_REAL;
	static const float onSurfaceEpsilon = 0.2f; // tolerance to determine that an impact point is 'on' a face
	// Iterate over each poly
	for(PxU32 j=0; j<nbPolys; j++)
	{
		const PxPlane& pl = hullData->mPolygons[j].mPlane;

		PxPlane plane;
		scaling.transformPlaneToShapeSpace(pl.n, pl.d, plane.n, plane.d);

		// Find distance of impact point to this place
		PxReal d = plane.distance(localPoint);
		// Track plane that impact point is furthest point (will be out fallback normal)
		if(d>maxD)
		{
			maxDIndex = j;
			maxD = d;
		}

		// If impact point is 'behind' this plane, we are not interested
		if(d<-onSurfaceEpsilon)
			continue;

		// Calculate direction dot plane normal
		const PxReal normalDot = plane.n.dot(localDir);
		// If this is more opposing than our current 'most opposing' normal, update 'most opposing'
		if(normalDot<minNormalDot)
		{
			minIndex = j;
			bMinIndexValid = true;
			minNormalDot = normalDot;
		}
	}
	// If we found at least one face that we are considered 'on', use best normal
	if(bMinIndexValid)
	{
		return minIndex;
	}
	// Fallback is the face that we are most in front of
	else
	{
		return maxDIndex;
	}
// END EPIC MODIFICATION
}