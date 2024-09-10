	virtual void processTriangle( btVector3* triangle,int partId, int triangleIndex)
	{
		(void)partId;
		(void)triangleIndex;
		for (int i=0;i<3;i++)
		{
			btScalar dot = m_supportVecLocal.dot(triangle[i]);
			if (dot > m_maxDot)
			{
				m_maxDot = dot;
				m_supportVertexLocal = triangle[i];
			}
		}
	}