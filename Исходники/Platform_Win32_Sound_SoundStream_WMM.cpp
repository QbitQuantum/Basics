void Platform_Win32_Sound_SoundStream_WMM::Play()
	{
	if (playing_)
		{
		return;
		}
	for (int i=0; i<WaveBlockCount; i++)
		{
        if(waveBlocks_[i].dwFlags & WHDR_PREPARED)
			{
			waveOutUnprepareHeader(hWaveOut_, &waveBlocks_[i], sizeof(WAVEHDR));
			}
		int bytesToWrite=WaveBlockSize-(int)(waveBlocks_[i].dwUser);
		int remainder=0;
		if (soundPosition_+bytesToWrite>size_)
			{
			int roomLeft=size_-soundPosition_;
			remainder=bytesToWrite-roomLeft;
			bytesToWrite=roomLeft;
			}
        memcpy(waveBlocks_[i].lpData+waveBlocks_[i].dwUser, static_cast<char*>(soundBuffer_)+soundPosition_,bytesToWrite);
		soundPosition_+=bytesToWrite;
		soundPosition_%=size_;
		if (remainder>0)
			{
	        memcpy(waveBlocks_[i].lpData+waveBlocks_[i].dwUser+bytesToWrite, static_cast<char*>(soundBuffer_)+soundPosition_,remainder);
			soundPosition_+=remainder;
			soundPosition_%=size_;
			}
        waveBlocks_[i].dwBufferLength = WaveBlockSize;
        waveOutPrepareHeader(hWaveOut_, &waveBlocks_[i], sizeof(WAVEHDR));
        waveOutWrite(hWaveOut_, &waveBlocks_[i], sizeof(WAVEHDR));

		EnterCriticalSection(&waveCriticalSection_);
        firstUsedWaveBlock_=0;
        LeaveCriticalSection(&waveCriticalSection_);
        lastUsedWaveBlock_=WaveBlockCount-1;
		}
	playing_=true;
	}