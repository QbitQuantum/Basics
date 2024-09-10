bool	btSubsimplexConvexCast::calcTimeOfImpact(
		const btTransform& fromA,
		const btTransform& toA,
		const btTransform& fromB,
		const btTransform& toB,
		CastResult& result)
{

	btMinkowskiSumShape combi(m_convexA,m_convexB);
	btMinkowskiSumShape* convex = &combi;

	btTransform	rayFromLocalA;
	btTransform	rayToLocalA;

	rayFromLocalA = fromA.inverse()* fromB;
	rayToLocalA = toA.inverse()* toB;


	m_simplexSolver->reset();

	convex->setTransformB(btTransform(rayFromLocalA.getBasis()));

	//btScalar radius = btScalar(0.01);

	btScalar lambda = btScalar(0.);
	//todo: need to verify this:
	//because of minkowski difference, we need the inverse direction
	
	btVector3 s = -rayFromLocalA.getOrigin();
	btVector3 r = -(rayToLocalA.getOrigin()-rayFromLocalA.getOrigin());
	btVector3 x = s;
	btVector3 v;
	btVector3 arbitraryPoint = convex->localGetSupportingVertex(r);
	
	v = x - arbitraryPoint;

	int maxIter = MAX_ITERATIONS;

	btVector3 n;
	n.setValue(btScalar(0.),btScalar(0.),btScalar(0.));
	bool hasResult = false;
	btVector3 c;

	btScalar lastLambda = lambda;


	btScalar dist2 = v.length2();
#ifdef BT_USE_DOUBLE_PRECISION
	btScalar epsilon = btScalar(0.0001);
#else
	btScalar epsilon = btScalar(0.0001);
#endif //BT_USE_DOUBLE_PRECISION
	btVector3	w,p;
	btScalar VdotR;
	
	while ( (dist2 > epsilon) && maxIter--)
	{
		p = convex->localGetSupportingVertex( v);
		 w = x - p;

		btScalar VdotW = v.dot(w);

		if ( VdotW > btScalar(0.))
		{
			VdotR = v.dot(r);

			if (VdotR >= -(SIMD_EPSILON*SIMD_EPSILON))
				return false;
			else
			{
				lambda = lambda - VdotW / VdotR;
				x = s + lambda * r;
				m_simplexSolver->reset();
				//check next line
				w = x-p;
				lastLambda = lambda;
				n = v;
				hasResult = true;
			}
		} 
		m_simplexSolver->addVertex( w, x , p);
		if (m_simplexSolver->closest(v))
		{
			dist2 = v.length2();
			hasResult = true;
			//printf("V=%f , %f, %f\n",v[0],v[1],v[2]);
			//printf("DIST2=%f\n",dist2);
			//printf("numverts = %i\n",m_simplexSolver->numVertices());
		} else
		{
			dist2 = btScalar(0.);
		} 
	}

	//int numiter = MAX_ITERATIONS - maxIter;
//	printf("number of iterations: %d", numiter);
	result.m_fraction = lambda;
	result.m_normal = n;

	return true;
}