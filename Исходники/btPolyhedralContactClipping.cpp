bool btPolyhedralContactClipping::findSeparatingAxis(	const btConvexPolyhedron& hullA, const btConvexPolyhedron& hullB, const btTransform& transA, const btTransform& transB, btVector3& sep, btDiscreteCollisionDetectorInterface::Result& resultOut)
{
	gActualSATPairTests++;

//#ifdef TEST_INTERNAL_OBJECTS
	const btVector3 c0 = transA * hullA.m_localCenter;
	const btVector3 c1 = transB * hullB.m_localCenter;
	const btVector3 DeltaC2 = c0 - c1;
//#endif

	btScalar dmin = FLT_MAX;
	int curPlaneTests=0;

	int numFacesA = hullA.m_faces.size();
	// Test normals from hullA
	for(int i=0;i<numFacesA;i++)
	{
		const btVector3 Normal(hullA.m_faces[i].m_plane[0], hullA.m_faces[i].m_plane[1], hullA.m_faces[i].m_plane[2]);
		btVector3 faceANormalWS = transA.getBasis() * Normal;
		if (DeltaC2.dot(faceANormalWS)<0)
			faceANormalWS*=-1.f;

		curPlaneTests++;
#ifdef TEST_INTERNAL_OBJECTS
		gExpectedNbTests++;
		if(gUseInternalObject && !TestInternalObjects(transA, transB, DeltaC2, faceANormalWS, hullA, hullB, dmin))
			continue;
		gActualNbTests++;
#endif

		btScalar d;
		btVector3 wA, wB;
		if(!TestSepAxis( hullA, hullB, transA, transB, faceANormalWS, d, wA, wB))
			return false;

		if(d<dmin)
		{
			dmin = d;
			sep = faceANormalWS;
		}
	}

	int numFacesB = hullB.m_faces.size();
	// Test normals from hullB
	for(int i=0;i<numFacesB;i++)
	{
		const btVector3 Normal(hullB.m_faces[i].m_plane[0], hullB.m_faces[i].m_plane[1], hullB.m_faces[i].m_plane[2]);
		btVector3 WorldNormal = transB.getBasis() * Normal;
		if (DeltaC2.dot(WorldNormal)<0)
			WorldNormal *=-1.f;

		curPlaneTests++;
#ifdef TEST_INTERNAL_OBJECTS
		gExpectedNbTests++;
		if(gUseInternalObject && !TestInternalObjects(transA, transB, DeltaC2, WorldNormal, hullA, hullB, dmin))
			continue;
		gActualNbTests++;
#endif

		btScalar d;
		btVector3 wA, wB;
		if(!TestSepAxis(hullA, hullB, transA, transB, WorldNormal, d,wA, wB))
			return false;

		if(d<dmin)
		{
			dmin = d;
			sep = WorldNormal;
		}
	}

	btVector3 edgeAstart, edgeAend, edgeBstart, edgeBend;
	int edgeA=-1;
	int edgeB=-1;
	btVector3 worldEdgeA;
	btVector3 worldEdgeB;
	btVector3 witnessPointA, witnessPointB;
	

	int curEdgeEdge = 0;
	// Test edges
	for(int e0=0;e0<hullA.m_uniqueEdges.size();e0++)
	{
		const btVector3 edge0 = hullA.m_uniqueEdges[e0];
		const btVector3 WorldEdge0 = transA.getBasis() * edge0;
		for(int e1=0;e1<hullB.m_uniqueEdges.size();e1++)
		{
			const btVector3 edge1 = hullB.m_uniqueEdges[e1];
			const btVector3 WorldEdge1 = transB.getBasis() * edge1;

			btVector3 Cross = WorldEdge0.cross(WorldEdge1);
			curEdgeEdge++;
			if(!IsAlmostZero(Cross))
			{
				Cross = Cross.normalize();
				if (DeltaC2.dot(Cross)<0)
					Cross *= -1.f;


#ifdef TEST_INTERNAL_OBJECTS
				gExpectedNbTests++;
				if(gUseInternalObject && !TestInternalObjects(transA, transB, DeltaC2, Cross, hullA, hullB, dmin))
					continue;
				gActualNbTests++;
#endif

				btScalar dist;
				btVector3 wA, wB;
				if(!TestSepAxis( hullA, hullB, transA, transB, Cross, dist, wA, wB))
					return false;

				if(dist<dmin)
				{
					dmin = dist;
					sep = Cross;
					edgeA=e0;
					edgeB=e1;
					worldEdgeA = WorldEdge0;
					worldEdgeB = WorldEdge1;
					witnessPointA=wA;
					witnessPointB=wB;
				}
			}
		}

	}

	if (edgeA>=0&&edgeB>=0)
	{
//		printf("edge-edge\n");
		//add an edge-edge contact

		btVector3 ptsVector;
		btVector3 offsetA;
		btVector3 offsetB;
		btScalar tA;
		btScalar tB;

		btVector3 translation = witnessPointB-witnessPointA;

		btVector3 dirA = worldEdgeA;
		btVector3 dirB = worldEdgeB;
		
		btScalar hlenB = 1e30f;
		btScalar hlenA = 1e30f;

		btSegmentsClosestPoints(ptsVector, offsetA, offsetB, tA, tB,
			translation,
			dirA, hlenA,
			dirB, hlenB);

		btScalar nlSqrt = ptsVector.length2();
		if (nlSqrt>SIMD_EPSILON)
		{
			btScalar nl = btSqrt(nlSqrt);
			ptsVector *= 1.f/nl;
			if (ptsVector.dot(DeltaC2)<0.f)
			{
				ptsVector*=-1.f;
			}
			btVector3 ptOnB = witnessPointB + offsetB;
			btScalar distance = nl;
			resultOut.addContactPoint(ptsVector, ptOnB,-distance);
		}

	}


	if((DeltaC2.dot(sep))<0.0f)
		sep = -sep;

	return true;
}