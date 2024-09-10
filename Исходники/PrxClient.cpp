//------------------------------------------------------------------------------
// Function: Initialize
//
// This routine initializes the sensor to its default properties
//
// Arguments:
//       Device: IN: WDFDEVICE object
//       SensorInstance: IN: SENSOROBJECT for each sensor instance
//
// Return Value:
//      NTSTATUS code
//------------------------------------------------------------------------------
NTSTATUS
PrxDevice::Initialize(
    _In_ WDFDEVICE Device,
    _In_ SENSOROBJECT SensorInstance
    )
{
    NTSTATUS Status = STATUS_SUCCESS;

    SENSOR_FunctionEnter();

    //
    // Store device and instance
    //
    m_Device = Device;
    m_SensorInstance = SensorInstance;
    m_Started = FALSE;

    //
    // Create Lock
    //
    Status = WdfWaitLockCreate(WDF_NO_OBJECT_ATTRIBUTES, &m_Lock);
    if (!NT_SUCCESS(Status))
    {
        TraceError("COMBO %!FUNC! PRX WdfWaitLockCreate failed %!STATUS!", Status);
        goto Exit;
    }

    //
    // Create timer object for polling sensor samples
    //
    {
        WDF_OBJECT_ATTRIBUTES TimerAttributes;
        WDF_TIMER_CONFIG TimerConfig;

        WDF_TIMER_CONFIG_INIT(&TimerConfig, OnTimerExpire);
        WDF_OBJECT_ATTRIBUTES_INIT(&TimerAttributes);
        TimerAttributes.ParentObject = SensorInstance;
        TimerAttributes.ExecutionLevel = WdfExecutionLevelPassive;

        Status = WdfTimerCreate(&TimerConfig, &TimerAttributes, &m_Timer);
        if (!NT_SUCCESS(Status))
        {
            TraceError("COMBO %!FUNC! PRX WdfTimerCreate failed %!STATUS!", Status);
            goto Exit;
        }
    }

    //
    // Sensor Enumeration Properties
    //
    {
        WDF_OBJECT_ATTRIBUTES MemoryAttributes;
        WDFMEMORY MemoryHandle = NULL;
        ULONG Size = SENSOR_COLLECTION_LIST_SIZE(SENSOR_PRX_ENUMERATION_PROPERTY_COUNT);

        MemoryHandle = NULL;
        WDF_OBJECT_ATTRIBUTES_INIT(&MemoryAttributes);
        MemoryAttributes.ParentObject = SensorInstance;
        Status = WdfMemoryCreate(&MemoryAttributes,
                                 PagedPool,
                                 SENSORV2_POOL_TAG_PROXIMITY,
                                 Size,
                                 &MemoryHandle,
                                 reinterpret_cast<PVOID*>(&m_pEnumerationProperties));
        if (!NT_SUCCESS(Status) || nullptr == m_pEnumerationProperties)
        {
            TraceError("COMBO %!FUNC! PRX WdfMemoryCreate failed %!STATUS!", Status);
            goto Exit;
        }

        SENSOR_COLLECTION_LIST_INIT(m_pEnumerationProperties, Size);
        m_pEnumerationProperties->Count = SENSOR_ENUMERATION_PROPERTIES_COUNT;
        m_pEnumerationProperties->Count = SENSOR_PRX_ENUMERATION_PROPERTY_COUNT;

        m_pEnumerationProperties->List[SENSOR_TYPE_GUID].Key = DEVPKEY_Sensor_Type;
        InitPropVariantFromCLSID(GUID_SensorType_Proximity,
                                 &(m_pEnumerationProperties->List[SENSOR_TYPE_GUID].Value));

        m_pEnumerationProperties->List[SENSOR_MANUFACTURER].Key = DEVPKEY_Sensor_Manufacturer;
        InitPropVariantFromString(L"Manufacturer name",
                                  &(m_pEnumerationProperties->List[SENSOR_MANUFACTURER].Value));

        m_pEnumerationProperties->List[SENSOR_MODEL].Key = DEVPKEY_Sensor_Model;
        InitPropVariantFromString(L"PRX",
                                  &(m_pEnumerationProperties->List[SENSOR_MODEL].Value));

        m_pEnumerationProperties->List[SENSOR_CONNECTION_TYPE].Key = DEVPKEY_Sensor_ConnectionType;
        // The DEVPKEY_Sensor_ConnectionType values match the SensorConnectionType enumeration
        InitPropVariantFromUInt32(static_cast<ULONG>(SensorConnectionType::Integrated),
                                 &(m_pEnumerationProperties->List[SENSOR_CONNECTION_TYPE].Value));

        m_pEnumerationProperties->List[SENSOR_PERSISTENT_UNIQUEID].Key = DEVPKEY_Sensor_PersistentUniqueId;
        InitPropVariantFromCLSID(GUID_PrxDevice_UniqueID,
                                 &(m_pEnumerationProperties->List[SENSOR_PERSISTENT_UNIQUEID].Value));

        m_pEnumerationProperties->List[SENSOR_ISPRIMARY].Key = DEVPKEY_Sensor_IsPrimary;
        InitPropVariantFromBoolean(FALSE,
                                 &(m_pEnumerationProperties->List[SENSOR_ISPRIMARY].Value));

        m_pEnumerationProperties->List[SENSOR_PROPERTY_PRX_TYPE].Key = DEVPKEY_Sensor_ProximityType;
        InitPropVariantFromUInt32(PROXIMITY_TYPE::ProximityType_HumanProximity,
                                 &(m_pEnumerationProperties->List[SENSOR_PROPERTY_PRX_TYPE].Value));

        m_pEnumerationProperties->List[SENSOR_ISWAKECAPABLE].Key = PKEY_Sensor_WakeCapable;
        InitPropVariantFromBoolean(FALSE,
                                 &(m_pEnumerationProperties->List[SENSOR_ISWAKECAPABLE].Value));

    }

    //
    // Supported Data-Fields
    //
    {
        WDF_OBJECT_ATTRIBUTES MemoryAttributes;
        WDFMEMORY MemoryHandle = NULL;
        ULONG Size = SENSOR_PROPERTY_LIST_SIZE(PRX_DATA_COUNT);

        MemoryHandle = NULL;
        WDF_OBJECT_ATTRIBUTES_INIT(&MemoryAttributes);
        MemoryAttributes.ParentObject = SensorInstance;
        Status = WdfMemoryCreate(&MemoryAttributes,
                                 PagedPool,
                                 SENSORV2_POOL_TAG_PROXIMITY,
                                 Size,
                                 &MemoryHandle,
                                 (PVOID*)&m_pSupportedDataFields);
        if (!NT_SUCCESS(Status) || m_pSupportedDataFields == nullptr)
        {
            TraceError("COMBO %!FUNC! PRX WdfMemoryCreate failed %!STATUS!", Status);
            goto Exit;
        }

        SENSOR_PROPERTY_LIST_INIT(m_pSupportedDataFields, Size);
        m_pSupportedDataFields->Count = PRX_DATA_COUNT;

        m_pSupportedDataFields->List[PRX_DATA_TIMESTAMP] = PKEY_SensorData_Timestamp;
        m_pSupportedDataFields->List[PRX_DATA_DETECT] = PKEY_SensorData_ProximityDetection;
        m_pSupportedDataFields->List[PRX_DATA_DISTANCE] = PKEY_SensorData_ProximityDistanceMillimeters;
    }

    //
    // Data
    //
    {
        WDF_OBJECT_ATTRIBUTES MemoryAttributes;
        WDFMEMORY MemoryHandle = NULL;
        ULONG Size = SENSOR_COLLECTION_LIST_SIZE(PRX_DATA_COUNT);
        FILETIME Time = {};

        MemoryHandle = NULL;
        WDF_OBJECT_ATTRIBUTES_INIT(&MemoryAttributes);
        MemoryAttributes.ParentObject = SensorInstance;
        Status = WdfMemoryCreate(&MemoryAttributes,
                                 PagedPool,
                                 SENSORV2_POOL_TAG_PROXIMITY,
                                 Size,
                                 &MemoryHandle,
                                 reinterpret_cast<PVOID*>(&m_pData));
        if (!NT_SUCCESS(Status) || nullptr == m_pData)
        {
            TraceError("COMBO %!FUNC! PRX WdfMemoryCreate failed %!STATUS!", Status);
            goto Exit;
        }

        SENSOR_COLLECTION_LIST_INIT(m_pData, Size);
        m_pData->Count = PRX_DATA_COUNT;

        m_pData->List[PRX_DATA_TIMESTAMP].Key = PKEY_SensorData_Timestamp;
        GetSystemTimePreciseAsFileTime(&Time);
        InitPropVariantFromFileTime(&Time, &(m_pData->List[PRX_DATA_TIMESTAMP].Value));

        m_pData->List[PRX_DATA_DETECT].Key = PKEY_SensorData_ProximityDetection;
        InitPropVariantFromBoolean(FALSE, &(m_pData->List[PRX_DATA_DETECT].Value));

        m_pData->List[PRX_DATA_DISTANCE].Key = PKEY_SensorData_ProximityDistanceMillimeters;
        InitPropVariantFromUInt32(FALSE, &(m_pData->List[PRX_DATA_DISTANCE].Value));

        m_CachedData.Detected = FALSE;
        m_CachedData.DistanceMillimeters = PrxDevice_Maximum_Millimeters;

        m_LastSample.Detected = FALSE;
        m_LastSample.DistanceMillimeters = PrxDevice_Maximum_Millimeters;
    }

    //
    // Sensor Properties
    //
    {
        WDF_OBJECT_ATTRIBUTES MemoryAttributes;
        WDFMEMORY MemoryHandle = NULL;
        ULONG Size = SENSOR_COLLECTION_LIST_SIZE(SENSOR_COMMON_PROPERTY_COUNT);

        MemoryHandle = NULL;
        WDF_OBJECT_ATTRIBUTES_INIT(&MemoryAttributes);
        MemoryAttributes.ParentObject = SensorInstance;
        Status = WdfMemoryCreate(&MemoryAttributes,
                                 PagedPool,
                                 SENSORV2_POOL_TAG_PROXIMITY,
                                 Size,
                                 &MemoryHandle,
                                 reinterpret_cast<PVOID*>(&m_pProperties));
        if (!NT_SUCCESS(Status) || nullptr == m_pProperties)
        {
            TraceError("COMBO %!FUNC! PRX WdfMemoryCreate failed %!STATUS!", Status);
            goto Exit;
        }

        SENSOR_COLLECTION_LIST_INIT(m_pProperties, Size);
        m_pProperties->Count = SENSOR_COMMON_PROPERTY_COUNT;

        m_pProperties->List[SENSOR_COMMON_PROPERTY_STATE].Key = PKEY_Sensor_State;
        InitPropVariantFromUInt32(SensorState_Initializing,
                                  &(m_pProperties->List[SENSOR_COMMON_PROPERTY_STATE].Value));

        m_pProperties->List[SENSOR_COMMON_PROPERTY_MIN_INTERVAL].Key = PKEY_Sensor_MinimumDataInterval_Ms;
        InitPropVariantFromUInt32(Prx_MinDataInterval_Ms,
                                  &(m_pProperties->List[SENSOR_COMMON_PROPERTY_MIN_INTERVAL].Value));
        m_IntervalMs = Prx_MinDataInterval_Ms;
        m_MinimumIntervalMs = Prx_MinDataInterval_Ms;

        m_pProperties->List[SENSOR_COMMON_PROPERTY_MAX_DATAFIELDSIZE].Key = PKEY_Sensor_MaximumDataFieldSize_Bytes;
        InitPropVariantFromUInt32(CollectionsListGetMarshalledSize(m_pData),
                                  &(m_pProperties->List[SENSOR_COMMON_PROPERTY_MAX_DATAFIELDSIZE].Value));

        m_pProperties->List[SENSOR_COMMON_PROPERTY_TYPE].Key = PKEY_Sensor_Type;
        InitPropVariantFromCLSID(GUID_SensorType_Proximity,
                                 &(m_pProperties->List[SENSOR_COMMON_PROPERTY_TYPE].Value));
    }

    //
    // Data field properties
    //
    {
        WDF_OBJECT_ATTRIBUTES MemoryAttributes;
        WDFMEMORY MemoryHandle = NULL;
        ULONG Size = SENSOR_COLLECTION_LIST_SIZE(SENSOR_DATA_FIELD_PROPERTY_COUNT);

        MemoryHandle = NULL;
        WDF_OBJECT_ATTRIBUTES_INIT(&MemoryAttributes);
        MemoryAttributes.ParentObject = SensorInstance;
        Status = WdfMemoryCreate(&MemoryAttributes,
                                 PagedPool,
                                 SENSORV2_POOL_TAG_PROXIMITY,
                                 Size,
                                 &MemoryHandle,
                                 reinterpret_cast<PVOID*>(&m_pDataFieldProperties));
        if (!NT_SUCCESS(Status) || nullptr == m_pDataFieldProperties)
        {
            TraceError("COMBO %!FUNC! PRX WdfMemoryCreate failed %!STATUS!", Status);
            goto Exit;
        }

        SENSOR_COLLECTION_LIST_INIT(m_pDataFieldProperties, Size);
        m_pDataFieldProperties->Count = SENSOR_DATA_FIELD_PROPERTY_COUNT;

        m_pDataFieldProperties->List[SENSOR_RESOLUTION].Key = PKEY_SensorDataField_Resolution;
        InitPropVariantFromUInt32(PrxDevice_Resolution_Millimeters,
                                  &(m_pDataFieldProperties->List[SENSOR_RESOLUTION].Value));

        m_pDataFieldProperties->List[SENSOR_MIN_RANGE].Key = PKEY_SensorDataField_RangeMinimum;
        InitPropVariantFromUInt32(PrxDevice_Minimum_Millimeters,
                                  &(m_pDataFieldProperties->List[SENSOR_MIN_RANGE].Value));

        m_pDataFieldProperties->List[SENSOR_MAX_RANGE].Key = PKEY_SensorDataField_RangeMaximum;
        InitPropVariantFromUInt32(PrxDevice_Maximum_Millimeters,
                                  &(m_pDataFieldProperties->List[SENSOR_MAX_RANGE].Value));
    }

    //
    // Set default threshold
    //
    {
        WDF_OBJECT_ATTRIBUTES MemoryAttributes;
        WDFMEMORY MemoryHandle = NULL;
        ULONG Size =  SENSOR_COLLECTION_LIST_SIZE(PRX_THRESHOLD_COUNT);

        MemoryHandle = NULL;
        WDF_OBJECT_ATTRIBUTES_INIT(&MemoryAttributes);
        MemoryAttributes.ParentObject = SensorInstance;
        Status = WdfMemoryCreate(&MemoryAttributes,
                                 PagedPool,
                                 SENSORV2_POOL_TAG_PROXIMITY,
                                 Size,
                                 &MemoryHandle,
                                 reinterpret_cast<PVOID*>(&m_pThresholds));
        if (!NT_SUCCESS(Status) || nullptr == m_pThresholds)
        {
            TraceError("COMBO %!FUNC! PRX WdfMemoryCreate failed %!STATUS!", Status);
            goto Exit;
        }

        SENSOR_COLLECTION_LIST_INIT(m_pThresholds, Size);

        m_FirstSample = TRUE;
    }

Exit:
    SENSOR_FunctionExit(Status);
    return Status;
}