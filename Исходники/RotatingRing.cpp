	//------------------------------------------------------------------------------------------------------
	void RotatingRing::CreateRing( const float& r )
	{
		float bs = 1.5 * r;
		m_BindBox = aabbox3df( vector3f( -bs, -bs, -bs ), vector3f( bs, bs, bs ) );
		m_isMaked = true;
		m_fRadius = r;
		ASSERT( 3 == RC_AXIS );
		VertexColor LineVertex[ RC_AXIS * RC_POINT ];
		for ( int i = 0; i < RC_POINT; i ++ )
		{
			Matrix22f m;
			m.FromRadian( (PI / 180) * i );
			vector2f v( r, 0 );
			v *= m;
			LineVertex[i].SetVertex( vector4f( v.m_x, 0, v.m_y, 1 ) );//Î§ÈÆyÖá
			LineVertex[i].SetColor( Color( 1, 0, 0, 1) );

			LineVertex[i+RC_POINT].SetVertex( vector4f( 0, v.m_x, v.m_y, 1 ) );//Î§ÈÆxÖá
			LineVertex[i+RC_POINT].SetColor( Color( 0, 1, 0, 1) );

			LineVertex[i+2*RC_POINT].SetVertex( vector4f( v.m_x, v.m_y, 0, 1 ) );//Î§ÈÆxÖá
			LineVertex[i+2*RC_POINT].SetColor( Color( 0, 0, 1, 1) );
		}
		m_pVertexBuffer->FlushVertexBuffer( RC_AXIS * RC_POINT, LineVertex );
	}