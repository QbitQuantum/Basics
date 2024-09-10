bool	btGeometryUtil::areVerticesBehindPlane(const btVector3& planeNormal, const btAlignedObjectArray<btVector3>& vertices, btScalar	margin)
{
	int numvertices = vertices.size();
	for (int i=0;i<numvertices;i++)
	{
		const btVector3& N1 = vertices[i];
		btScalar dist = btScalar(planeNormal.dot(N1))+btScalar(planeNormal[3])-margin;
		if (dist>btScalar(0.))
		{
			return false;
		}
	}
	return true;
}