	//------------------------------------------------------------------------------------------------------
	void GridNode::MakeGrid( const vector3f& center, float size, int grids )
	{
		int Lines = (grids+1)*2;
		float addtion = size / grids;
		float begin = - size / 2;
		m_BindBox.Reset();
		m_BindBox.Contains( vector3f( center.m_x + begin, center.m_y, center.m_z + begin ) );
		m_BindBox.Contains( vector3f( center.m_x - begin, center.m_y, center.m_z - begin ) );
		VertexColor* linever = NEW VertexColor[Lines*2];
		for ( int i = 0 ; i < Lines / 2; i ++ )//×ÝÏß
		{
			if ( i == Lines / 4 )
			{
				linever[i*2].SetColor( Color(0,0,1,1) );
				linever[i*2+1].SetColor( Color(0,0,1,1) );
			}
			else
			{
				linever[i*2].SetColor( Color::White );
				linever[i*2+1].SetColor( Color::White );
			}
			linever[i*2].SetVertex( vector4f( 
				center.m_x+begin+addtion*i,
				center.m_y,
				center.m_z+begin
				) );
			linever[i*2+1].SetVertex( vector4f( 
				center.m_x+begin+addtion*i,
				center.m_y,
				center.m_z+begin+size
				) );
		}
		for ( int i = Lines / 2, j = 0 ; i < Lines ; i ++, j ++ )//×ÝÏß
		{
			if ( i == 3* Lines / 4 )
			{
				linever[i*2].SetColor( Color(1,0,0,1) );
				linever[i*2+1].SetColor( Color(1,0,0,1) );
			}
			else
			{
				linever[i*2].SetColor( Color::White );
				linever[i*2+1].SetColor( Color::White );
			}
			linever[i*2].SetVertex( vector4f( 
				center.m_x+begin,
				center.m_y,
				center.m_z+begin+addtion*j
				) );
			linever[i*2+1].SetVertex( vector4f( 
				center.m_x+begin+size,
				center.m_y,
				center.m_z+begin+addtion*j
				) );
		}
		vector<ushort> Indies;
		for ( int i = 0; i < Lines * 2; i ++ )
		{
			Indies.push_back(i);
		}
		m_pVertexBuffer->FlushVertexBuffer( Lines*2, linever );
		m_pIndicesBuffer->FlushIndiesBuffer( Indies.size(), &Indies[0] );
		SAFE_DELETE_ARRAY(linever);
	}