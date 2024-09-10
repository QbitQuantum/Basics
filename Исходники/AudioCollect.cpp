void CAudioCollect::Stop()
{
	bStart = false;
	bReset = true;
	waveOutReset(m_hWaveOut);
	waveOutClose(m_hWaveOut);
	waveInReset(m_hWaveIn);
	waveInClose(m_hWaveIn);
}