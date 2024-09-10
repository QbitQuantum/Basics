void MidiParser::mergeMidiEventLists(QVector<MidiEventList> &trackList) {
	int totalEventCount = 0;

	// Remove empty tracks & allocate memory exactly needed
	for (int i = trackList.count() - 1; i >=0; i--) {
		int eventCount = trackList.at(i).count();
		if (eventCount == 0) {
			trackList.remove(i);
		} else {
			totalEventCount += eventCount;
		}
	}
	midiEventList.reserve(totalEventCount);
	qDebug() << "MidiParser: Expected" << totalEventCount << "events";

	// Append events from all the tracks to the output list in sequence
	QVarLengthArray<int> currentIx(trackList.count());	            // The index of the event to be added next
	QVarLengthArray<SynthTimestamp> currentTime(trackList.count()); // The time in MIDI ticks of the event to be added next
	for (int i = 0; i < trackList.count(); i++) {
		currentIx[i] = 0;
		currentTime[i] = trackList.at(i).at(0).getTimestamp();
	}
	SynthTimestamp lastEventTime = 0; // Timestamp of the last added event
	forever {
		int trackIx = -1;
		SynthTimestamp nextEventTime = 0x10000000;

		// Find lowest track index with earliest event
		for (int i = 0; i < trackList.count(); i++) {
			if (trackList.at(i).count() <= currentIx[i]) continue;
			if (currentTime[i] < nextEventTime) {
				nextEventTime = currentTime[i];
				trackIx = i;
			}
		}
		if (trackIx == -1) break;
		const MidiEvent *e = &trackList.at(trackIx).at(currentIx[trackIx]);
		forever {
			midiEventList.append(*e);
			midiEventList.last().setTimestamp(nextEventTime - lastEventTime);
			lastEventTime = nextEventTime;
			if (trackList.at(trackIx).count() <= ++currentIx[trackIx]) break;
			e = &trackList.at(trackIx).at(currentIx[trackIx]);
			SynthTimestamp nextDeltaTime = e->getTimestamp();
			if (nextDeltaTime != 0) {
				currentTime[trackIx] += nextDeltaTime;
				break;
			}
		}
	}
	qDebug() << "MidiParser: Actually" << midiEventList.count() << "events";
}