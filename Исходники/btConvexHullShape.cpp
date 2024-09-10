btVector3	btConvexHullShape::localGetSupportingVertexWithoutMargin(const btVector3& vec)const
{
	btVector3 supVec(btScalar(0.),btScalar(0.),btScalar(0.));
	btScalar newDot,maxDot = btScalar(-BT_LARGE_FLOAT);

	for (int i=0;i<m_unscaledPoints.size();i++)
	{
		btVector3 vtx = m_unscaledPoints[i] * m_localScaling;

		newDot = vec.dot(vtx);
		if (newDot > maxDot)
		{
			maxDot = newDot;
			supVec = vtx;
		}
	}
	return supVec;
}