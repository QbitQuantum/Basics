bool MeshCompiler::TraceMesh( const Segment& s )
{
	if( m_RawTris.Size() )
	{
		if( s.Intersects( m_AABB ) )
		{
			for( uint j = 0; j < m_RawTris.Size(); ++j )
			{
				if(	s.Intersects( m_RawTris[j] ) ||
					( m_TraceTriangleBacks && s.Intersects( m_RawTris[j].GetFlipped() ) ) )
				{
					return true;
				}
			}
		}
	}
	return false;
}