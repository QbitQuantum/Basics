void SoundGen2GS::advanceMidiPlayer() {
	if (_disableMidi)
		return;

	const uint8 *p;
	uint8 parm1, parm2;
	static uint8 cmd, chn;

	if (_playingSound == -1 || _vm->_game.sounds[_playingSound] == NULL) {
		warning("Error playing Apple IIGS MIDI sound resource");
		_playing = false;
		return;
	}

	IIgsMidi *midiObj = (IIgsMidi *) _vm->_game.sounds[_playingSound];

	_ticks++;
	_playing = true;
	p = midiObj->getPtr();

	while (true) {
		// Check for end of MIDI sequence marker (Can also be here before delta-time)
		if (*p == MIDI_STOP_SEQUENCE) {
			debugC(3, kDebugLevelSound, "End of MIDI sequence (Before reading delta-time)");
			_playing = false;
			midiObj->rewind();
			return;
		}
		if (*p == MIDI_TIMER_SYNC) {
			debugC(3, kDebugLevelSound, "Timer sync");
			p++; // Jump over the timer sync byte as it's not needed
			continue;
		}

		// Check for delta time
		uint8 delta = *p;
		if (midiObj->_ticks + delta > _ticks)
			break;
		midiObj->_ticks += delta;
		p++;

		// Check for end of MIDI sequence marker (This time it after reading delta-time)
		if (*p == MIDI_STOP_SEQUENCE) {
			debugC(3, kDebugLevelSound, "End of MIDI sequence (After reading delta-time)");
			_playing = false;
			midiObj->rewind();
			return;
		}

		// Separate byte into command and channel if it's a command byte.
		// Otherwise use running status (i.e. previously set command and channel).
		if (*p & 0x80) {
			cmd = *p++;
			chn = cmd & 0x0f;
			cmd >>= 4;
		}

		switch (cmd) {
		case MIDI_NOTE_OFF:
			parm1 = *p++;
			parm2 = *p++;
			debugC(3, kDebugLevelSound, "channel %X: note off (key = %d, velocity = %d)", chn, parm1, parm2);
			midiNoteOff(chn, parm1, parm2);
			break;
		case MIDI_NOTE_ON:
			parm1 = *p++;
			parm2 = *p++;
			debugC(3, kDebugLevelSound, "channel %X: note on (key = %d, velocity = %d)", chn, parm1, parm2);
			midiNoteOn(chn, parm1, parm2);
			break;
		case MIDI_CONTROLLER:
			parm1 = *p++;
			parm2 = *p++;
			debugC(3, kDebugLevelSound, "channel %X: controller %02X = %02X", chn, parm1, parm2);
			// The tested Apple IIGS AGI MIDI resources only used
			// controllers 0 (Bank select?), 7 (Volume) and 64 (Sustain On/Off).
			// Controller 0's parameter was in range 94-127,
			// controller 7's parameter was in range 0-127 and
			// controller 64's parameter was always 0 (i.e. sustain off).
			switch (parm1) {
			case 7:
				_channels[chn].setVolume(parm2);
				break;
			}
			break;
		case MIDI_PROGRAM_CHANGE:
			parm1 = *p++;
			debugC(3, kDebugLevelSound, "channel %X: program change %02X", chn, parm1);
			_channels[chn].setInstrument(getInstrument(parm1));
			break;
		case MIDI_PITCH_WHEEL:
			parm1 = *p++;
			parm2 = *p++;
			debugC(3, kDebugLevelSound, "channel %X: pitch wheel (unimplemented)", chn);
			break;

		default:
			debugC(3, kDebugLevelSound, "channel %X: unimplemented command %02X", chn, cmd);
			break;
		}
	}