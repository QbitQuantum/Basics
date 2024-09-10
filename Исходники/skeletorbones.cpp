SkelMat4 skelBone_HoseRot::GetDirtyTransform( SkelMat4& myParentTM, SkelMat4& targetTM )
{
	SkelMat4 m;
	SkelMat4 invParentTM;
	SkelMat4 temp;
	SkelVec3 rotaxis;
	SkelVec3 targetup, targetaim;
	SkelVec3 upaxis, aimaxis;
	SkelVec3 tmp;
	SkelQuat targetQuat;
	float l, s, c;
	float angle, vScale;

	aimaxis = myParentTM[ 0 ];
	targetaim = targetTM[ 0 ];

	CrossProduct( targetaim, aimaxis, rotaxis );

	s = VectorLengthSquared( rotaxis );

	if( s == 0.0 ) {
		rotaxis.x = 1.0;
	} else if( s != 1.0 ) {
		l = 1.0 / sqrt( s );
		VectorScale( rotaxis, l, rotaxis );
	}

	s = DotProduct( aimaxis, targetaim );
	if( s < 1.0 ) {
		if( s > -0.999 ) {
			angle = acos( s );
		} else {
			angle = 6.2831855f;
		}
	} else {
		angle = 0.0;
	}

	vScale = angle * m_bendRatio;
	if( vScale > m_bendMax ) {
		vScale = m_bendMax;
	}

	temp[ 0 ][ 0 ] = myParentTM[ 0 ][ 0 ];
	temp[ 0 ][ 1 ] = myParentTM[ 1 ][ 0 ];
	temp[ 0 ][ 2 ] = myParentTM[ 2 ][ 0 ];
	temp[ 1 ][ 0 ] = myParentTM[ 0 ][ 1 ];
	temp[ 1 ][ 1 ] = myParentTM[ 1 ][ 1 ];
	temp[ 1 ][ 2 ] = myParentTM[ 2 ][ 1 ];
	temp[ 2 ][ 0 ] = myParentTM[ 0 ][ 2 ];
	temp[ 2 ][ 1 ] = myParentTM[ 1 ][ 2 ];
	temp[ 2 ][ 2 ] = myParentTM[ 2 ][ 2 ];
	temp[ 3 ][ 0 ] = -( myParentTM[ 0 ][ 0 ] * myParentTM[ 3 ][ 0 ] + myParentTM[ 0 ][ 1 ] * myParentTM[ 3 ][ 1 ] + myParentTM[ 0 ][ 2 ] * myParentTM[ 3 ][ 2 ] );
	temp[ 3 ][ 1 ] = -( myParentTM[ 1 ][ 0 ] * myParentTM[ 3 ][ 0 ] + myParentTM[ 1 ][ 1 ] * myParentTM[ 3 ][ 1 ] + myParentTM[ 1 ][ 2 ] * myParentTM[ 3 ][ 2 ] );
	temp[ 3 ][ 2 ] = -( myParentTM[ 2 ][ 0 ] * myParentTM[ 3 ][ 0 ] + myParentTM[ 2 ][ 1 ] * myParentTM[ 3 ][ 1 ] + myParentTM[ 2 ][ 2 ] * myParentTM[ 3 ][ 2 ] );

	m.Multiply( temp, myParentTM );

	VectorCopy( rotaxis, tmp );
	rotaxis[ 0 ] = tmp[ 0 ] * temp[ 0 ][ 0 ] + tmp[ 1 ] * temp[ 1 ][ 0 ] + tmp[ 2 ] * temp[ 2 ][ 0 ];
	rotaxis[ 1 ] = tmp[ 0 ] * temp[ 0 ][ 1 ] + tmp[ 1 ] * temp[ 1 ][ 1 ] + tmp[ 2 ] * temp[ 2 ][ 1 ];
	rotaxis[ 2 ] = tmp[ 0 ] * temp[ 0 ][ 2 ] + tmp[ 1 ] * temp[ 1 ][ 2 ] + tmp[ 2 ] * temp[ 2 ][ 2 ];

	targetaim.y = cos( vScale * 0.5 );
	targetup.y = rotaxis.x * targetaim.y;
	targetup.z = rotaxis.y * targetaim.y;
	targetaim.x = rotaxis.z * targetaim.y;

	c = cos( vScale * 0.5 );
	l = sqrt( 1.0 - c * c );

	m_cachedQuat[ 0 ] = rotaxis[ 0 ] * l;
	m_cachedQuat[ 1 ] = rotaxis[ 1 ] * l;
	m_cachedQuat[ 2 ] = rotaxis[ 2 ] * l;
	m_cachedQuat[ 3 ] = c;

	if( m_spinRatio < 1.0 )
	{
		m.Multiply( targetTM, temp );
		MatToQuat( m.val, targetQuat.val );
		Slerp( targetQuat, m_cachedQuat, m_spinRatio, &m_cachedQuat );
	}

	m_cachedQuat.GetMat4( m_cachedValue );
	VectorCopy( m_basePos, m_cachedValue[ 3 ] );

	m.Multiply( m_cachedValue, myParentTM );
	m_cachedValue = m;

	m_isDirty = false;

	return m_cachedValue;
}