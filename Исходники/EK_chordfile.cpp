	int ChordFile::ReadChords(FILE* f) {
		char buf[LINE_BUFFER_LENGTH], keyBuf[NOTE_STRING_MAX_LENGTH];
		int totalBeats = 0, beats = 0;
		string chordStyle;
		while (!feof(f)) {
			while ((beats = ReadChord(f, buf, keyBuf, &chordStyle)) == -1);
			totalBeats += beats;
			if (chordStyle.empty())
				chordStyle = CHORDSTYLES_DEFAULT;
			Heap.Debug<Chord>("Pushing Chord");
			Chords.push_back(Chord(Key(keyBuf), beats, chordStyle));
		}
		return totalBeats;
	}