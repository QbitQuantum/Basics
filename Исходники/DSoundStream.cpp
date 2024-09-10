int DSoundAudioBackend::RunThread() {
	if (FAILED(DirectSoundCreate8(0, &ds_, 0))) {
		ds_ = NULL;
		threadData_ = 2;
		return 1;
	}

	ds_->SetCooperativeLevel(window_, DSSCL_PRIORITY);
	if (!CreateBuffer()) {
		ds_->Release();
		ds_ = NULL;
		threadData_ = 2;
		return 1;
	}

	soundSyncEvent_ = CreateEvent(0, false, false, 0);
	InitializeCriticalSection(&soundCriticalSection);

	DWORD num1;
	short *p1;

	dsBuffer_->Lock(0, bufferSize_, (void **)&p1, &num1, 0, 0, 0);

	memset(p1, 0, num1);
	dsBuffer_->Unlock(p1, num1, 0, 0);
	totalRenderedBytes_ = -bufferSize_;

	setCurrentThreadName("DSound");
	currentPos_ = 0;
	lastPos_ = 0;

	dsBuffer_->Play(0,0,DSBPLAY_LOOPING);

	while (!threadData_) {
		EnterCriticalSection(&soundCriticalSection);

		dsBuffer_->GetCurrentPosition((DWORD *)&currentPos_, 0);
		int numBytesToRender = RoundDown128(ModBufferSize(currentPos_ - lastPos_)); 

		if (numBytesToRender >= 256) {
			int numBytesRendered = 4 * (*callback_)(realtimeBuffer_, numBytesToRender >> 2, 16, 44100, 2);
			//We need to copy the full buffer, regardless of what the mixer claims to have filled
			//If we don't do this then the sound will loop if the sound stops and the mixer writes only zeroes
			numBytesRendered = numBytesToRender;
			WriteDataToBuffer(lastPos_, (char *) realtimeBuffer_, numBytesRendered);

			currentPos_ = ModBufferSize(lastPos_ + numBytesRendered);
			totalRenderedBytes_ += numBytesRendered;

			lastPos_ = currentPos_;
		}

		LeaveCriticalSection(&soundCriticalSection);
		WaitForSingleObject(soundSyncEvent_, MAXWAIT);
	}