MStatus sgHair_controlJoint::setGravityJointPositionWorld()
{
	MStatus status;

	m_mtxArrGravityAdd = m_mtxArrBase;

	if( m_weightGravity == 0 ) return MS::kSuccess;

	if( !m_bStaticRotation )
	{
		double minParam = m_paramGravity - m_rangeGravity;
		double maxParam = m_paramGravity;
		double divRate = maxParam - minParam;
		if( divRate == 0 ) divRate = 0.0001;

		if( minParam > m_mtxArrBase.length()-1 ) return MS::kSuccess;
		MDoubleArray dArrGravityWeights;
		dArrGravityWeights.setLength( m_mtxArrBase.length() );

		double beforeWeight = 1.0;
		for( int i= m_mtxArrBase.length()-1; i > minParam, i >= 0; i-- )
		{
			double paramRate = ( i - minParam ) / divRate;
			if( paramRate > 1 ) paramRate = 1.0;
			else if( paramRate < 0 ) paramRate = 0.0;
			double cuRate = beforeWeight - paramRate;
			if( cuRate < 0 ) cuRate = 0;
			dArrGravityWeights[i] = cuRate * m_weightGravity;
			beforeWeight = paramRate;
		}

		MMatrix mtxDefault;
		MMatrix mtxMult;

		for( int i= m_mtxArrBase.length()-1; i > minParam, i >= 0; i-- )
		{
			if( dArrGravityWeights[i] == 0 ) continue;
			double weight = dArrGravityWeights[i];

			mtxDefault( 3,0 ) = m_mtxArrBase[i]( 3,0 );
			mtxDefault( 3,1 ) = m_mtxArrBase[i]( 3,1 );
			mtxDefault( 3,2 ) = m_mtxArrBase[i]( 3,2 );

			mtxMult = getAngleWeightedMatrix( m_mtxGravityOffset, weight );
			mtxMult( 3,0 ) = m_mtxArrBase[i]( 3,0 );
			mtxMult( 3,1 ) = m_mtxArrBase[i]( 3,1 );
			mtxMult( 3,2 ) = m_mtxArrBase[i]( 3,2 );

			mtxMult = mtxDefault.inverse() * mtxMult;

			for( int j=i; j< m_mtxArrBase.length(); j++ )
			{
				m_mtxArrGravityAdd[j] *= mtxMult;
			}
		}
	}
	else
	{
		double minParam = m_paramGravity - m_rangeGravity;
		double maxParam = m_paramGravity;
		double divRate = maxParam - minParam;
		if( divRate == 0 ) divRate = 0.0001;

		MDoubleArray dArrGravityWeights;
		dArrGravityWeights.setLength( m_mtxArrBase.length() );

		double weight;
		for( int i= 0; i < m_mtxArrBase.length(); i++ )
		{
			if( i < minParam )weight=0;
			else weight = (i-minParam)/divRate;
			if( weight > 1 ) weight = 1;
			m_mtxArrGravityAdd[i] = m_mtxArrBase[i];

			double invWeight = 1-weight;
			MMatrix mtx = weight * m_mtxGravityOffset*m_mtxArrBase[i] + invWeight * m_mtxArrBase[i]; 

			cleanMatrix( mtx );

			m_mtxArrGravityAdd[i] = mtx;
			m_mtxArrGravityAdd[i]( 3,0 ) = m_mtxArrBase[i]( 3,0 );
			m_mtxArrGravityAdd[i]( 3,1 ) = m_mtxArrBase[i]( 3,1 );
			m_mtxArrGravityAdd[i]( 3,2 ) = m_mtxArrBase[i]( 3,2 );
		}
		cout << endl;
	}
	return MS::kSuccess;
}