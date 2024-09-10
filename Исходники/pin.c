NTSTATUS
NTAPI
InstantiatePins(
    IN PKSAUDIO_DEVICE_ENTRY DeviceEntry,
    IN PKSPIN_CONNECT Connect,
    IN PDISPATCH_CONTEXT DispatchContext,
    IN PSYSAUDIODEVEXT DeviceExtension)
{
    NTSTATUS Status;
    HANDLE RealPinHandle;
    PKSDATAFORMAT_WAVEFORMATEX InputFormat;
    PKSDATAFORMAT_WAVEFORMATEX OutputFormat = NULL;
    PKSPIN_CONNECT MixerPinConnect = NULL;
    KSPIN_CINSTANCES PinInstances;

    DPRINT("InstantiatePins entered\n");

    /* query instance count */
    Status = GetPinInstanceCount(DeviceEntry, &PinInstances, Connect);
    if (!NT_SUCCESS(Status))
    {
        /* failed to query instance count */
        return Status;
    }

    /* can be the pin be instantiated */
    if (PinInstances.PossibleCount == 0)
    {
        /* caller wanted to open an instance-less pin */
        return STATUS_UNSUCCESSFUL;
    }

    /* has the maximum instance count been exceeded */
    if (PinInstances.CurrentCount == PinInstances.PossibleCount)
    {
        /* FIXME pin already exists
         * and kmixer infrastructure is not implemented
         */
        return STATUS_UNSUCCESSFUL;
    }

    /* Fetch input format */
    InputFormat = (PKSDATAFORMAT_WAVEFORMATEX)(Connect + 1);

    /* Let's try to create the audio irp pin */
    Status = KsCreatePin(DeviceEntry->Handle, Connect, GENERIC_READ | GENERIC_WRITE, &RealPinHandle);

    if (!NT_SUCCESS(Status))
    {
        /* FIXME disable kmixer
         */
        return STATUS_UNSUCCESSFUL;
    }
#if 0
    if (!NT_SUCCESS(Status))
    {
        /* the audio irp pin didnt accept the input format
         * let's compute a compatible format
         */
        MixerPinConnect = AllocateItem(NonPagedPool, sizeof(KSPIN_CONNECT) + sizeof(KSDATAFORMAT_WAVEFORMATEX));
        if (!MixerPinConnect)
        {
            /* not enough memory */
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        /* Zero pin connect */
        RtlZeroMemory(MixerPinConnect, sizeof(KSPIN_CONNECT) + sizeof(KSDATAFORMAT_WAVEFORMATEX));

        /* Copy initial connect details */
        RtlMoveMemory(MixerPinConnect, Connect, sizeof(KSPIN_CONNECT));


        OutputFormat = (PKSDATAFORMAT_WAVEFORMATEX)(MixerPinConnect + 1);

        Status = ComputeCompatibleFormat(DeviceEntry, Connect->PinId, InputFormat, OutputFormat);
        if (!NT_SUCCESS(Status))
        {
            DPRINT1("ComputeCompatibleFormat failed with %x\n", Status);
            FreeItem(MixerPinConnect);
            return Status;
        }

        /* Retry with Mixer format */
        Status = KsCreatePin(DeviceEntry->Handle, MixerPinConnect, GENERIC_READ | GENERIC_WRITE, &RealPinHandle);
        if (!NT_SUCCESS(Status))
        {
           /* This should not fail */
            DPRINT1("KsCreatePin failed with %x\n", Status);
            DPRINT1(" InputFormat: SampleRate %u Bits %u Channels %u\n", InputFormat->WaveFormatEx.nSamplesPerSec, InputFormat->WaveFormatEx.wBitsPerSample, InputFormat->WaveFormatEx.nChannels);
            DPRINT1("OutputFormat: SampleRate %u Bits %u Channels %u\n", OutputFormat->WaveFormatEx.nSamplesPerSec, OutputFormat->WaveFormatEx.wBitsPerSample, OutputFormat->WaveFormatEx.nChannels);

            FreeItem(MixerPinConnect);
            return Status;
        }
    }
#endif

    //DeviceEntry->Pins[Connect->PinId].References = 0;

    /* initialize dispatch context */
    DispatchContext->Handle = RealPinHandle;
    DispatchContext->PinId = Connect->PinId;
    DispatchContext->AudioEntry = DeviceEntry;


    DPRINT("RealPinHandle %p\n", RealPinHandle);

    /* Do we need to transform the audio stream */
    if (OutputFormat != NULL)
    {
        /* Now create the mixer pin */
        Status = CreateMixerPinAndSetFormat(DeviceExtension->KMixerHandle,
                                            MixerPinConnect,
                                            (PKSDATAFORMAT)InputFormat,
                                            (PKSDATAFORMAT)OutputFormat,
                                            &DispatchContext->hMixerPin);

        /* check for success */
        if (!NT_SUCCESS(Status))
        {
            DPRINT1("Failed to create Mixer Pin with %x\n", Status);
            FreeItem(MixerPinConnect);
        }
    }
    /* done */
    return Status;
}