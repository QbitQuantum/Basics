int CPolyMesh3::CreatePM3( char* nameptr, int pointnum, int facenum, float facet, D3DXVECTOR3* pointptr, CMQOFace* faceptr, 
	map<int,CMQOMaterial*>& srcmat, D3DXMATRIX multmat )
{
	m_nameptr = nameptr;
	m_orgpointnum = pointnum;
	m_orgfacenum = facenum;
	m_mqoface = faceptr;
	m_pointbuf = pointptr;
	m_facet = facet;

	CallF( CreateN3PFromMQOFace( 0, &m_facenum ), return 1 );

	if( m_facenum <= 0 ){
		return 0;
	}
	
	int n3pnum = m_facenum * 3;

	m_n3p = (N3P*)malloc( sizeof( N3P ) * n3pnum );
	if( !m_n3p ){
		_ASSERT( 0 );
		return 1;
	}
	ZeroMemory( m_n3p, sizeof( N3P ) * n3pnum );

	int n3;
	for( n3 = 0; n3 < n3pnum; n3++ ){
		N3P* curn3p = m_n3p + n3;

		PERFACE* perface = (PERFACE*)malloc( sizeof( PERFACE ) );
		if( !perface ){
			_ASSERT( 0 );
			return 1;
		}
		ZeroMemory( perface, sizeof( PERFACE ) );

		PERVERT* pervert = (PERVERT*)malloc( sizeof( PERVERT ) );
		if( !pervert ){
			_ASSERT( 0 );
			return 1;
		}
		ZeroMemory( pervert, sizeof( PERVERT ) );

		N3SM* n3sm = (N3SM*)malloc( sizeof( N3SM ) );
		if( !n3sm ){
			_ASSERT( 0 );
			return 1;
		}
		ZeroMemory( n3sm, sizeof( N3SM ) );

		curn3p->perface = perface;
		curn3p->pervert = pervert;
		curn3p->n3sm = n3sm;
	}

	int tmpnum = 0;
	CallF( CreateN3PFromMQOFace( m_n3p, &tmpnum ), return 1 );
	if( tmpnum != m_facenum ){
		_ASSERT( 0 );
		return 1;
	}

//////////
	CallF( CalcOrgNormal(), return 1 );
	qsort_s( m_n3p, m_facenum * 3, sizeof( N3P ), sortfunc_material, (void*)this );
	CallF( SetSMFace(), return 1 );
	qsort_s( m_n3p, m_facenum * 3, sizeof( N3P ), sortfunc_order0, (void*)this );

///////////
	CallF( SetOptV( 0, &m_optleng, &m_optmatnum, srcmat ), return 1 );
	if( (m_optleng <= 0) || (m_optmatnum <= 0) ){
		_ASSERT( 0 );
		return 0;
	}
	m_dispv = (PM3DISPV*)malloc( sizeof( PM3DISPV ) * m_optleng );
	if( !m_dispv ){
		_ASSERT( 0 );
		return 1;
	}
	ZeroMemory( m_dispv, sizeof( PM3DISPV ) * m_optleng );
	m_matblock = (MATERIALBLOCK*)malloc( sizeof( MATERIALBLOCK ) * m_optmatnum );
	if( !m_matblock ){
		_ASSERT( 0 );
		return 1;
	}
	ZeroMemory( m_matblock, sizeof( MATERIALBLOCK ) * m_optmatnum );

	m_dispindex = (int*)malloc( sizeof( int ) * m_facenum * 3 );
	if( !m_dispindex ){
		_ASSERT( 0 );
		return 1;
	}
	ZeroMemory( m_dispindex, sizeof( int ) * m_facenum * 3 );

	int tmpleng, tmpmatnum;
	CallF( SetOptV( m_dispv, &tmpleng, &tmpmatnum, srcmat ), return 1 );
	if( (tmpleng != m_optleng) || (tmpmatnum != m_optmatnum) ){
		_ASSERT( 0 );
		return 1;
	}

	CallF( CalcBound(), return 1 );


	m_infbone = new CInfBone[ m_orgpointnum ];
	if( !m_infbone ){
		_ASSERT( 0 );
		return 1;
	}

	m_createoptflag = 1;

	return 0;
}