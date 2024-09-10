float MapManager::GetHeightByPosition( float x, float z )
{
	if ( !m_HeightMap )
	{
		return 0.0f;
	}
	
	x /= m_PixelSize;
	z /= m_PixelSize;
	x = static_cast<float>(m_HeightMapWidth) / 2.0f + x;
	z = static_cast<float>(m_HeightMapHeight) / 2.0f + z;
	
	int col = static_cast<int>( std::floor( x ) );
	int row = static_cast<int>( std::floor( z ) );
	
	col = __min( col, m_HeightMapWidth - 1 );
	row = __min( row, m_HeightMapHeight - 1 );
	col = __max( 0, col );
	row = __max( 0, row );

	float leftBottom = GetHeightInMap( col, row + 1 );
	float rightBottom = GetHeightInMap( col + 1, row + 1 );
	float leftTop = GetHeightInMap( col , row );
	float rightTop = GetHeightInMap( col + 1, row );

	float dx = x - col;
	float dz = z - row;
	
	if ( dx < 0 )
	{
		dx = -dx;
	}
	if ( dz < 0 )
	{
		dz = -dz;
	}

	float heightBottom = Lerp( leftBottom, rightBottom, dx );
	float heightTop = Lerp( leftTop, rightTop, dx );
	float height = Lerp( heightTop, heightBottom, dz );
	
	// Log( "(%x, %x) %4f %4f %4f %4f %4f %4f %4f \n",
	//	 col, row, leftBottom, rightBottom, leftTop, rightTop, heightBottom, heightTop, height);

	return height;
}