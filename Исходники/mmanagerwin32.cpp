MInputDeviceWin32::~MInputDeviceWin32()
{
	if(hMidiIn) {
		midiInStop(hMidiIn);
		midiInClose(hMidiIn);
	}
}