	void MidiInputDeviceMidiShare::WakeUp(short r)
	{
		MidiConnect(MidiShareDrvRef, r, true);
		MidiConnect(r, MidiShareDrvRef, true);
	}