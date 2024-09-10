void VISFile::load(Common::SeekableReadStream &vis) {
	clear();

	Common::StreamTokenizer tokenizer(Common::StreamTokenizer::kRuleIgnoreAll);
	tokenizer.addSeparator(' ');
	tokenizer.addChunkEnd('\n');
	tokenizer.addIgnore('\r');

	for (;;) {
		std::vector<Common::UString> strings;
		tokenizer.getTokens(vis, strings);

		// Make sure we don't get any empty lines
		while (!vis.eos() && !vis.err() && strings.empty()) {
			tokenizer.nextChunk(vis);
			tokenizer.getTokens(vis, strings);
		}

		if (vis.eos() || vis.err())
			break;

		if ((strings.size() == 1) && (strings[0] == "[Adjacent]"))
			// TODO: New in Jade Empire
			break;

		if (strings.size() > 2)
			throw Common::Exception("Malformed VIS file");

		Common::UString room = strings[0];
		std::vector<Common::UString> visibilityArray;

		int roomCount = 0;
		if (strings.size() > 1)
			roomCount = atoi(strings[1].c_str());

		room.tolower();

		int realRoomCount = 0;

		visibilityArray.reserve(roomCount);
		while (!vis.eos() && !vis.err()) {
			uint32 lineStart = vis.pos();

			tokenizer.nextChunk(vis);

			if (((char) vis.readByte()) != ' ') {
				// Not indented => new room

				vis.seek(lineStart);
				break;
			}

			tokenizer.getTokens(vis, strings);

			if (strings.size() != 1) {
				// More than one token => new room

				vis.seek(lineStart);
				break;
			}

			visibilityArray.push_back(strings[0]);
			realRoomCount++;
		}

		if (roomCount != realRoomCount)
			// Thanks, BioWare! -.-
			warning("Malformed VIS file. Wanted %d rooms, got %d?!?", roomCount, realRoomCount);

		if (!visibilityArray.empty())
			_map[room] = visibilityArray;
	}
}