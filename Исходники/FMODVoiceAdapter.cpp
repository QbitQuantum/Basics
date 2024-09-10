void FMODVoiceAdapter::UpdateSound(bool isRec)
{
	FMOD_RESULT fmodErr;
	unsigned int soundLength;
	const int sampleSize = 2;

	FMOD::Sound *snd = (isRec) ? recSound : sound;
	unsigned int& lastPos = (isRec) ? lastRecordingPos : lastPlayPos;

	// get current Play or recording position
	unsigned int currPos;
	if (isRec){
		fmodErr=fmodSystem->getRecordPosition(0,&currPos);
		RakAssert(fmodErr==FMOD_OK);
	} else {
		fmodErr=channel->getPosition(&currPos, FMOD_TIMEUNIT_PCM);
		RakAssert(fmodErr==FMOD_OK);
	}

	// Get length of sound in samples
	fmodErr=snd->getLength(&soundLength, FMOD_TIMEUNIT_PCM);
	RakAssert(fmodErr==FMOD_OK);

	// calculate some variables we'll need ahead
	int bufferSizeBytes = rakVoice->GetBufferSizeBytes();

	// Round down the current position to a multiple of buffer size in samples
	currPos -= currPos % (bufferSizeBytes/sampleSize);

	if ( ((!isRec)||(isRec && !mute)) && (currPos != lastPos) ) 	
	{
		void *ptr1, *ptr2;
		unsigned int len1, len2;
		int blockLength;
	
		blockLength = (int)currPos - (int)lastPos;
		// Check for wrap around, and adjust
		if (blockLength < 0)
		{
			blockLength += soundLength;
		}

		// Lock to get access to the raw data
		snd->lock(lastPos * sampleSize, blockLength * sampleSize, &ptr1, &ptr2, &len1, &len2);

		//  Since the length and current position are both a multiple of bufferSizeBytes
		// just treat treat one full buffer at a time
		int numFrames = len1 / bufferSizeBytes;
		while(numFrames--){
			if (isRec) {
				BroadcastFrame(ptr1);
			} else {
				rakVoice->ReceiveFrame(ptr1);
			}
			ptr1 = (char*)ptr1 + bufferSizeBytes;
		}
		numFrames = len2 / bufferSizeBytes;
		while(numFrames--) {
			if (isRec){
				BroadcastFrame(ptr2);
			} else {
				rakVoice->ReceiveFrame(ptr2);
			}
			ptr2 = (char*)ptr2 + bufferSizeBytes;
		}

		snd->unlock(ptr1, ptr2, len1, len2);
	}

	lastPos = currPos;
}