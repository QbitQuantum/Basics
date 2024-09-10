	void		Process(const btDbvtNode* leaf0,const btDbvtNode* leaf1)
	{
		m_numOverlapPairs++;


		int childIndex0 = leaf0->dataAsInt;
		int childIndex1 = leaf1->dataAsInt;
		

		btAssert(childIndex0>=0);
		btAssert(childIndex1>=0);


		const btCompoundShape* compoundShape0 = static_cast<const btCompoundShape*>(m_compound0ColObjWrap->getCollisionShape());
		btAssert(childIndex0<compoundShape0->getNumChildShapes());

		const btCompoundShape* compoundShape1 = static_cast<const btCompoundShape*>(m_compound1ColObjWrap->getCollisionShape());
		btAssert(childIndex1<compoundShape1->getNumChildShapes());

		const btCollisionShape* childShape0 = compoundShape0->getChildShape(childIndex0);
		const btCollisionShape* childShape1 = compoundShape1->getChildShape(childIndex1);

		//backup
		btTransform	orgTrans0 = m_compound0ColObjWrap->getWorldTransform();
		const btTransform& childTrans0 = compoundShape0->getChildTransform(childIndex0);
		btTransform	newChildWorldTrans0 = orgTrans0*childTrans0 ;
		
		btTransform	orgTrans1 = m_compound1ColObjWrap->getWorldTransform();
		const btTransform& childTrans1 = compoundShape1->getChildTransform(childIndex1);
		btTransform	newChildWorldTrans1 = orgTrans1*childTrans1 ;
		

		//perform an AABB check first
		btVector3 aabbMin0,aabbMax0,aabbMin1,aabbMax1;
		childShape0->getAabb(newChildWorldTrans0,aabbMin0,aabbMax0);
		childShape1->getAabb(newChildWorldTrans1,aabbMin1,aabbMax1);
		
		if (gCompoundCompoundChildShapePairCallback)
		{
			if (!gCompoundCompoundChildShapePairCallback(childShape0,childShape1))
				return;
		}

		if (TestAabbAgainstAabb2(aabbMin0,aabbMax0,aabbMin1,aabbMax1))
		{
			btCollisionObjectWrapper compoundWrap0(this->m_compound0ColObjWrap,childShape0, m_compound0ColObjWrap->getCollisionObject(),newChildWorldTrans0,-1,childIndex0);
			btCollisionObjectWrapper compoundWrap1(this->m_compound1ColObjWrap,childShape1,m_compound1ColObjWrap->getCollisionObject(),newChildWorldTrans1,-1,childIndex1);
			

			btSimplePair* pair = m_childCollisionAlgorithmCache->findPair(childIndex0,childIndex1);

			btCollisionAlgorithm* colAlgo = 0;

			if (pair)
			{
				colAlgo = (btCollisionAlgorithm*)pair->m_userPointer;
				
			} else
			{
				colAlgo = m_dispatcher->findAlgorithm(&compoundWrap0,&compoundWrap1,m_sharedManifold);
				pair = m_childCollisionAlgorithmCache->addOverlappingPair(childIndex0,childIndex1);
				btAssert(pair);
				pair->m_userPointer = colAlgo;
			}

			btAssert(colAlgo);
						
			const btCollisionObjectWrapper* tmpWrap0 = 0;
			const btCollisionObjectWrapper* tmpWrap1 = 0;

			tmpWrap0 = m_resultOut->getBody0Wrap();
			tmpWrap1 = m_resultOut->getBody1Wrap();

			m_resultOut->setBody0Wrap(&compoundWrap0);
			m_resultOut->setBody1Wrap(&compoundWrap1);

			m_resultOut->setShapeIdentifiersA(-1,childIndex0);
			m_resultOut->setShapeIdentifiersB(-1,childIndex1);


			colAlgo->processCollision(&compoundWrap0,&compoundWrap1,m_dispatchInfo,m_resultOut);
			
			m_resultOut->setBody0Wrap(tmpWrap0);
			m_resultOut->setBody1Wrap(tmpWrap1);
			


		}
	}