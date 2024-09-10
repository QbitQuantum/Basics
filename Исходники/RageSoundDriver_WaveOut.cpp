int64_t RageSoundDriver_WaveOut::GetPosition() const
{
	MMTIME tm;
	tm.wType = TIME_SAMPLES;
	MMRESULT ret = waveOutGetPosition( m_hWaveOut, &tm, sizeof(tm) );
  	if( ret != MMSYSERR_NOERROR )
		FAIL_M( wo_ssprintf(ret, "waveOutGetPosition failed") );

	return tm.u.sample;
}