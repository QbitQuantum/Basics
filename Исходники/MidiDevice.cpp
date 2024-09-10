INT CMidiDevice::GetDevInID()
{
	UINT uDeviceInID;
    MMRESULT Result = midiInGetID(m_hMidiIn, &uDeviceInID);
    if(Result != MMSYSERR_NOERROR)
    {
		return -1;
	}

	return uDeviceInID;
}