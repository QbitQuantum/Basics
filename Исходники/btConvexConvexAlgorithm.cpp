	virtual void addContactPoint(const btVector3& normalOnBInWorld, const btVector3& pointInWorld, btScalar orgDepth)
	{
		btVector3 endPt, startPt;
		btScalar newDepth;
		btVector3 newNormal;

		if (m_perturbA)
		{
			btVector3 endPtOrg = pointInWorld + normalOnBInWorld*orgDepth;
			endPt = (m_unPerturbedTransform*m_transformA.inverse())(endPtOrg);
			newDepth = (endPt -  pointInWorld).dot(normalOnBInWorld);
			startPt = endPt+normalOnBInWorld*newDepth;
		} else
		{
			endPt = pointInWorld + normalOnBInWorld*orgDepth;
			startPt = (m_unPerturbedTransform*m_transformB.inverse())(pointInWorld);
			newDepth = (endPt -  startPt).dot(normalOnBInWorld);
			
		}

#ifdef DEBUG_CONTACTS
		m_debugDrawer->drawLine(startPt, endPt, btVector3(1,0,0));
		m_debugDrawer->drawSphere(startPt,0.05, btVector3(0,1,0));
		m_debugDrawer->drawSphere(endPt,0.05, btVector3(0,0,1));
#endif //DEBUG_CONTACTS

		
		m_originalManifoldResult->addContactPoint(normalOnBInWorld, startPt, newDepth);
	}