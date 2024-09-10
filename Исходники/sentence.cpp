// This is a compressed save of just the data needed to drive phonemes in the engine (no word / sentence text, etc )
//-----------------------------------------------------------------------------
// Purpose: 
// Input  : buf - 
//-----------------------------------------------------------------------------
void CSentence::CacheSaveToBuffer( CUtlBuffer& buf, int version )
{
	Assert( !buf.IsText() );
	Assert( m_bIsCached );

	int i;
	unsigned short pcount = GetRuntimePhonemeCount();

	// header
	if ( version == CACHED_SENTENCE_VERSION_ALIGNED )
	{
		buf.PutChar( version );
		buf.PutChar( 0 );
		buf.PutChar( 0 );
		buf.PutChar( 0 );
		buf.PutInt( pcount );
	}
	else
	{
		buf.PutChar( version );
		buf.PutShort( pcount );
	}

	// phoneme
	if ( version == CACHED_SENTENCE_VERSION_ALIGNED )
	{
		for ( i = 0; i < pcount; ++i )
		{
			const CBasePhonemeTag *phoneme = GetRuntimePhoneme( i );
			Assert( phoneme );
			buf.PutInt( phoneme->GetPhonemeCode() );
			buf.PutFloat( phoneme->GetStartTime() );
			buf.PutFloat( phoneme->GetEndTime() );
		}
	}
	else
	{
		for ( i = 0; i < pcount; ++i )
		{
			const CBasePhonemeTag *phoneme = GetRuntimePhoneme( i );
			Assert( phoneme );
			buf.PutShort( phoneme->GetPhonemeCode() );
			buf.PutFloat( phoneme->GetStartTime() );
			buf.PutFloat( phoneme->GetEndTime() );
		}
	}

	// emphasis samples and voice duck
	int c = m_EmphasisSamples.Count();
	Assert( c <= 32767 );

	if ( version == CACHED_SENTENCE_VERSION_ALIGNED )
	{
		buf.PutInt( c );
		for ( i = 0; i < c; i++ )
		{
			CEmphasisSample *sample = &m_EmphasisSamples[i];
			Assert( sample );
			buf.PutFloat( sample->time );
			buf.PutFloat( sample->value );
		}
		buf.PutInt( GetVoiceDuck() ? 1 : 0 );
	}
	else
	{
		buf.PutShort( c );
		for ( i = 0; i < c; i++ )
		{
			CEmphasisSample *sample = &m_EmphasisSamples[i];
			Assert( sample );
			buf.PutFloat( sample->time );
			short scaledValue = clamp( (short)( sample->value * 32767 ), (short)0, (short)32767 );
			buf.PutShort( scaledValue );
		}
		buf.PutChar( GetVoiceDuck() ? 1 : 0 );
	}
}