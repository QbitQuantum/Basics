sint32 VDAudioOutputWaveOutW32::GetPositionBytes() {
	MMTIME mmtime;

	if (mCurState != kStatePlaying) return -1;

	mmtime.wType = TIME_BYTES;

	MMRESULT res;

	vdsynchronized(mcsWaveDevice) {
		res = waveOutGetPosition(mhWaveOut, &mmtime, sizeof mmtime);
	}

	if (MMSYSERR_NOERROR != res)
		return -1;

	switch(mmtime.wType) {
	case TIME_BYTES:
		return mmtime.u.cb;
	case TIME_MS:
		return MulDiv(mmtime.u.ms, mAvgBytesPerSec, 1000);
	case TIME_SAMPLES:
		return MulDiv(mmtime.u.sample, mAvgBytesPerSec, mSamplesPerSec);
	}

	return -1;
}