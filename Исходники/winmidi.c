int s_ResetMidiStream(WinmidiObject *obj, UINT devNum) {
	UINT retVal;

	assert(obj);

	(void)midiOutReset((HMIDIOUT)obj->m_midiOut);
	if(!s_CleanUpBlockNodes(obj)) {
	return 0;
	}
	(void)midiStreamClose(obj->m_midiOut);
	if(!s_FreeNodes(obj)) {
	return 0;
	}

	retVal = midiStreamOpen(&(obj->m_midiOut), &devNum, 1,
		(DWORD) s_MidiCallback, (DWORD) obj, CALLBACK_FUNCTION); //lint !e620
	if(retVal != MMSYSERR_NOERROR) {
	s_SetMidiError("opening a MIDI stream", retVal);
	return 0;
	}
	assert(obj->m_midiOut);
	
	return 1;
}