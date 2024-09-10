void processNotes(HumdrumRecord& record) {
	NoteEvent note;
	int pitch = 0;
	double duration = 0.0;
	int staccatoQ = 0;
	int accentQ = 0;
	int sforzandoQ = 0;
	int i, j;
	int notecount = 0;
	char buffer[128] = {0};
	for (i=0; i<record.getFieldCount(); i++) {
		if ((record.getPrimaryTrack(i) < (int)trackmute.size())
				&& trackmute[record.getPrimaryTrack(i)]) {
			continue;
		}
		if (record.getExInterpNum(i) == E_KERN_EXINT) {
			notecount = record.getTokenCount(i);
			if (strcmp(record[i], ".") == 0) {
				continue;
			}
			for (j=0; j<notecount; j++) {
				record.getToken(buffer, i, j);
				if (strchr(buffer, '[')) {
					// total tied note durations
					duration = data.getTiedDuration(linenum, i, j);
				} else {
					duration = Convert::kernToDuration(buffer);
				}
				pitch = Convert::kernToMidiNoteNumber(buffer);
				// skip rests
				if (pitch < 0) {
					continue;
				}
				pitch += transpose;
				// don't play note which is transposed too extremely
				if (pitch < 0)   { continue; }
				if (pitch > 127) { continue; }

				// skip tied notes
				if (strchr(buffer, '_') || strchr(buffer, ']')) {
					continue;
				}

				accentQ    = strchr(buffer, '^')  == NULL? 0 : 1;
				sforzandoQ = strchr(buffer, 'z')  == NULL? 0 : 1;
				staccatoQ  = strchr(buffer, '\'') == NULL? 0 : 1;
				note.setChannel(0);
				note.setKey(pitch);
				note.setOnTime(t_time);
				duration = duration * 60000 / tempo / tempoScale;
				if (shortenQ) {
					duration -= shortenamount;
					if (duration < mine) {
						duration = mine;
					}
				}
				note.setDur((int)duration);
				if (staccatoQ) {
					note.setDur((int)(0.5 * note.getDur()));
				}
				note.setKey(pitch);
				if (accentQ) {
					velocity *= 1.3;
				}
				if (sforzandoQ) {
					velocity *= 1.5;
				}
				if (velocity > 127) {
					velocity = 127;
				}
				note.setVelocity(velocity);

				note.activate();
				note.action(eventBuffer);
				eventBuffer.insert(note);
			}
		}
	}
}