/**
input scaledPlaneBuf needs a capacity of the number of planes in convexShape
*/
void physx::collideWithConvex(PxPlane* scaledPlaneBuf, PxsParticleCollData* particleCollData, PxU32 numCollData, 
							  const Gu::GeometryUnion& convexShape, const PxReal proxRadius)
{
	PX_ASSERT(scaledPlaneBuf);
	PX_ASSERT(particleCollData);

	const PxConvexMeshGeometryLL& convexShapeData = convexShape.get<const PxConvexMeshGeometryLL>();
	const Gu::ConvexHullData* convexHullData = convexShapeData.hullData;
	PX_ASSERT(convexHullData);

	// convex bounds in local space
	PxMat33 scaling = convexShapeData.scale.toMat33(), invScaling;
	invScaling = scaling.getInverse();

	PX_ASSERT(!convexHullData->mAABB.isEmpty());
	PxBounds3 shapeBounds = PxBounds3::transformFast(scaling, convexHullData->mAABB);
	PX_ASSERT(!shapeBounds.isEmpty());
	shapeBounds.fattenFast(proxRadius);
	bool scaledPlanes = false;	

#if PXS_FLUID_USE_SIMD_CONVEX_COLLISION	
	const Vec3V boundMin = V3LoadU(shapeBounds.minimum);
	const Vec3V boundMax = V3LoadU(shapeBounds.maximum);	
	const Vec4V boundMinX = V4SplatElement<0>(Vec4V_From_Vec3V(boundMin));
	const Vec4V boundMinY = V4SplatElement<1>(Vec4V_From_Vec3V(boundMin));
	const Vec4V boundMinZ = V4SplatElement<2>(Vec4V_From_Vec3V(boundMin));
	const Vec4V boundMaxX = V4SplatElement<0>(Vec4V_From_Vec3V(boundMax));
	const Vec4V boundMaxY = V4SplatElement<1>(Vec4V_From_Vec3V(boundMax));
	const Vec4V boundMaxZ = V4SplatElement<2>(Vec4V_From_Vec3V(boundMax));

	PxsParticleCollDataV4 collDataV4;	

	const VecU32V u4Zero = VecU32VLoadXYZW(0,0,0,0);
	const VecU32V u4One = VecU32VLoadXYZW(1,1,1,1);
	PX_ALIGN(16, PxsParticleCollData fakeCsd);
	fakeCsd.localOldPos = PxVec3(FLT_MAX, FLT_MAX, FLT_MAX);
	fakeCsd.localNewPos = PxVec3(FLT_MAX, FLT_MAX, FLT_MAX);
	PX_ALIGN(16, PxU32 overlapArray[128]);

	PxU32 start = 0;
	while(start < numCollData)
	{
		const PxU32 batchSize = PxMin(numCollData-start, (PxU32)128);
		PxU32 v4Count = 0;
		PxsParticleCollData* particleCollDataIt = &particleCollData[start];
		for(PxU32 i=0; i<batchSize; i+=4)
		{				
			PxsParticleCollData* collData[4];
			collData[0] = particleCollDataIt++;
			collData[1] = (i+1 < numCollData) ? particleCollDataIt++ : &fakeCsd;
			collData[2] = (i+2 < numCollData) ? particleCollDataIt++ : &fakeCsd;
			collData[3] = (i+3 < numCollData) ? particleCollDataIt++ : &fakeCsd;

			Vec4V oldPosV0 = V4LoadU((PxF32*)&collData[0]->localOldPos);  
			Vec4V newPosV0 = V4LoadU((PxF32*)&collData[0]->localNewPos);
			Vec4V oldPosV1 = V4LoadU((PxF32*)&collData[1]->localOldPos);
			Vec4V newPosV1 = V4LoadU((PxF32*)&collData[1]->localNewPos);
			Vec4V oldPosV2 = V4LoadU((PxF32*)&collData[2]->localOldPos);
			Vec4V newPosV2 = V4LoadU((PxF32*)&collData[2]->localNewPos);
			Vec4V oldPosV3 = V4LoadU((PxF32*)&collData[3]->localOldPos);
			Vec4V newPosV3 = V4LoadU((PxF32*)&collData[3]->localNewPos);

			Vec4V particleMin0 = V4Min(oldPosV0, newPosV0);
			Vec4V particleMax0 = V4Max(oldPosV0, newPosV0);
			Vec4V particleMin1 = V4Min(oldPosV1, newPosV1);
			Vec4V particleMax1 = V4Max(oldPosV1, newPosV1);
			Vec4V particleMin2 = V4Min(oldPosV2, newPosV2);
			Vec4V particleMax2 = V4Max(oldPosV2, newPosV2);
			Vec4V particleMin3 = V4Min(oldPosV3, newPosV3);
			Vec4V particleMax3 = V4Max(oldPosV3, newPosV3);

			Mat44V particleMin44(particleMin0, particleMin1, particleMin2, particleMin3);
			const Mat44V particleMinTrans44 = M44Trnsps(particleMin44);
			Mat44V particleMax44(particleMax0, particleMax1, particleMax2, particleMax3);
			const Mat44V particleMaxTrans44 = M44Trnsps(particleMax44);

			BoolV mask = V4IsGrtr(boundMaxX, particleMinTrans44.col0); 
			mask = BAnd(V4IsGrtr(boundMaxY, particleMinTrans44.col1), mask); 
			mask = BAnd(V4IsGrtr(boundMaxZ, particleMinTrans44.col2), mask); 
			mask = BAnd(V4IsGrtr(particleMaxTrans44.col0, boundMinX), mask); 
			mask = BAnd(V4IsGrtr(particleMaxTrans44.col1, boundMinY), mask); 
			mask = BAnd(V4IsGrtr(particleMaxTrans44.col2, boundMinZ), mask); 

			VecU32V overlap4 = V4U32Sel(mask, u4One, u4Zero);
			V4U32StoreAligned(overlap4,(VecU32V*)&overlapArray[i]);
		}

		particleCollDataIt = &particleCollData[start];
		for(PxU32 k=0; k<batchSize; k++, ++particleCollDataIt)
		{
			if (overlapArray[k])
			{
				if(!scaledPlanes)
				{
					scalePlanes(scaledPlaneBuf, convexHullData, invScaling);
					scaledPlanes = true;
				}

				collDataV4.localOldPos[v4Count].v3 = particleCollDataIt->localOldPos;
				collDataV4.localNewPos[v4Count].v3 = particleCollDataIt->localNewPos;			
				collDataV4.localFlags[v4Count] = particleCollDataIt->localFlags;				
				collDataV4.restOffset[v4Count] = particleCollDataIt->restOffset;
				collDataV4.ccTime[v4Count] = particleCollDataIt->ccTime;
				collDataV4.collData[v4Count] = particleCollDataIt;
				v4Count++;
			}

			if(v4Count == 4  || (v4Count > 0 && (k == batchSize-1)))
			{
				collideWithConvexPlanesSIMD(collDataV4, scaledPlaneBuf, convexHullData->mNbPolygons, proxRadius);

				for(PxU32 j =0 ; j < v4Count; j++)
				{
					PxsParticleCollData* collData = collDataV4.collData[j];						
					PxU32 stateFlag = collDataV4.localFlags[j];
					if(stateFlag)
					{
						collData->localFlags |= stateFlag;
						collData->ccTime = collDataV4.ccTime[j];							
						collData->localSurfaceNormal = collDataV4.localSurfaceNormal[j].v3;
						collData->localSurfacePos = collDataV4.localSurfacePos[j].v3;
					}
				}										
				v4Count = 0;
			}
		}
		start += batchSize;

	}
#else
	PxsParticleCollData* particleCollDataIt = particleCollData;
	for(PxU32 i=0; i<numCollData; ++i, ++particleCollDataIt)
	{
		PxBounds3 particleBounds = PxBounds3::boundsOfPoints(particleCollDataIt->localOldPos, particleCollDataIt->localNewPos);

		if (particleBounds.intersects(shapeBounds))
		{
			if(!scaledPlanes)
			{
				scalePlanes(scaledPlaneBuf, convexHullData, invScaling);
				scaledPlanes = true;
			}

			collideWithConvexPlanes(*particleCollDataIt, scaledPlaneBuf, convexHullData->mNbPolygons, proxRadius);
		}
	}
#endif
}