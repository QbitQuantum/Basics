void CChoreoChannel::SaveToBuffer( CUtlBuffer& buf, CChoreoScene *pScene, IChoreoStringPool *pStringPool )
{
	buf.PutShort( pStringPool->FindOrAddString( GetName() ) );

	int c = GetNumEvents();
	Assert( c <= 255 );
	buf.PutUnsignedChar( c );

	for ( int i = 0; i < c; i++ )
	{
		CChoreoEvent *e = GetEvent( i );
		Assert( e );
		e->SaveToBuffer( buf, pScene, pStringPool );
	}

	buf.PutChar( GetActive() ? 1 : 0 );
}