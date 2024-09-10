BOOL WINAPI control_handler(DWORD control_type)
{
	midiInStop(midi_in);
	midiInClose(midi_in);

	Pa_StopStream(audio_stream);
	Pa_CloseStream(audio_stream);
	Pa_Terminate();

	Beatbox_free(beatbox);

	return FALSE;
}