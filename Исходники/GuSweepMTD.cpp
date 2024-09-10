bool physx::Gu::computePlane_ConvexMTD(const PxPlane& plane, const PxConvexMeshGeometry& convexGeom, const PxTransform& convexPose, PxSweepHit& hit)
{
	const ConvexMesh* convexMesh = static_cast<const ConvexMesh*>(convexGeom.convexMesh);
	const Cm::FastVertex2ShapeScaling convexScaling(convexGeom.scale);
	PxU32 nbVerts = convexMesh->getNbVerts();
	const PxVec3* PX_RESTRICT verts = convexMesh->getVerts();

	PxVec3 worldPointMin = convexPose.transform(convexScaling * verts[0]);
	PxReal dmin = plane.distance(worldPointMin);
	for(PxU32 i=1;i<nbVerts;i++)
	{
		const PxVec3 worldPoint = convexPose.transform(convexScaling * verts[i]);
		const PxReal d = plane.distance(worldPoint);
		if(dmin > d)
		{
			dmin = d;
			worldPointMin = worldPoint;
		}
	}

	hit.normal		= plane.n;
	hit.distance	= dmin;
	hit.position	= worldPointMin - plane.n * dmin;
	return true;
}