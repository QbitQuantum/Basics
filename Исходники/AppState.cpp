UINT AppState::GetMidiDeviceId()
{
    UINT deviceId = 0;
    UINT cDevices = midiOutGetNumDevs();
    for (UINT i = 0; i < cDevices; i++)
    {
        MIDIOUTCAPS outcaps = { 0 };
        MMRESULT result = midiOutGetDevCaps(i, &outcaps, sizeof(outcaps));
        if (result == MMSYSERR_NOERROR)
        {
            if (0 == lstrcmpi(outcaps.szPname, _midiDeviceName.c_str()))
            {
                deviceId = i;
                break;
            }
        }
    }
    return deviceId;
}