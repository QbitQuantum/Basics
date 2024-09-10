bool CWavePlay::CloseDevice()
{
	ZeroMemory(&m_wavformex,sizeof(WAVEFORMATEX)); 

	 while(_nWaveFreeBlockCount != 0 && _nWaveFreeBlockCount < BLOCK_COUNT)
        Sleep(10);

    /*
     * unprepare any blocks that are still prepared
     */
    for(int i = 0; i < _nWaveFreeBlockCount; i++)
	{
        if(_waveBlocks && _waveBlocks[i].dwFlags & WHDR_PREPARED)
		{
            waveOutUnprepareHeader(m_hWaveOut, &_waveBlocks[i], sizeof(WAVEHDR));
		}
	}
	if(_waveBlocks)
	{
		freeBlocks(_waveBlocks);
		_waveBlocks = NULL;
	}
	waveOutClose(m_hWaveOut);
	m_bPalyState = false; 
	return true;
}