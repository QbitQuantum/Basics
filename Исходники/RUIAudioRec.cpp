void RUIAudio::RecordClose()
{
	Stop();
	HWAVEIN hTemp = m_hWaveIn;
	m_hWaveIn = NULL;
	if (hTemp == NULL)
		return;

	RUIBuffer*	pRUIBuffer = m_RecBufferList.GetFirst();
	while (pRUIBuffer != NULL)
	{
		RecRemoveBuffer(pRUIBuffer);

		pRUIBuffer = m_RecBufferList.GetNext(pRUIBuffer);
	}

	if( hTemp == NULL )
		return;

	if (waveInReset(hTemp) != MMSYSERR_NOERROR)
		ASSERT(FALSE);

	if (waveInClose(hTemp) != MMSYSERR_NOERROR)
		ASSERT(FALSE);
}