void CChoreoActor::SaveToBuffer( CUtlBuffer& buf, CChoreoScene *pScene )
{
	int i, c;
	buf.PutString( GetName() );

	c = GetNumChannels();
	buf.PutShort( c );
	for ( i = 0; i < c; i++ )
	{
		CChoreoChannel *channel = GetChannel( i );
		Assert( channel );
		channel->SaveToBuffer( buf, pScene );
	}

	/*
	if ( Q_strlen( a->GetFacePoserModelName() ) > 0 )
	{
		FilePrintf( buf, level + 1, "faceposermodel \"%s\"\n", a->GetFacePoserModelName() );
	}
	*/
	buf.PutChar( GetActive() ? 1 : 0 );
}