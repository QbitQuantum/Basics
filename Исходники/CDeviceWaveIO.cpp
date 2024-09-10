tbool CDeviceWaveIO::Start()
{
	if ((mpCallback) && (mppfOutputs) && (mppfInputs) && (!mbStarted)) {
		mbBlocked_volatile = false;

		WAVEFORMATEX format;
		InitFormat(format, (tint32)mfSampleRate);
		// Open driver - will invoke waveOutProc_static with uMsg == WOM_OPEN
		MMRESULT mmres = MMSYSERR_ERROR; // Default => unspecified error
		if (mbOutput) {
			mmres = waveOutOpen(
				&mhandle_out,
				muiDevIndex,
				&format,
				(DWORD)&waveOutProc_static,
				(DWORD)this,
				CALLBACK_FUNCTION
			);
		}
		if (mbInput) {
			mmres = waveInOpen(
				&mhandle_in,
				muiDevIndex,
				&format,
				(DWORD)&waveInProc_static,
				(DWORD)this,
				CALLBACK_FUNCTION
			);
		}
		/*
MMSYSERR_ALLOCATED Specified resource is already allocated. 
MMSYSERR_BADDEVICEID Specified device identifier is out of range. 
MMSYSERR_NODRIVER No device driver is present. 
MMSYSERR_NOMEM Unable to allocate or lock memory. 
WAVERR_BADFORMAT 
		*/
		if (mmres == MMSYSERR_NOERROR) {
			mmres = StartBuffers();
		}
		mbStarted = (mmres == MMSYSERR_NOERROR);
		if (!mbStarted)
			mbBlocked_volatile = true;
	}

	return mbStarted;
} // Start