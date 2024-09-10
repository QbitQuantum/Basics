/** Util to find the normal of the face that we hit */
static bool FindGeomOpposingNormal(const PxLocationHit& PHit, FVector& OutNormal, FVector& OutPointOnGeom)
{
	PxTriangleMeshGeometry PTriMeshGeom;
	PxConvexMeshGeometry PConvexMeshGeom;
	if(	PHit.shape->getTriangleMeshGeometry(PTriMeshGeom) && 
		PTriMeshGeom.triangleMesh != NULL &&
		PHit.faceIndex < PTriMeshGeom.triangleMesh->getNbTriangles() )
	{
		const int32 TriIndex = PHit.faceIndex;
		const void* Triangles = PTriMeshGeom.triangleMesh->getTriangles();

		// Grab triangle indices that we hit
		int32 I0, I1, I2;

		if(PTriMeshGeom.triangleMesh->getTriangleMeshFlags() & PxTriangleMeshFlag::eHAS_16BIT_TRIANGLE_INDICES) 
		{
			PxU16* P16BitIndices = (PxU16*)Triangles;
			I0 = P16BitIndices[(TriIndex*3)+0];
			I1 = P16BitIndices[(TriIndex*3)+1];
			I2 = P16BitIndices[(TriIndex*3)+2];
		}
		else
		{
			PxU32* P32BitIndices = (PxU32*)Triangles;
			I0 = P32BitIndices[(TriIndex*3)+0];
			I1 = P32BitIndices[(TriIndex*3)+1];
			I2 = P32BitIndices[(TriIndex*3)+2];
		}

		// Get verts we hit (local space)
		const PxVec3* PVerts = PTriMeshGeom.triangleMesh->getVertices();
		const PxVec3 V0 = PVerts[I0];
		const PxVec3 V1 = PVerts[I1];
		const PxVec3 V2 = PVerts[I2];

		// Find normal of triangle, and convert into world space
		PxVec3 PLocalTriNormal = ((V1 - V0).cross(V2 - V0)).getNormalized();
		TransformNormalToShapeSpace(PTriMeshGeom.scale, PLocalTriNormal, PLocalTriNormal);
	
		const PxTransform PShapeWorldPose = PxShapeExt::getGlobalPose(*PHit.shape, *PHit.actor); 

		const PxVec3 PWorldTriNormal = PShapeWorldPose.rotate(PLocalTriNormal);
		OutNormal = P2UVector(PWorldTriNormal);
		
		if (PTriMeshGeom.scale.isIdentity())
		{
			OutPointOnGeom = P2UVector(PShapeWorldPose.transform(V0));
		}

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		if (!OutNormal.IsNormalized())
		{
			UE_LOG(LogPhysics, Warning, TEXT("Non-normalized Normal (Hit shape is TriangleMesh): %s (V0:%s, V1:%s, V2:%s)"), *OutNormal.ToString(), *P2UVector(V0).ToString(), *P2UVector(V1).ToString(), *P2UVector(V2).ToString());
			UE_LOG(LogPhysics, Warning, TEXT("WorldTransform \n: %s"), *P2UTransform(PShapeWorldPose).ToString());
		}
#endif
		return true;
	}
	else if(PHit.shape->getConvexMeshGeometry(PConvexMeshGeom) && 
		PConvexMeshGeom.convexMesh != NULL &&
		PHit.faceIndex < PConvexMeshGeom.convexMesh->getNbPolygons() )
	{
		const int32 PolyIndex = PHit.faceIndex;
		PxHullPolygon PPoly;
		bool bSuccess = PConvexMeshGeom.convexMesh->getPolygonData(PolyIndex, PPoly);
		if(bSuccess)
		{
			PxVec3 PPlaneNormal(PPoly.mPlane[0], PPoly.mPlane[1], PPoly.mPlane[2]);

			// Convert to local space, taking scale into account.
			// TODO: can we just change the hit normal within the physx code where we choose the most opposing normal, and avoid doing this here again?
			PxVec3 PLocalPolyNormal;
			TransformNormalToShapeSpace(PConvexMeshGeom.scale, PPlaneNormal.getNormalized(), PLocalPolyNormal);			
			const PxTransform PShapeWorldPose = PHit.actor->getGlobalPose() * PHit.shape->getLocalPose(); 

			const PxVec3 PWorldPolyNormal = PShapeWorldPose.rotate(PLocalPolyNormal);
			OutNormal = P2UVector(PWorldPolyNormal);

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
			if (!OutNormal.IsNormalized())
			{
				UE_LOG(LogPhysics, Warning, TEXT("Non-normalized Normal (Hit shape is ConvexMesh): %s (LocalPolyNormal:%s)"), *OutNormal.ToString(), *P2UVector(PLocalPolyNormal).ToString());
				UE_LOG(LogPhysics, Warning, TEXT("WorldTransform \n: %s"), *P2UTransform(PShapeWorldPose).ToString());
			}
#endif
			return true;
		}
	}

	return false;
}