bool BinkPlayer::loadFile(const Common::String &filename) {
	_fname = filename;

	if (_demo) {
		// The demo uses a .lab suffix
		_fname += ".lab";
		return MoviePlayer::loadFile(_fname);
	}

	_fname += ".m4b";

	Common::SeekableReadStream *stream = SearchMan.createReadStreamForMember(_fname);
	if (!stream) {
		warning("BinkPlayer::loadFile(): Can't create stream for: %s", _fname.c_str());
		return false;
	}

	// set the default start of the bink video in case there is no SMUSH header
	uint32 startBinkPos = 0x0;

	// clear existing subtitles
	_subtitles.clear();

	char header[6];
	// read the first 5 bytes of the header
	stream->read(header, 5);
	header[5] = 0;

	if (!strcmp(header, "SMUSH")) {
		// handle SMUSH header
		unsigned char smushHeader[0x2000];

		// read the first part
		uint32 consumed = 16;
		stream->read(smushHeader, consumed);

		// decode the first part
		for (unsigned int i = 0; i < consumed; i++) {
			smushHeader[i] ^= 0xd2;
		}

		Common::MemoryReadStream msStart(smushHeader, consumed);
		TextSplitter tsStart("", &msStart);

		// extract the length / the start of the following BINK header
		tsStart.scanString("%d", 1, &startBinkPos);

		assert(startBinkPos < sizeof(smushHeader));

		// read the rest (5 bytes less because of the string "SMUSH" at the beginning)
		stream->read(smushHeader+consumed, startBinkPos - consumed - 5);

		// decode the reset
		for (unsigned int i = consumed; i < startBinkPos - 5; i++) {
			smushHeader[i] ^= 0xd2;
		}
		consumed = startBinkPos - 5;

		Common::MemoryReadStream msSmush(smushHeader, consumed);
		TextSplitter tsSmush("", &msSmush);

		// skip the first line which contains the length
		tsSmush.nextLine();

		tsSmush.expectString("BEGINDATA");
		while (!tsSmush.checkString("ENDOFDATA")) {
			unsigned int start, end;
			char textId[256];

			// extract single subtitle entry
			tsSmush.scanString("%d\t%d\t%s", 3, &start, &end, textId);

			Subtitle st(start, end, textId);
			_subtitles.push_back(st);
		}
		tsSmush.expectString("ENDOFDATA");
	}

	// set current subtitle index to the first subtitle
	_subtitleIndex = _subtitles.begin();

	if (!bikCheck(stream, startBinkPos)) {
		warning("BinkPlayer::loadFile(): Could not find BINK header for: %s", _fname.c_str());
		delete stream;
		return false;
	}

	Common::SeekableReadStream *bink = nullptr;
	bink = new Common::SeekableSubReadStream(stream, startBinkPos, stream->size(), DisposeAfterUse::YES);
	_videoDecoder->setDefaultHighColorFormat(Graphics::PixelFormat(4, 8, 8, 8, 0, 8, 16, 24, 0));
	return _videoDecoder->loadStream(bink);
}