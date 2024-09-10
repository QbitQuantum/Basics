void Player_SID::initMusic(int songResIndex) { // $7de6
	unlockResource(resID_song);

	resID_song = songResIndex;
	_music = getResource(resID_song);
	if (_music == NULL) {
		return;
	}

	// song base address
	uint8* songFileDataPtr = _music;
	actSongFileData = _music;

	initializing = true;
	_soundInQueue = false;
	isMusicPlaying = false;

	unlockCodeLocation();
	resetPlayerState();

	lockResource(resID_song);
	buildStepTbl(songFileDataPtr[5]);

	// fetch sound
	songChannelBits = songFileDataPtr[4];
	for (int i = 2; i >= 0; --i) {
		if ((songChannelBits & BITMASK[i]) != 0) {
			func_7eae(i, songFileDataPtr);
		}
	}

	isMusicPlaying = true;
	lockCodeLocation();

	SIDReg23 &= 0xf0;
	SID_Write(23, SIDReg23);

	handleMusicBuffer();

	initializing = false;
	_soundInQueue = true;
}