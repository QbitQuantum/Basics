OVR_PUBLIC_FUNCTION(ovrResult) ovr_GetAudioDeviceInWaveId(UINT* deviceInId)
{
	REV_TRACE(ovr_GetAudioDeviceInWaveId);

	if (!deviceInId)
		return ovrError_InvalidParameter;

	// Query and cache the result
	static UINT cachedId = 0;
	if (!cachedId)
	{
#pragma warning( disable : 4312 )
		if (waveInMessage((HWAVEIN)WAVE_MAPPER, DRVM_MAPPER_PREFERRED_GET, (DWORD_PTR)&cachedId, NULL) != 0)
			return ovrError_AudioDeviceNotFound;
#pragma warning( default : 4312 )
	}

	*deviceInId = cachedId;
	return ovrSuccess;
}