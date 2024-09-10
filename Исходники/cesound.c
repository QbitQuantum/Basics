void wince_sound_interrupt(void)
{
	int i;
	for (i = 0; i < NUM_WAVEHDRS; i++)
		waveOutBreakLoop(This.m_hWaveOut);
}