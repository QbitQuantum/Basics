	void	ProcessChildShape(btCollisionShape* childShape,int index)
	{
		
		btCompoundShape* compoundShape = static_cast<btCompoundShape*>(m_compoundColObj->getCollisionShape());


		//backup
		btTransform	orgTrans = m_compoundColObj->getWorldTransform();
		btTransform	orgInterpolationTrans = m_compoundColObj->getInterpolationWorldTransform();
		const btTransform& childTrans = compoundShape->getChildTransform(index);
		btTransform	newChildWorldTrans = orgTrans*childTrans ;

		//perform an AABB check first
		btVector3 aabbMin0,aabbMax0,aabbMin1,aabbMax1;
		childShape->getAabb(newChildWorldTrans,aabbMin0,aabbMax0);
		m_otherObj->getCollisionShape()->getAabb(m_otherObj->getWorldTransform(),aabbMin1,aabbMax1);

		if (TestAabbAgainstAabb2(aabbMin0,aabbMax0,aabbMin1,aabbMax1))
		{

			m_compoundColObj->setWorldTransform( newChildWorldTrans);
			m_compoundColObj->setInterpolationWorldTransform(newChildWorldTrans);

			//the contactpoint is still projected back using the original inverted worldtrans
			btCollisionShape* tmpShape = m_compoundColObj->getCollisionShape();
			m_compoundColObj->internalSetTemporaryCollisionShape( childShape );

			if (!m_childCollisionAlgorithms[index])
				m_childCollisionAlgorithms[index] = m_dispatcher->findAlgorithm(m_compoundColObj,m_otherObj,m_sharedManifold);

			///detect swapping case
			if (m_resultOut->getBody0Internal() == m_compoundColObj)
			{
				m_resultOut->setShapeIdentifiersA(-1,index);
			} else
			{
				m_resultOut->setShapeIdentifiersB(-1,index);
			}

			m_childCollisionAlgorithms[index]->processCollision(m_compoundColObj,m_otherObj,m_dispatchInfo,m_resultOut);
			if (m_dispatchInfo.m_debugDraw && (m_dispatchInfo.m_debugDraw->getDebugMode() & btIDebugDraw::DBG_DrawAabb))
			{
				btVector3 worldAabbMin,worldAabbMax;
				m_dispatchInfo.m_debugDraw->drawAabb(aabbMin0,aabbMax0,btVector3(1,1,1));
				m_dispatchInfo.m_debugDraw->drawAabb(aabbMin1,aabbMax1,btVector3(1,1,1));
			}
			
			//revert back transform
			m_compoundColObj->internalSetTemporaryCollisionShape( tmpShape);
			m_compoundColObj->setWorldTransform(  orgTrans );
			m_compoundColObj->setInterpolationWorldTransform(orgInterpolationTrans);
		}
	}