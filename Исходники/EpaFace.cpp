bool EpaFace::CalculatePlane()
{
	assert( ( m_pVertices[ 0 ] && m_pVertices[ 1 ] && m_pVertices[ 2 ] )
			&& "Must setup vertices pointers first!" );

	// Traditional method

	const btVector3 v1 = m_pVertices[ 1 ]->m_point - m_pVertices[ 0 ]->m_point;
	const btVector3 v2 = m_pVertices[ 2 ]->m_point - m_pVertices[ 0 ]->m_point;

	m_planeNormal = v2.cross( v1 );

	if ( m_planeNormal.length2() == 0 )
	{
		return false;
	}

	m_planeNormal.normalize();

	m_planeDistance = m_pVertices[ 0 ]->m_point.dot( -m_planeNormal );

	// Robust method

	//btVector3 _v1 = m_pVertices[ 1 ]->m_point - m_pVertices[ 0 ]->m_point;
	//btVector3 _v2 = m_pVertices[ 2 ]->m_point - m_pVertices[ 0 ]->m_point;

	//btVector3 n;

	//n = _v2.cross( _v1 );

	//_v1 = m_pVertices[ 0 ]->m_point - m_pVertices[ 1 ]->m_point;
	//_v2 = m_pVertices[ 2 ]->m_point - m_pVertices[ 1 ]->m_point;

	//n += ( _v1.cross( _v2 ) );

	//_v1 = m_pVertices[ 0 ]->m_point - m_pVertices[ 2 ]->m_point;
	//_v2 = m_pVertices[ 1 ]->m_point - m_pVertices[ 2 ]->m_point;

	//n += ( _v2.cross( _v1 ) );

	//n /= 3;	
	//n.normalize();

	//btVector3 c = ( m_pVertices[ 0 ]->m_point + m_pVertices[ 1 ]->m_point + m_pVertices[ 2 ]->m_point ) / 3;
	//btScalar d  = c.dot( -n );

	//m_robustPlaneNormal   = n;
	//m_robustPlaneDistance = d;

	// Compare results from both methods and check whether they disagree

	//if ( d < 0 )
	//{
	//	assert( ( m_planeDistance < 0 ) && "He he! Busted!" );
	//}
	//else
	//{
	//	assert( ( m_planeDistance >= 0 ) && "He he! Busted!" );
	//}

	return true;
}