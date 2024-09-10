	void TinyWaveOut::SendMessage(UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
	{
		waveOutMessage(hWaveOut, uMsg, dwParam1, dwParam2);
	}