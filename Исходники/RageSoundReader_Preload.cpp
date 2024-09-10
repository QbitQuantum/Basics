bool RageSoundReader_Preload::Open( RageSoundReader *pSource )
{
	ASSERT( pSource != NULL );
	m_iSampleRate = pSource->GetSampleRate();
	m_iChannels = pSource->GetNumChannels();
	m_fRate = pSource->GetStreamToSourceRatio();

	int iMaxSamples = g_iSoundPreloadMaxSamples.Get();
	
	/* Check the length, and see if we think it'll fit in the buffer. */
	int iLen = pSource->GetLength_Fast();
	if( iLen != -1 )
	{
		float fSecs = iLen / 1000.f;

		int iFrames = lrintf( fSecs * m_iSampleRate ); /* seconds -> frames */
		int iSamples = unsigned( iFrames * m_iChannels ); /* frames -> samples */
		if( iSamples > iMaxSamples )
			return false; /* Don't bother trying to preload it. */

		int iBytes = unsigned( iSamples * samplesize ); /* samples -> bytes */
		m_Buffer.Get()->reserve( iBytes );
	}

	for(;;)
	{
		/* If the rate changes, we won't preload it. */
		if( pSource->GetStreamToSourceRatio() != m_fRate )
		{
			return false; /* Don't bother trying to preload it. */
		}
		float buffer[1024];
		int iCnt = pSource->Read( buffer, ARRAYLEN(buffer) / m_iChannels );

		if( iCnt == END_OF_FILE )
		{
			break;
		}
		if( iCnt < 0 )
		{
			return false;
		}
		/* Add the buffer. */
		if( m_bBufferIs16Bit )
		{
			int16_t buffer16[1024];
			RageSoundUtil::ConvertFloatToNativeInt16( buffer, buffer16, iCnt*m_iChannels );
			m_Buffer.Get()->append( (char *) buffer16, (char *) (buffer16+iCnt*m_iChannels) );
		}
		else
		{
			m_Buffer.Get()->append( (char *) buffer, (char *) (buffer+iCnt*m_iChannels) );
		}

		if( m_Buffer.Get()->size() > iMaxSamples * samplesize )
		{
			return false; /* too big */
		}
	}

	m_iPosition = 0;
	delete pSource;
	return true;
}