 ///return true if it requires a dma transfer back
bool ManifoldResultAddContactPoint(const btVector3& normalOnBInWorld,
								   const btVector3& pointInWorld,
								   float depth,
								   btPersistentManifold* manifoldPtr,
								   btTransform& transA,
								   btTransform& transB,
									btScalar	combinedFriction,
									btScalar	combinedRestitution,
								   bool isSwapped)
{
	
	float contactTreshold = manifoldPtr->getContactBreakingThreshold();

	//spu_printf("SPU: add contactpoint, depth:%f, contactTreshold %f, manifoldPtr %llx\n",depth,contactTreshold,manifoldPtr);

#ifdef DEBUG_SPU_COLLISION_DETECTION
	spu_printf("SPU: contactTreshold %f\n",contactTreshold);
#endif //DEBUG_SPU_COLLISION_DETECTION
	if (depth > manifoldPtr->getContactBreakingThreshold())
		return false;

	//provide inverses or just calculate?
	btTransform transAInv = transA.inverse();//m_body0->m_cachedInvertedWorldTransform;
	btTransform transBInv= transB.inverse();//m_body1->m_cachedInvertedWorldTransform;

	btVector3 pointA;
	btVector3 localA;
	btVector3 localB;
	btVector3 normal;

	if (isSwapped)
	{
		normal = normalOnBInWorld * -1;
		pointA = pointInWorld + normal * depth;
		localA = transAInv(pointA );
		localB = transBInv(pointInWorld);
		/*localA = transBInv(pointA );
		localB = transAInv(pointInWorld);*/
	}
	else
	{
		normal = normalOnBInWorld;
		pointA = pointInWorld + normal * depth;
		localA = transAInv(pointA );
		localB = transBInv(pointInWorld);
	}

	btManifoldPoint newPt(localA,localB,normal,depth);

	int insertIndex = manifoldPtr->getCacheEntry(newPt);
	if (insertIndex >= 0)
	{
//		manifoldPtr->replaceContactPoint(newPt,insertIndex);
//		return true;

#ifdef DEBUG_SPU_COLLISION_DETECTION
		spu_printf("SPU: same contact detected, nothing done\n");
#endif //DEBUG_SPU_COLLISION_DETECTION
		// This is not needed, just use the old info! saves a DMA transfer as well
	} else
	{

		newPt.m_combinedFriction = combinedFriction;
		newPt.m_combinedRestitution = combinedRestitution;

		/*
		///@todo: SPU callbacks, either immediate (local on the SPU), or deferred
		//User can override friction and/or restitution
		if (gContactAddedCallback &&
			//and if either of the two bodies requires custom material
			 ((m_body0->m_collisionFlags & btCollisionObject::customMaterialCallback) ||
			   (m_body1->m_collisionFlags & btCollisionObject::customMaterialCallback)))
		{
			//experimental feature info, for per-triangle material etc.
			(*gContactAddedCallback)(newPt,m_body0,m_partId0,m_index0,m_body1,m_partId1,m_index1);
		}
		*/
		manifoldPtr->addManifoldPoint(newPt);
		return true;

	}
	return false;
	
}