MIXER_STATUS
MMixerOpenWavePin(
    IN PMIXER_CONTEXT MixerContext,
    IN PMIXER_LIST MixerList,
    IN ULONG DeviceId,
    IN ULONG PinId,
    IN LPWAVEFORMATEX WaveFormatEx,
    IN ACCESS_MASK DesiredAccess,
    IN PIN_CREATE_CALLBACK CreateCallback,
    IN PVOID Context,
    OUT PHANDLE PinHandle)
{
    PKSPIN_CONNECT PinConnect;
    PKSDATAFORMAT_WAVEFORMATEX DataFormat;
    LPMIXER_DATA MixerData;
    NTSTATUS Status;
    MIXER_STATUS MixerStatus;

    MixerData = MMixerGetDataByDeviceId(MixerList, DeviceId);
    if (!MixerData)
        return MM_STATUS_INVALID_PARAMETER;

    /* allocate pin connect */
    PinConnect = MMixerAllocatePinConnect(MixerContext, sizeof(KSDATAFORMAT_WAVEFORMATEX));
    if (!PinConnect)
    {
        /* no memory */
        return MM_STATUS_NO_MEMORY;
    }

    /* initialize pin connect struct */
    MMixerInitializePinConnect(PinConnect, PinId);

    /* get offset to dataformat */
    DataFormat = (PKSDATAFORMAT_WAVEFORMATEX) (PinConnect + 1);
    /* initialize with requested wave format */
    MMixerInitializeDataFormat(DataFormat, WaveFormatEx);

    if (CreateCallback)
    {
        /* let the callback handle the creation */
        MixerStatus = CreateCallback(Context, DeviceId, PinId, MixerData->hDevice, PinConnect, DesiredAccess, PinHandle);
    }
    else
    {
        /* now create the pin */
        Status = KsCreatePin(MixerData->hDevice, PinConnect, DesiredAccess, PinHandle);

        /* normalize status */
        if (Status == STATUS_SUCCESS)
            MixerStatus = MM_STATUS_SUCCESS;
        else
            MixerStatus = MM_STATUS_UNSUCCESSFUL;
    }

    /* free create info */
    MixerContext->Free(PinConnect);

    /* done */
    return MixerStatus;
}