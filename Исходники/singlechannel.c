void
filter_midi_onechannelfilter(MidiFilter* self,
		uint32_t tme,
		const uint8_t* const buffer,
		uint32_t size)
{
	if (size > 3) {
		forge_midimessage(self, tme, buffer, size);
		return;
	}

	int chn = buffer[0]&0x0f;
	switch (buffer[0] & 0xf0) {
		case MIDI_NOTEOFF:
		case MIDI_NOTEON:
		case MIDI_POLYKEYPRESSURE:
		case MIDI_CONTROLCHANGE:
		case MIDI_PROGRAMCHANGE:
		case MIDI_CHANNELPRESSURE:
		case MIDI_PITCHBEND:
			if (rintf(*(self->cfg[0])) == chn + 1) {
				forge_midimessage(self, tme, buffer, size);
			}
			break;
		default:
			forge_midimessage(self, tme, buffer, size);
			break;
	}
}