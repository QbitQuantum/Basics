HRESULT
WINAPI
IDirectSound8_fnInitialize(
    LPDIRECTSOUND8 iface,
    LPCGUID pcGuidDevice)
{
    GUID DeviceGuid;
    LPOLESTR pGuidStr;
    HRESULT hr;
    LPCDirectSoundImpl This = (LPCDirectSoundImpl)CONTAINING_RECORD(iface, CDirectSoundImpl, lpVtbl);

    if (!RootInfo)
    {
        EnumAudioDeviceInterfaces(&RootInfo);
    }

    /* sanity check */
    ASSERT(RootInfo);

    if (This->bInitialized)
    {
        /* object has already been initialized */
        return DSERR_ALREADYINITIALIZED;
    }

    /* fixme mutual exlucsion */

    if (pcGuidDevice == NULL || IsEqualGUID(pcGuidDevice, &GUID_NULL))
    {
        /* use default playback device id */
        pcGuidDevice = &DSDEVID_DefaultPlayback;
    }

    if (IsEqualIID(pcGuidDevice, &DSDEVID_DefaultCapture) || IsEqualIID(pcGuidDevice, &DSDEVID_DefaultVoiceCapture))
    {
        /* this has to be a winetest */
        return DSERR_NODRIVER;
    }

    /* now verify the guid */
    if (GetDeviceID(pcGuidDevice, &DeviceGuid) != DS_OK)
    {
        if (SUCCEEDED(StringFromIID(pcGuidDevice, &pGuidStr)))
        {
            DPRINT("IDirectSound8_fnInitialize: Unknown GUID %ws\n", pGuidStr);
            CoTaskMemFree(pGuidStr);
        }
        return DSERR_INVALIDPARAM;
    }

    hr = FindDeviceByGuid(&DeviceGuid, &This->Filter);

    if (SUCCEEDED(hr))
    {
        This->bInitialized = TRUE;
        return DS_OK;	
    }

    DPRINT("Failed to find device\n");
    return DSERR_INVALIDPARAM;
}