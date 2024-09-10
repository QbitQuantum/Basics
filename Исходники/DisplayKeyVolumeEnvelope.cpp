void DisplayKeyVolumeEnvelope::Update(HANDLE hOut)
{
	WORD note_env_attrib[SPECTRUM_WIDTH];
	WORD voice_env_attrib[VOICES];

	memset(note_env_attrib, env_attrib[EnvelopeState::OFF], sizeof(note_env_attrib));
	for (int v = 0; v < VOICES; ++v)
	{
		EnvelopeState::State const state = amp_env_state[v].state;
		WORD const attrib = env_attrib[state];
		if (state != EnvelopeState::OFF)
		{
			int const x = key_pos.X - keyboard_octave * 12 + voice_note[v];
			if (x >= 0 && x < SPECTRUM_WIDTH)
				note_env_attrib[x] = attrib;
		}
		voice_env_attrib[v] = attrib;
	}

	DWORD written;
	WriteConsoleOutputAttribute(hOut, note_env_attrib, SPECTRUM_WIDTH, { 0, key_pos.Y }, &written);
	WriteConsoleOutputAttribute(hOut, voice_env_attrib, VOICES, voice_pos, &written);
}