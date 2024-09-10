unsigned int WINAPI MaoVoice::Play(PVOID para)
{
	MaoVoice * me = (MaoVoice*)para;

	HWAVEOUT hWaveOut;
	WAVEFORMATEX wavform;
	wavform.wFormatTag = WAVE_FORMAT_PCM;
	wavform.nChannels = Channels;
	wavform.nSamplesPerSec = Sample_Rate;
	wavform.nAvgBytesPerSec = Sample_Rate * Quantize_Bits * Channels / 8;
	wavform.nBlockAlign = Channels * Quantize_Bits / 8;
	wavform.wBitsPerSample = Quantize_Bits;
	wavform.cbSize = 0;


	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wavform, (DWORD_PTR)MaoVoice::waveOutProc, 0, CALLBACK_FUNCTION);

	char * buf = NULL;
	WAVEHDR wavhdr;
	while (true)
	{
		if (true == me->needRelease)
		{
			break;
		}
		else if (true == me->canPLAY)
		{
			EnterCriticalSection(&me->playBufCritical);
			if (false == me->playBufQueue.empty())
			{
				buf = me->playBufQueue.front();
				me->playBufQueue.pop();
				LeaveCriticalSection(&me->playBufCritical);
			}
			else
			{
				LeaveCriticalSection(&me->playBufCritical);
				Sleep(1);
				continue;
			}

			wavhdr.dwBufferLength = BUFFER_SIZE;
			wavhdr.lpData = buf;
			wavhdr.dwFlags = 0;
			wavhdr.dwLoops = 0;
			waveOutPrepareHeader(hWaveOut, &wavhdr, sizeof(WAVEHDR));

			/* ·ÅÒô */

			waveOutWrite(hWaveOut, &wavhdr, sizeof(WAVEHDR));
		}
		else
			Sleep(1);
	}

	waveOutReset(hWaveOut);
	waveOutClose(hWaveOut);

	return 0;
}