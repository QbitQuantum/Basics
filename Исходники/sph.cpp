void collisionWithBound(btVector3 &vel, btVector3 &pos, const btVector3 &normal, const btScalar &penetrationDist)
{
    if( penetrationDist < btScalar(0.0) )
	{
        
        pos = pos - normal * penetrationDist;
        
        vel = vel - (1 + Constant.m_boundaryRestitution * (-penetrationDist) / (Constant.m_timeStep * vel.length())) * vel.dot(normal) * normal;
	}
}