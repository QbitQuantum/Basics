SoundLibrary2dWin32::~SoundLibrary2dWin32()
{
	waveOutReset(s_device);
	delete [] m_buffers;		m_buffers = NULL;
	waveOutClose(s_device);		s_device = NULL;
}