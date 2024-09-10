void Player_AD::saveLoadWithSerializer(Common::Serializer &s) {
	Common::StackLock lock(_mutex);

	if (s.getVersion() < VER(95)) {
		IMuse *dummyImuse = IMuse::create(_vm->_system, NULL, NULL);
		dummyImuse->saveLoadIMuse(s, _vm, false);
		delete dummyImuse;
		return;
	}

	if (s.getVersion() >= VER(96)) {
		int32 res[4] = {
			_musicResource, _sfx[0].resource, _sfx[1].resource, _sfx[2].resource
		};

		// The first thing we save is a list of sound resources being played
		// at the moment.
		s.syncArray(res, 4, Common::Serializer::Sint32LE);

		// If we are loading start the music again at this point.
		if (s.isLoading()) {
			if (res[0] != -1) {
				startSound(res[0]);
			}
		}

		uint32 musicOffset = _curOffset;

		s.syncAsSint32LE(_engineMusicTimer, VER(96));
		s.syncAsUint32LE(_musicTimer, VER(96));
		s.syncAsUint32LE(_internalMusicTimer, VER(96));
		s.syncAsUint32LE(_curOffset, VER(96));
		s.syncAsUint32LE(_nextEventTimer, VER(96));

		// We seek back to the old music position.
		if (s.isLoading()) {
			SWAP(musicOffset, _curOffset);
			musicSeekTo(musicOffset);
		}

		// Finally start up the SFX. This makes sure that they are not
		// accidently stopped while seeking to the old music position.
		if (s.isLoading()) {
			for (int i = 1; i < ARRAYSIZE(res); ++i) {
				if (res[i] != -1) {
					startSound(res[i]);
				}
			}
		}
	}
}