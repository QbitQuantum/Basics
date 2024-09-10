void CCompiledKeyValuesWriter::WriteData( CUtlBuffer& buf )
{
	int c = m_Data.Count();
	buf.PutInt( c );
	for ( int i = 0; i < c; ++i )
	{
		KVInfo_t &info = m_Data[ i ];
		buf.PutShort( info.key );
		buf.PutShort( info.value );
		buf.PutShort( info.GetParent() );
		buf.PutChar( info.IsSubTree() ? 1 : 0 );
	}
}