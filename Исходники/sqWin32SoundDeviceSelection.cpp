/* Given a DirectX device identified by "lpszDesc", find the corresponding wave device ID and return it in "waveID".
   This is a hack that we use because GetWaveDeviceIDFromGUID() only works for playback devices (not capture devices). */
HRESULT GetWaveDeviceIDFromName(LPCTSTR lpszDesc, DWORD* waveID)
{
	UINT totalDevices = mixerGetNumDevs();
	UINT currentDevice;
	MIXERCAPS mmCaps;
	MMRESULT mmResult;

	for (currentDevice = 0; currentDevice < totalDevices; currentDevice++) {
		mmResult = mixerGetDevCaps(currentDevice, &mmCaps, sizeof(mmCaps));
		if (mmFAILED(mmResult)) {
			// We couldn't get mixer-caps for this device.  This isn't good, but
			// let's persevere and try the rest of the devices.
			DPRINTF(("ERROR GetWaveDeviceIDFromName() failed to get dev-caps for index %d\n", currentDevice));
		}
		else if (stringMatchIn(lpszDesc, mmCaps.szPname)) {
			// Success!!  We've found a device with a matching name, so grab its
			// device-ID and return triumphantly.
			*waveID = currentDevice;
			return S_OK;
		}
	}
	// Failure.  We couldn't find a matching device.
	*waveID = -1;
	return ERROR_INVALID_DATA;
}