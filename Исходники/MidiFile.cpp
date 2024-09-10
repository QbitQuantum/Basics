void CMidiFile::WriteTrack(const CMidiEventArray& Event, LPCTSTR Name)
{
	static bool	HasP2[8] = {1, 1, 1, 1, 0, 0, 1, 1};
	FILE_POS	StartPos = BeginTrack();	// write track header
	USES_CONVERSION;
	if (Name != NULL) {	// if track name specified
		int	len = UINT64TO32(_tcslen(Name));
		if (len) {	// if track name has non-zero length
			WriteMeta(ME_TRACK_NAME, len);	// write meta header
			Write(T2CA(Name), len);	// write track name
		}
	}
	BYTE	RunningStatus = 0;	// init running status
	int	nEvents = Event.GetSize();
	for (int iEvent = 0; iEvent < nEvents; iEvent++) {	// for each event
		const MIDI_EVENT&	ev = Event[iEvent];
		WriteVarLen(ev.DeltaT);	// write variable-length delta time
		BYTE	status = MIDI_STAT(ev.Msg);	// get message status
		if (status != RunningStatus) {	// if status changed
			WriteByte(status);
			RunningStatus = status;
		}
		WriteByte(MIDI_P1(ev.Msg));	// write message 1st parameter
		if (HasP2[(status >> 4) - 8])	// if message has 2nd parameter
			WriteByte(MIDI_P2(ev.Msg));	// write message 2nd parameter
	}
	EndTrack(StartPos);	// finish track and fix header
}