void MIDIDeviceOutJack::longMsgOut(const char* data, int size)
{
	m_hdr.dwBufferLength = size;
	m_hdr.dwBytesRecorded = size;
	m_hdr.lpData = (char*)data;

	MMRESULT result;

	result = midiOutPrepareHeader((HMIDIOUT)m_handle, &m_hdr, sizeof(m_hdr));
	if (result != MMSYSERR_NOERROR)
		error("MIDIDeviceOutJack::longMsgOut (prepare)", result);

	result = midiOutLongMsg((HMIDIOUT)m_handle, &m_hdr, sizeof(m_hdr));
	if (result != MMSYSERR_NOERROR)
		error("MIDIDeviceOutJack::longMsgOut", result);

	result = midiOutUnprepareHeader((HMIDIOUT)m_handle, &m_hdr, sizeof(m_hdr));
	if (result != MMSYSERR_NOERROR)
		error("MIDIDeviceOutJack::longMsgOut (unprepare)", result);
}