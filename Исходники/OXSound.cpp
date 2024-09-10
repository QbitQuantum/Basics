BOOL COXSound::GetCurrentPosition(MMTIME* pMMTime) const
{
	if(!m_hWaveOut)
	{
		return FALSE;
	}

	if(!IsPlaying())
	{
		return FALSE;
	}

	ASSERT(pMMTime != NULL);

	// Return time in milliseconds
	pMMTime->wType=TIME_MS;

	MMRESULT hResult;
	hResult=waveOutGetPosition(m_hWaveOut,pMMTime,sizeof(MMTIME));

	return (hResult==MMSYSERR_NOERROR);
}