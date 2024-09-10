void btContinuousConvexCollision::computeClosestPoints( const btTransform& transA, const btTransform& transB,btPointCollector& pointCollector)
{
	if (m_convexB1)
	{
		m_simplexSolver->reset();
		btGjkPairDetector gjk(m_convexA,m_convexB1,m_convexA->getShapeType(),m_convexB1->getShapeType(),m_convexA->getMargin(),m_convexB1->getMargin(),m_simplexSolver,m_penetrationDepthSolver);		
		btGjkPairDetector::ClosestPointInput input;
		input.m_transformA = transA;
		input.m_transformB = transB;
		gjk.getClosestPoints(input,pointCollector,0);
	} else
	{
		//convex versus plane
		const btConvexShape* convexShape = m_convexA;
		const btStaticPlaneShape* planeShape = m_planeShape;
		
		bool hasCollision = false;
		const btVector3& planeNormal = planeShape->getPlaneNormal();
		const btScalar& planeConstant = planeShape->getPlaneConstant();
		
		btTransform convexWorldTransform = transA;
		btTransform convexInPlaneTrans;
		convexInPlaneTrans= transB.inverse() * convexWorldTransform;
		btTransform planeInConvex;
		planeInConvex= convexWorldTransform.inverse() * transB;
		
		btVector3 vtx = convexShape->localGetSupportingVertex(planeInConvex.getBasis()*-planeNormal);

		btVector3 vtxInPlane = convexInPlaneTrans(vtx);
		btScalar distance = (planeNormal.dot(vtxInPlane) - planeConstant);

		btVector3 vtxInPlaneProjected = vtxInPlane - distance*planeNormal;
		btVector3 vtxInPlaneWorld = transB * vtxInPlaneProjected;
		btVector3 normalOnSurfaceB = transB.getBasis() * planeNormal;

		pointCollector.addContactPoint(
			normalOnSurfaceB,
			vtxInPlaneWorld,
			distance);
	}
}