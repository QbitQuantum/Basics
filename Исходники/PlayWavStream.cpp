DWORD PlayWavStream::GetCurrentTime()
{
	DWORD dwResult = 0;

	m_mtWavOut.Lock();

	if (	m_pWavOut &&
			NULL != m_pWavOut->GetHwave() )
	{
		MMTIME		mmt;
		MMRESULT	mmr;

		mmt.wType = TIME_BYTES;

		mmr = waveOutGetPosition( m_pWavOut->GetHwave(), &mmt, sizeof( mmt ) ); 

		if ( m_WavFormat.nAvgBytesPerSec )
		{
			dwResult = (DWORD)( mmt.u.cb * 1000.0 / m_WavFormat.nAvgBytesPerSec );
		}
	}

	m_mtWavOut.Unlock();

	return dwResult;
} 