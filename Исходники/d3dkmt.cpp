VOID
D3DKMTInitialize()
{
    VOID *gdi32 = NULL;
    VOID *deviceInfoSet;
    UINT32 result;
    UINT32 memberIndex;
    UINT32 detailDataSize;
    SP_DEVICE_INTERFACE_DATA            deviceInterfaceData;
    SP_DEVICE_INTERFACE_DETAIL_DATA_W   *detailData;
    SP_DEVINFO_DATA                     deviceInfoData;
    //D3DKMT_OPENADAPTERFROMDEVICENAME    openAdapterFromDeviceName;
    D3DKMT_QUERYSTATISTICS              queryStatistics;

    gdi32 = Module::Load(L"gdi32.dll");

    if (!gdi32)
    {
        return;
    }

    D3DKMTOpenAdapterFromDeviceName = (TYPE_D3DKMTOpenAdapterFromDeviceName) Module::GetProcedureAddress(
                                                                                gdi32,
                                                                                "D3DKMTOpenAdapterFromDeviceName"
                                                                                );

    D3DKMTQueryStatistics = (TYPE_D3DKMTQueryStatistics) Module::GetProcedureAddress(gdi32, "D3DKMTQueryStatistics");

    if (!D3DKMTOpenAdapterFromDeviceName || !D3DKMTQueryStatistics)
    {
        return;
    }

    deviceInfoSet = SetupDiGetClassDevsW(&GUID_DISPLAY_DEVICE_ARRIVAL_I,
                                         NULL, NULL,
                                         DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

    if (!deviceInfoSet)
    {
        return;
    }

    memberIndex = 0;
    deviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    while (SetupDiEnumDeviceInterfaces(deviceInfoSet, NULL, &GUID_DISPLAY_DEVICE_ARRIVAL_I, memberIndex, &deviceInterfaceData))
    {
        detailDataSize = 0x100;
		detailData = (SP_DEVICE_INTERFACE_DETAIL_DATA_W*) Memory::Allocate(detailDataSize);
        detailData->cbSize = 6; /*sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_W)*/
        deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

        result = SetupDiGetDeviceInterfaceDetailW(
                    deviceInfoSet,
                    &deviceInterfaceData,
                    detailData,
                    detailDataSize,
                    &detailDataSize,
                    &deviceInfoData
                    );

        if (result)
        {
            openAdapterFromDeviceName.pDeviceName = detailData->DevicePath;

            if (NT_SUCCESS(D3DKMTOpenAdapterFromDeviceName(&openAdapterFromDeviceName)))
            {
                memset(&queryStatistics, 0, sizeof(D3DKMT_QUERYSTATISTICS));

                queryStatistics.Type = D3DKMT_QUERYSTATISTICS_ADAPTER;
                queryStatistics.AdapterLuid = openAdapterFromDeviceName.AdapterLuid;

                if (NT_SUCCESS(D3DKMTQueryStatistics(&queryStatistics)))
                {
                    UINT32 i;

                    D3dkmt_GpuAdapter = AllocateGpuAdapter(queryStatistics.QueryResult.AdapterInformation.NbSegments);

                    D3dkmt_GpuAdapter->AdapterLuid       = openAdapterFromDeviceName.AdapterLuid;
                    D3dkmt_GpuAdapter->NodeCount     = queryStatistics.QueryResult.AdapterInformation.NodeCount;
                    D3dkmt_GpuAdapter->SegmentCount  = queryStatistics.QueryResult.AdapterInformation.NbSegments;

                    RtlInitializeBitMap(
                        &D3dkmt_GpuAdapter->ApertureBitMap,
                        D3dkmt_GpuAdapter->ApertureBitMapBuffer,
                        queryStatistics.QueryResult.AdapterInformation.NbSegments
                        );

                    EtGpuTotalNodeCount += D3dkmt_GpuAdapter->NodeCount;

                    EtGpuTotalSegmentCount += D3dkmt_GpuAdapter->SegmentCount;

                    D3dkmt_GpuAdapter->FirstNodeIndex = EtGpuNextNodeIndex;
                    EtGpuNextNodeIndex += D3dkmt_GpuAdapter->NodeCount;

                    for (i = 0; i < D3dkmt_GpuAdapter->SegmentCount; i++)
                    {
                        memset(&queryStatistics, 0, sizeof(D3DKMT_QUERYSTATISTICS));

                        queryStatistics.Type = D3DKMT_QUERYSTATISTICS_SEGMENT;
                        queryStatistics.AdapterLuid = D3dkmt_GpuAdapter->AdapterLuid;
                        queryStatistics.QuerySegment.SegmentId = i;

                        if (NT_SUCCESS(D3DKMTQueryStatistics(&queryStatistics)))
                        {
                            UINT64 commitLimit;
                            UINT32 aperature;

                            commitLimit = queryStatistics.QueryResult.SegmentInformationV1.CommitLimit;
                            aperature = queryStatistics.QueryResult.SegmentInformationV1.Aperture;

                            if (aperature)
                                RtlSetBits(&D3dkmt_GpuAdapter->ApertureBitMap, i, 1);
                            else
                                EtGpuDedicatedLimit += commitLimit;
                        }
                    }
                }
            }
        }

		Memory::Free(detailData);

        memberIndex++;
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);

    EtGpuNodeBitMapBuffer = (UINT32*) Memory::Allocate(BYTES_NEEDED_FOR_BITS(EtGpuTotalNodeCount));
    
	RtlInitializeBitMap(&EtGpuNodeBitMap, EtGpuNodeBitMapBuffer, EtGpuTotalNodeCount);

    EtGpuNodesTotalRunningTimeDelta = (PPH_UINT64_DELTA) Memory::Allocate(sizeof(PH_UINT64_DELTA) * EtGpuTotalNodeCount);

    memset(EtGpuNodesTotalRunningTimeDelta, 0, sizeof(PH_UINT64_DELTA) * EtGpuTotalNodeCount);
}